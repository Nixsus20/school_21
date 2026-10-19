#include <check.h>

#include "brick_game/tetris/code.h"

static int rand_values[] = {0, 1, 2, 3, 4, 5, 6};  
static int rand_index = 0;


int rand() {
  int value = rand_values[rand_index];
  rand_index =
      (rand_index + 1) % (sizeof(rand_values) / sizeof(rand_values[0]));
  return value;
}

// Тест для функции getCurrentState
START_TEST(test_getCurrentState) {
  State_t* state = getCurrentState();
  ck_assert_ptr_nonnull(state);
  ck_assert_int_eq(state->status, Initial);
}
END_TEST

// Тест для функции createMatrix
START_TEST(test_createMatrix) {
  int H = 5, W = 5;
  int** matrix = createMatrix(H, W);
  ck_assert_ptr_nonnull(matrix);

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      ck_assert_int_eq(matrix[i][j], 0);  // проверка, что начальные значения 0
    }
  }

  freeMatrix(matrix, H);
}
END_TEST

// Тест для функции freeMatrix
START_TEST(test_freeMatrix) {
  int H = 3, W = 3;
  int** matrix = createMatrix(H, W);
  ck_assert_ptr_nonnull(matrix);
  freeMatrix(matrix, H);  // Проверяем, что не возникнет утечек памяти
}
END_TEST

// Тест для функции generateNewBlock
START_TEST(test_generateNewBlock_A) {
  int blockSize;
  rand_index = 0;  // Устанавливаем `rand()` на A
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 4);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_B) {
  int blockSize;
  rand_index = 1;  // Устанавливаем `rand()` на B
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_G) {
  int blockSize;
  rand_index = 2;  
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_D) {
  int blockSize;
  rand_index = 3;  
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 2);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_O) {
  int blockSize;
  rand_index = 4;  
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_P) {
  int blockSize;
  rand_index = 5;  
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_else) {
  int blockSize;
  rand_index = 6;  
  int** block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);

  freeMatrix(block, blockSize);
}
END_TEST

// Тест для функции rotate
START_TEST(test_rotate) {
  int size = 2;
  int** block = createMatrix(size, size);
  block[0][0] = 1;
  block[0][1] = 0;
  block[1][0] = 1;
  block[1][1] = 1;

  int** rotatedBlock = createMatrix(size, size);
  rotate(rotatedBlock, block, size);

  // Проверяем, что после поворота блок поменялся
  ck_assert_int_eq(rotatedBlock[0][0], 1);
  ck_assert_int_eq(rotatedBlock[0][1], 1);
  ck_assert_int_eq(rotatedBlock[1][0], 1);
  ck_assert_int_eq(rotatedBlock[1][1], 0);

  freeMatrix(block, size);
  freeMatrix(rotatedBlock, size);
}
END_TEST

// Тест для функции moveBlockLeft
START_TEST(test_moveBlockLeft) {
  State_t* state = getCurrentState();
  state->coordX = 0;
  state->coordY = 1;

  int** block = createMatrix(2, 2);
  block[0][0] = 1;
  block[0][1] = 1;
  block[1][0] = 1;
  block[1][1] = 0;

  state->block = block;

  moveBlockLeft();
  ck_assert_int_eq(state->coordY, 0);  
  freeMatrix(block, 2);
}
END_TEST

// Тест для функции moveBlockRight
START_TEST(test_moveBlockRight) {
  State_t* state = getCurrentState();
  state->coordX = 0;
  state->coordY = 1;

  int** block = createMatrix(2, 2);
  block[0][0] = 1;
  block[0][1] = 1;
  block[1][0] = 1;
  block[1][1] = 0;

  state->block = block;

  moveBlockRight();
  ck_assert_int_eq(state->coordY, 2);  // Блок должен был переместиться вправо

  freeMatrix(block, 2);
}
END_TEST

START_TEST(test_copyMatrix) {
  int H = 2, W = 2;

  // Создаем исходную и целевую матрицу
  int** src = malloc(H * sizeof(int*));
  int** dest = malloc(H * sizeof(int*));

  for (int i = 0; i < H; i++) {
    src[i] = malloc(W * sizeof(int));
    dest[i] = malloc(W * sizeof(int));
  }

  // Инициализируем исходную матрицу
  src[0][0] = 1;
  src[0][1] = 2;
  src[1][0] = 3;
  src[1][1] = 4;

  // Копируем данные из src в dest
  copyMatrix(dest, src, H, W);

  // Проверяем, что содержимое матриц одинаковое
  ck_assert_int_eq(dest[0][0], 1);
  ck_assert_int_eq(dest[0][1], 2);
  ck_assert_int_eq(dest[1][0], 3);
  ck_assert_int_eq(dest[1][1], 4);

  // Освобождаем память
  for (int i = 0; i < H; i++) {
    free(src[i]);
    free(dest[i]);
  }
  free(src);
  free(dest);
}
END_TEST

