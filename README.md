# School 21 · Selected projects

**C · Unix utilities · Libraries · PostgreSQL**

[![Build and tests](https://github.com/Nixsus20/school_21/actions/workflows/verify.yml/badge.svg)](https://github.com/Nixsus20/school_21/actions/workflows/verify.yml)

Здесь опубликована часть моих работ из Школы 21: программы и библиотеки на C, а также SQL-запросы. Остальные проекты, предыдущие версии и часть командных материалов я храню в приватных репозиториях.

## Быстрый старт

Для проверки всех опубликованных проектов понадобятся **Git, Docker и Make**.

```bash
git clone https://github.com/Nixsus20/school_21.git
cd school_21
make check
```

Команда собирает Docker-окружение и запускает проверки. Внутри уже есть GCC, Check, ncurses и PostgreSQL — ставить их в основную систему не нужно. Результаты отображаются в терминале как `PASS`, `FAIL` или `SKIP`.

Если Docker не установлен, но есть GCC, Make и зависимости для тестов, можно проверить C-проекты отдельно:

```bash
make check-local
```

Тесты выполняются на копиях исходников во временной директории. Локальный вариант не проверяет SQL.

## C

| Проект | Что внутри |
| --- | --- |
| [Simple Bash Utils](C/simple-bash-utils/) | `cat` и `grep`: флаги, файлы, регулярные выражения и сравнение с системными утилитами |
| [s21_stringplus](C/string-library/) | Свои функции для строк и памяти, частичная реализация `sprintf` |
| [s21_decimal](C/decimal-library/) | Десятичная арифметика, битовые операции и преобразования типов |
| [s21_matrix](C/matrix-library/) | Работа с матрицами, динамической памятью и вычислением определителя |
| [Terminal Tetris](C/terminal-tetris/) | Игровые состояния, управление фигурами и интерфейс на `ncurses` |

Для каждого проекта есть отдельный README: условия задания, ограничения, файлы реализации и команды сборки.

### Поиграть в Tetris

Понадобятся GCC, Make и установленная библиотека разработки ncurses.

```bash
make -C C/terminal-tetris/src
./C/terminal-tetris/src/tetris
```

Клавиши: `s` — начало игры, стрелки — перемещение, пробел — поворот, `p` — пауза, `Esc` — выход.

## SQL / PostgreSQL

| Серия | Темы |
| --- | --- |
| [01 · Basics](SQL/01-sql-basics/) | `SELECT`, фильтрация, `CASE` |
| [02 · Set operations](SQL/02-set-operations/) | `UNION`, `EXCEPT`, `INTERSECT`, соединения |
| [03 · JOIN и CTE](SQL/03-joins-and-subqueries/) | Поиск пропусков, внешние соединения, подзапросы |
| [04 · DML](SQL/04-data-manipulation/) | `INSERT`, `UPDATE`, `DELETE` |
| [05 · Views](SQL/05-views-and-snapshots/) | `VIEW`, `MATERIALIZED VIEW`, обновление |
| [06 · Traveling salesman](SQL/06-traveling-salesman/) | Рекурсивные запросы и стоимость маршрутов |

Упражнения лежат в отдельных `.sql`-файлах. В README каждого набора описаны сами задачи и ограничения на используемый SQL.

## Проверка

Команда `make check` собирает пять C-проектов, сравнивает `cat` и `grep` с системными командами, запускает unit-тесты на Check и выполняет SQL-запросы в отдельных временных базах PostgreSQL.

Используется [собственная тестовая схема](scripts/sql-fixture.sql), а не школьный набор данных. Это проверка сборки и поведения на выбранных примерах, а не гарантия правильности для всех входных данных.

[Скрипт проверки](scripts/check.sh) · [Dockerfile](Dockerfile) · [История запусков](https://github.com/Nixsus20/school_21/actions/workflows/verify.yml)

Часть проектов выполнялась в команде. Оригинальные методические материалы Школы 21 сюда не включены.
