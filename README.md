# School 21 / Public projects

**C · Unix tools · Static libraries · PostgreSQL**

[![Build and tests](https://github.com/Nixsus20/school_21/actions/workflows/verify.yml/badge.svg)](https://github.com/Nixsus20/school_21/actions/workflows/verify.yml)

Это публичная часть моих проектов из Школы 21. Здесь можно посмотреть код на C, библиотеки, консольную игру и решения задач на SQL. Остальные работы по Linux и системному анализу, а также более ранние версии проектов остаются в приватном архиве.

## Проекты на C

| Проект | Что внутри |
| --- | --- |
| [Simple Bash Utils](C/simple-bash-utils/) | `cat` и `grep`: работа с файлами, флаги, регулярные выражения, сравнение с системными утилитами |
| [s21_stringplus](C/string-library/) | Функции `string.h`, операции с памятью, своя реализация части `sprintf` |
| [s21_decimal](C/decimal-library/) | Десятичная арифметика, битовое представление, округление и преобразование типов |
| [s21_matrix](C/matrix-library/) | Работа с матрицами и динамической памятью, определитель, обратная матрица |
| [Terminal Tetris](C/terminal-tetris/) | Игровой автомат, управление фигурами, интерфейс через `ncurses` |

В README каждого проекта указаны условия задачи, технические ограничения, сборка и тесты. Исходники находятся в `src/`.

## SQL / PostgreSQL

| Серия | Темы |
| --- | --- |
| [01 · Basics](SQL/01-sql-basics/) | `SELECT`, условия, сортировка, `CASE` |
| [02 · Set operations](SQL/02-set-operations/) | `UNION`, `EXCEPT`, `INTERSECT`, `JOIN` |
| [03 · JOIN и CTE](SQL/03-joins-and-subqueries/) | Соединения, поиск отсутствующих записей, `WITH` |
| [04 · DML](SQL/04-data-manipulation/) | `INSERT`, `UPDATE`, `DELETE` |
| [05 · Views](SQL/05-views-and-snapshots/) | `VIEW`, `MATERIALIZED VIEW`, обновление данных |
| [06 · Traveling salesman](SQL/06-traveling-salesman/) | Рекурсивные запросы и поиск маршрутов в графе |

У каждого SQL-упражнения отдельный файл. Рядом с решениями есть описание задачи и ограничений на синтаксис.

## Клонирование и проверка

Нужны Git, Make и запущенный Docker. Никаких отдельных установок GCC, Check, ncurses или PostgreSQL при таком способе не требуется.

```bash
git clone https://github.com/Nixsus20/school_21.git
cd school_21
make check
```

Команда собирает все пять C-проектов, сравнивает `cat` и `grep` с системными командами, запускает unit-тесты и проверяет SQL на временных базах PostgreSQL. В консоли отображаются `PASS`, `FAIL` и `SKIP`.

**Локально, без Docker:** если установлены GCC, Make и библиотеки для тестов, можно выполнить `make check-local`. Он проверяет C-проекты, но пропускает SQL.

**Запуск Tetris:** при наличии GCC, Make и ncurses:

```bash
make -C C/terminal-tetris/src
./C/terminal-tetris/src/tetris
```

Управление: `s` — старт, стрелки — движение, пробел — поворот, `p` — пауза, `Esc` — выход.

## Как устроены проверки

- [`scripts/check.sh`](scripts/check.sh) — сборка, тесты C и выполнение SQL.
- [`scripts/sql-fixture.sql`](scripts/sql-fixture.sql) — независимые демонстрационные данные для PostgreSQL.
- [`Dockerfile`](Dockerfile) и [`Makefile`](Makefile) — воспроизводимая проверка одной командой.
- [GitHub Actions](https://github.com/Nixsus20/school_21/actions/workflows/verify.yml) — результаты автоматических запусков.

SQL-тесты выполняются на отдельном наборе данных, который создаётся автоматически.