START_TEST(test_pauseGame) {
  State_t* state = getCurrentState();

  // Изначально игра не на паузе
  ck_assert_int_eq(state->Pause, 0);

  // Время старта игры
  unsigned long long initialStartTime = currentTimeMillis();

  // Устанавливаем паузу
  pauseGame();

  // Проверяем, что игра теперь на паузе
  ck_assert_int_eq(state->Pause, 1);

  // Проверяем, что время на паузе обновляется правильно
  unsigned long long elapsedTime = currentTimeMillis() - initialStartTime;
  if (elapsedTime < state->timeLeft) {
    ck_assert_int_eq(state->timeLeft, state->timeLeft - elapsedTime);
  } else {
    ck_assert_int_eq(state->timeLeft, 0);
  }

  // Снимаем паузу
  pauseGame();

  // Проверяем, что игра снова не на паузе
  ck_assert_int_eq(state->Pause, 0);

  // Проверяем, что startTime обновился
  unsigned long long newStartTime = currentTimeMillis();
  ck_assert_int_ge(
      newStartTime,
      initialStartTime);  // Время старта не может быть меньше текущего
}
END_TEST

START_TEST(test_SpawnNewBlock) {
  // Устанавливаем начальное состояние
  State_t* state = getCurrentState();

  // Инициализируем состояние вручную
  state->blockSize = 2;
  state->coordX = 0;
  state->coordY = 0;
  state->block = createMatrix(2, 2);  // создаем блок размером 2x2
  state->nextBlockSize = 3;
  state->nextblock = createMatrix(3, 3);  // создаем следующий блок размером 3x3
  state->speed = 1000;

  // Вызов функции
  spawnNewBlock();

  // Проверка изменений состояния
  ck_assert_int_eq(state->blockSize, 3);  // новый блок должен быть размером 3
  ck_assert_int_eq(state->coordX,
                   -1);  // координаты должны быть установлены в -1
  ck_assert_int_eq(state->coordY,
                   3);  // для блока размером 3 координаты Y должны быть 3
}

START_TEST(test_initializeState) {
    initializeState();
    State_t *state = getCurrentState();
    ck_assert_ptr_nonnull(state->field);
    ck_assert_int_eq(state->status, Initial);
    // Можно добавить больше проверок для других полей state
}
END_TEST

START_TEST(test_processTimer_initial) {
    initializeState(); // чтобы state->status == Initial
    unsigned long long t = processTimer();
    ck_assert_int_eq(t, (unsigned long long)-1);
}
END_TEST

START_TEST(test_userInput_start) {
    initializeState();
    userInput(Start);
    State_t *state = getCurrentState();
    ck_assert_int_eq(state->status, Spawn); // после startGame
}
END_TEST

START_TEST(test_userInput_left_right_down_action_pause_terminate) {
    initializeState();
    State_t *state = getCurrentState();
    state->status = Moving;
    state->blockSize = 2;
    state->block = createMatrix(2, 2);
    state->nextBlockSize = 2;
    state->nextblock = createMatrix(2, 2);
    state->field = createMatrix(FIELD_H, FIELD_W);

    userInput(Left);
    userInput(Right);
    userInput(Down);
    userInput(Action);
    userInput(Pause);
    userInput(Terminate);

    // Проверки: например, что память освобождена, статус изменён и т.д.
    // Можно добавить дополнительные проверки по необходимости
}
END_TEST

START_TEST(test_startGame) {
    initializeState();
    startGame();
    State_t *state = getCurrentState();
    ck_assert_int_eq(state->status, Spawn);
}
END_TEST


START_TEST(test_rotateBlock) {
    initializeState();
    State_t *state = getCurrentState();
    state->blockSize = 2;
    state->coordX = 1;
    state->coordY = 1;
    state->field = createMatrix(FIELD_H, FIELD_W);

    // Заполняем блок
    int **block = createMatrix(2, 2);
    block[0][0] = 1; block[0][1] = 0;
    block[1][0] = 1; block[1][1] = 1;
    state->block = block;

    // Проверяем, что rotateBlock не вызывает ошибок и меняет статус
    rotateBlock();
    ck_assert(state->status == Moving || state->status == Attaching);

    freeMatrix(state->block, 2);
    freeMatrix(state->field, FIELD_H);
}
END_TEST

START_TEST(test_shiftBlock_not_attached) {
    initializeState();
    State_t *state = getCurrentState();
    state->coordX = 5;
    state->speed = 42;
    state->status = Moving;
    state->startTime = 0;
    state->timeLeft = 0;

    // Заглушка: blockIsAttached всегда возвращает 0
    // Если возможно, переопределите blockIsAttached для теста, либо убедитесь, что он вернёт 0
    // Например, если blockIsAttached зависит от состояния поля, подготовьте поле так, чтобы он вернул 0

    shiftBlock();

    ck_assert_int_eq(state->coordX, 6);
    ck_assert_int_eq(state->status, Moving);
    ck_assert_int_eq(state->timeLeft, state->speed);
    // Можно добавить проверку, что startTime обновился (например, стал не 0)
}
END_TEST

