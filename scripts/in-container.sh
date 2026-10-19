#!/usr/bin/env bash
# Docker-only entrypoint: start disposable PostgreSQL and run the full checker.
set -euo pipefail

version="$(ls -1 /etc/postgresql | head -n 1)"
if [[ -z "$version" ]]; then
  echo "PostgreSQL cluster not found in the verification image."
  exit 2
fi

pg_ctlcluster "$version" main start

# Peer authentication: execute the checks as the postgres OS user.
# The scripts create and drop only databases with the school21_verify_* prefix.
cd /work
exec runuser -u postgres -- env CHECK_SQL=1 bash scripts/check.sh
