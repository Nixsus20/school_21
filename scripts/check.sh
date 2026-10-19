#!/usr/bin/env bash
# Build and test the published School 21 projects without changing the working tree.
set -u
set -o pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WORK="$(mktemp -d "${TMPDIR:-/tmp}/school21-check.XXXXXX")" || exit 2
trap 'rm -rf "$WORK"' EXIT

passed=0
failed=0
skipped=0

pass() { printf 'PASS  %s\n' "$1"; passed=$((passed + 1)); }
fail() {
  printf 'FAIL  %s\n' "$1"
  if [[ -f "$WORK/last.log" ]]; then tail -n 25 "$WORK/last.log" | sed 's/^/      /'; fi
  failed=$((failed + 1))
}
skip() { printf 'SKIP  %s\n' "$1"; skipped=$((skipped + 1)); }
run() {
  local label="$1"
  shift
  : > "$WORK/last.log"
  if "$@" > "$WORK/last.log" 2>&1; then pass "$label"; else fail "$label"; fi
}

if ! command -v gcc >/dev/null 2>&1 || ! command -v make >/dev/null 2>&1; then
  echo "Missing gcc/make. Install build-essential (Debian/Ubuntu) or run 'make check' with Docker."
  exit 2
fi

for project in simple-bash-utils string-library decimal-library matrix-library terminal-tetris; do
  mkdir -p "$WORK/$project"
  cp -R "$ROOT/C/$project/src" "$WORK/$project/src" || exit 2
done

echo "== C: build =="
run "cat: compile"     make -C "$WORK/simple-bash-utils/src/cat" all
run "grep: compile"    make -C "$WORK/simple-bash-utils/src/grep" all
run "string: archive"  make -C "$WORK/string-library/src" all
run "decimal: archive" make -C "$WORK/decimal-library/src" s21_decimal.a
run "matrix: archive"  make -C "$WORK/matrix-library/src" all
run "Tetris: compile"  make -C "$WORK/terminal-tetris/src" all

cat_smoke() {
  local dir="$WORK/simple-bash-utils/src/cat"
  printf 'alpha\n\nbeta\n\n\nend\t!\n' > "$WORK/input.txt"
  for flag in -b -n -s -v -E -T; do
    "$dir/s21_cat" "$flag" "$WORK/input.txt" > "$WORK/actual"
    cat "$flag" "$WORK/input.txt" > "$WORK/expected"
    if ! diff -u "$WORK/expected" "$WORK/actual"; then
      echo "Mismatch for cat $flag"
      return 1
    fi
  done
}

grep_smoke() {
  local dir="$WORK/simple-bash-utils/src/grep"
  printf 'Hello world\nquiet line\nHELLO again\nanother line\n' > "$WORK/input.txt"
  local flag
  for flag in -i -n -v -c -l; do
    grep "$flag" 'hello' "$WORK/input.txt" > "$WORK/expected"
    local system_status=$?
    "$dir/s21_grep" "$flag" 'hello' "$WORK/input.txt" > "$WORK/actual"
    local program_status=$?
    if [[ "$system_status" -ne "$program_status" ]]; then
      echo "Exit-code mismatch for grep $flag: grep=$system_status, s21_grep=$program_status"
      return 1
    fi
    if ! diff -u "$WORK/expected" "$WORK/actual"; then
      echo "Output mismatch for grep $flag"
      return 1
    fi
  done
}

echo
echo "== C: smoke tests =="
if [[ -x "$WORK/simple-bash-utils/src/cat/s21_cat" ]]; then
  run "cat: compare with /bin/cat" cat_smoke
else
  skip "cat: build failed"
fi
if [[ -x "$WORK/simple-bash-utils/src/grep/s21_grep" ]]; then
  run "grep: compare with /bin/grep" grep_smoke
else
  skip "grep: build failed"
fi

if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists check; then
  echo
  echo "== C: Check unit tests =="
  # Unlike the original decimal Makefile, re-running ./test checks the real exit status.
  run "string: unit tests"     make -C "$WORK/string-library/src" test
  run "decimal: compile tests" make -C "$WORK/decimal-library/src" test
  if [[ -x "$WORK/decimal-library/src/test" ]]; then
    run "decimal: unit tests" "$WORK/decimal-library/src/test"
  else
    skip "decimal: unit-test executable not built"
  fi
  run "matrix: unit tests"     make -C "$WORK/matrix-library/src" test
  run "Tetris: unit tests"     make -C "$WORK/terminal-tetris/src" test
else
  skip "Check tests: install check, libsubunit-dev and pkg-config, or use Docker (make check)"
fi

sql_group() {
  local folder="$1"
  local index="$2"
  local db="school21_verify_$$_$index"
  local result=0
  local file

  psql -X -q -v ON_ERROR_STOP=1 -d postgres \
    -c "CREATE DATABASE $db;" || return 1

  if ! psql -X -q -v ON_ERROR_STOP=1 -d "$db" -f "$ROOT/scripts/sql-fixture.sql"; then
    result=1
  else
    while IFS= read -r -d '' file; do
      echo "  running ${file#"$ROOT/"}"
      if ! psql -X -q -v ON_ERROR_STOP=1 -d "$db" -f "$file" >/dev/null; then
        echo "  SQL failed: ${file#"$ROOT/"}"
        result=1
        break
      fi
    done < <(find "$ROOT/SQL/$folder/src" -type f -name '*.sql' -print0 | sort -zV)
  fi

  psql -X -q -v ON_ERROR_STOP=1 -d postgres \
    -c "DROP DATABASE $db;" || result=1
  return "$result"
}

echo
echo "== SQL: PostgreSQL integration smoke tests =="
if [[ "${CHECK_SQL:-0}" == "1" ]]; then
  if ! command -v psql >/dev/null 2>&1; then
    skip "SQL: psql unavailable"
  else
    run "SQL 01: basics"             sql_group "01-sql-basics" 1
    run "SQL 02: set operations"     sql_group "02-set-operations" 2
    run "SQL 03: joins"              sql_group "03-joins-and-subqueries" 3
    run "SQL 04: DML"                sql_group "04-data-manipulation" 4
    run "SQL 05: views"              sql_group "05-views-and-snapshots" 5
    run "SQL 06: traveling salesman" sql_group "06-traveling-salesman" 6
  fi
else
  skip "SQL requires disposable PostgreSQL: run 'make check' (Docker)"
fi

echo
printf 'Results: %d passed, %d failed, %d skipped\n' "$passed" "$failed" "$skipped"
if (( failed > 0 )); then exit 1; fi
if (( skipped > 0 )); then echo "Some checks were skipped; this is not a complete test run."; fi