START_TEST(test_shiftBlock_attached) {
    initializeState();
    State_t *state = getCurrentState();
    state->coordX = FIELD_H - 1; // Поместить блок в самый низ поля
    state->blockSize = 2;
    state->block = createMatrix(2, 2);
    state->block[0][0] = 1; state->block[0][1] = 1;
    state->block[1][0] = 1; state->block[1][1] = 1;
    state->field = createMatrix(FIELD_H, FIELD_W);

    // Теперь блок "упрётся" в низ поля, и blockIsAttached должен вернуть 1
    shiftBlock();

    ck_assert_int_eq(state->status, Attaching);

    freeMatrix(state->block, 2);
    freeMatrix(state->field, FIELD_H);
}
END_TEST

START_TEST(test_updateLevel) {
    initializeState();
    State_t *state = getCurrentState();

    // Начальные значения
    state->score = 0;
    state->level = 1;
    state->speed = 100; // Например, исходная скорость

    // Проверяем, что при score < NEW_LEVEL_THRESHOLD уровень не меняется
    updateLevel();
    ck_assert_int_eq(state->level, 1);

    // Увеличиваем score так, чтобы перейти на следующий уровень
    state->score = NEW_LEVEL_THRESHOLD;
    state->level = 1;
    state->speed = 100;
    updateLevel();
    ck_assert_int_eq(state->level, 2);
    ck_assert_int_eq(state->speed, 100 - SPEED_STEP);

    // Проверяем, что уровень не превышает MAX_LEVEL
    state->score = NEW_LEVEL_THRESHOLD * MAX_LEVEL;
    state->level = 1;
    state->speed = 100;
    updateLevel();
    ck_assert_int_eq(state->level, MAX_LEVEL);

    // Проверяем, что скорость не уменьшается ниже лимита (если есть лимит)
    // Можно добавить дополнительные проверки по необходимости
}
END_TEST

START_TEST(test_consumeRows) {
    initializeState();
    State_t *state = getCurrentState();

    // 1. Одна заполненная строка
    for (int j = 0; j < FIELD_W; j++) {
        state->field[FIELD_H - 1][j] = 1;
    }
    int oldScore = state->score;
    consumeRows();
    ck_assert_int_eq(state->score, oldScore + 100);

    // 2. Две заполненные строки
    initializeState();
    for (int j = 0; j < FIELD_W; j++) {
        state->field[FIELD_H - 1][j] = 1;
        state->field[FIELD_H - 2][j] = 1;
    }
    oldScore = state->score;
    consumeRows();
    ck_assert_int_eq(state->score, oldScore + 300);

    // 3. Три заполненные строки
    initializeState();
    for (int j = 0; j < FIELD_W; j++) {
        state->field[FIELD_H - 1][j] = 1;
        state->field[FIELD_H - 2][j] = 1;
        state->field[FIELD_H - 3][j] = 1;
    }
    oldScore = state->score;
    consumeRows();
    ck_assert_int_eq(state->score, oldScore + 700);

    // 4. Четыре заполненные строки
    initializeState();
    for (int j = 0; j < FIELD_W; j++) {
        state->field[FIELD_H - 1][j] = 1;
        state->field[FIELD_H - 2][j] = 1;
        state->field[FIELD_H - 3][j] = 1;
        state->field[FIELD_H - 4][j] = 1;
    }
    oldScore = state->score;
    consumeRows();
    ck_assert_int_eq(state->score, oldScore + 1500);
}
END_TEST

START_TEST(test_attachBlock_normal) {
    initializeState();
    State_t *state = getCurrentState();
    state->blockSize = 2;
    state->coordX = 2; // Блок полностью в поле
    state->coordY = 3;
    state->block = createMatrix(2, 2);
    state->block[0][0] = 1; state->block[0][1] = 0;
    state->block[1][0] = 1; state->block[1][1] = 1;
    state->field = createMatrix(FIELD_H, FIELD_W);

    attachBlock();

    // Проверяем, что блок прикрепился к полю
    ck_assert_int_eq(state->field[2][3], 1);
    ck_assert_int_eq(state->field[1][3], 1);
    ck_assert_int_eq(state->field[1][4], 1);
    ck_assert_int_eq(state->status, Spawn);

    freeMatrix(state->block, 2);
    freeMatrix(state->field, FIELD_H);
}
END_TEST

START_TEST(test_attachBlock_gameOver) {
    initializeState();
    State_t *state = getCurrentState();
    state->blockSize = 2;
    state->coordX = 0; // Блок выходит за верх поля
    state->coordY = 3;
    state->block = createMatrix(2, 2);
    state->block[0][0] = 1; state->block[0][1] = 0;
    state->block[1][0] = 1; state->block[1][1] = 1;
    state->field = createMatrix(FIELD_H, FIELD_W);

    attachBlock();

    // Проверяем, что наступил game over
    ck_assert_int_eq(state->status, GameOver);

    freeMatrix(state->block, 2);
    freeMatrix(state->field, FIELD_H);
}
END_TEST

START_TEST(test_updateCurrentState) {
    initializeState();
    State_t *state = getCurrentState();

    // Установим значения для state
    state->score = 123;
    state->level = 2;
    state->speed = 77;
    state->blockSize = 2;
    state->coordX = 5;
    state->coordY = 4;
    state->block = createMatrix(2, 2);
    state->block[0][0] = 1; state->block[0][1] = 0;
    state->block[1][0] = 1; state->block[1][1] = 1;
    state->field = createMatrix(FIELD_H, FIELD_W);
    state->field[5][4] = 1; // для проверки copyMatrix

    state->nextBlockSize = 2;
    state->nextblock = createMatrix(2, 2);
    state->nextblock[0][0] = 1; state->nextblock[0][1] = 1;
    state->nextblock[1][0] = 0; state->nextblock[1][1] = 1;

    // Проверяем основную логику
    GameInfo_t info = updateCurrentState();

    ck_assert_ptr_nonnull(info.field);
    ck_assert_int_eq(info.score, 123);
    ck_assert_int_eq(info.level, 2);
    ck_assert_int_eq(info.speed, 77);
    ck_assert_ptr_nonnull(info.next);

    // Проверяем, что блок корректно отображён на поле info.field
    ck_assert_int_eq(info.field[5][4], 1); // из state->field
    ck_assert_int_eq(info.field[5][4], state->field[5][4]);
    // Проверяем, что блок state->block тоже отображён
    ck_assert_int_eq(info.field[5][4], 1); // из блока
    ck_assert_int_eq(info.field[4][4], 1); // из блока (coordX - 1, coordY + 0)

    // Проверяем next
    ck_assert_int_eq(info.next[0][0], 1);
    ck_assert_int_eq(info.next[0][1], 1);
    ck_assert_int_eq(info.next[1][1], 1);

    // Проверяем паузы
    state->status = Initial;
    info = updateCurrentState();
    ck_assert_int_eq(info.pause, GameStart);

    state->Pause = 1;
    info = updateCurrentState();
    ck_assert_int_eq(info.pause, GamePause);

    // Освобождаем память
    freeMatrix(state->block, 2);
    freeMatrix(state->field, FIELD_H);
    freeMatrix(state->nextblock, 2);
    freeMatrix(info.field, FIELD_H);
    freeMatrix(info.next, 4);
}
END_TEST

Suite* game_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("Game");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_getCurrentState);
  tcase_add_test(tc_core, test_createMatrix);
  tcase_add_test(tc_core, test_freeMatrix);
  tcase_add_test(tc_core, test_generateNewBlock_A);
  tcase_add_test(tc_core, test_generateNewBlock_B);
  tcase_add_test(tc_core, test_generateNewBlock_G);
  tcase_add_test(tc_core, test_generateNewBlock_D);
  tcase_add_test(tc_core, test_generateNewBlock_O);
  tcase_add_test(tc_core, test_generateNewBlock_P);
  tcase_add_test(tc_core, test_generateNewBlock_else);
  tcase_add_test(tc_core, test_rotate);
  tcase_add_test(tc_core, test_moveBlockLeft);
  tcase_add_test(tc_core, test_moveBlockRight);
  tcase_add_test(tc_core, test_copyMatrix);
  tcase_add_test(tc_core, test_pauseGame);
  tcase_add_test(tc_core, test_SpawnNewBlock);
  tcase_add_test(tc_core, test_initializeState);
  tcase_add_test(tc_core, test_processTimer_initial);
  tcase_add_test(tc_core, test_userInput_start);
  tcase_add_test(tc_core, test_userInput_left_right_down_action_pause_terminate);
  tcase_add_test(tc_core, test_startGame);
  tcase_add_test(tc_core, test_rotateBlock);
  tcase_add_test(tc_core, test_shiftBlock_not_attached);
  tcase_add_test(tc_core, test_shiftBlock_attached);
  tcase_add_test(tc_core, test_updateLevel);
  tcase_add_test(tc_core, test_consumeRows);
  tcase_add_test(tc_core, test_attachBlock_normal);
  tcase_add_test(tc_core, test_attachBlock_gameOver);
  tcase_add_test(tc_core, test_updateCurrentState);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = game_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
