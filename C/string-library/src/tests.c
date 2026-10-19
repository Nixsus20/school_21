#include "test.h"

START_TEST(test_strcspn) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_uint_eq(s21_strcspn(text_test[i], text_test[2]),
                      strcspn(text_test[i], text_test[2]));
  }
}
END_TEST

START_TEST(test_memcmp) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_int_eq(
        s21_memcmp(text_test[i], text_test[2], strlen(text_test[2])),
        memcmp(text_test[i], text_test[2], strlen(text_test[2])));
  }
}
END_TEST

START_TEST(test_strcmp) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_int_eq(s21_strcmp(text_test[i], text_test[2]),
                     strcmp(text_test[i], text_test[2]));
  }
}
END_TEST

START_TEST(test_strncmp) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_int_eq(s21_strncmp(text_test[i], text_test[2], 3),
                     strncmp(text_test[i], text_test[2], 3));
  }
}
END_TEST

START_TEST(test_memcpy) {
  char dest[256];
  for (int i = 0; i <= 6; i++) {
    ck_assert_mem_eq(s21_memcpy(dest, text_test[i], strlen(text_test[i]) + 1),
                     memcpy(dest, text_test[i], strlen(text_test[i]) + 1),
                     strlen(text_test[i]) + 1);
  }
}
END_TEST

START_TEST(test_memset) {
  char buffer1[256];
  char buffer2[256];
  for (int c = 0; c <= 255; c += 64) {
    ck_assert_mem_eq(s21_memset(buffer1, c, 10), memset(buffer2, c, 10), 10);
  }
}
END_TEST

START_TEST(test_strcpy) {
  char dest[256];
  for (int i = 0; i <= 6; i++) {
    ck_assert_str_eq(s21_strcpy(dest, text_test[i]),
                     strcpy(dest, text_test[i]));
  }
}
END_TEST

START_TEST(test_strncpy) {
  char dest[256];
  for (int i = 0; i <= 6; i++) {
    ck_assert_str_eq(s21_strncpy(dest, text_test[i], 3),
                     strncpy(dest, text_test[i], 3));
  }
}
END_TEST

START_TEST(test_memchr) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_ptr_eq(s21_memchr(text_test[i], 'a', strlen(text_test[i])),
                     memchr(text_test[i], 'a', strlen(text_test[i])));
  }
}
END_TEST

START_TEST(test_strchr) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_ptr_eq(s21_strchr(text_test[i], 'a'), strchr(text_test[i], 'a'));
  }
}
END_TEST

START_TEST(test_strrchr) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_ptr_eq(s21_strrchr(text_test[i], 'a'),
                     strrchr(text_test[i], 'a'));
  }
}
END_TEST

START_TEST(test_insert) {
  for (int i = 0; i <= 6; i++) {
    char *result = s21_insert(text_test[i], "123", 2);
    if (result) {
      free(result);
    }
  }
}
END_TEST

START_TEST(test_to_lower) {
  for (int i = 0; i <= 6; i++) {
    char *result = s21_to_lower(text_test[i]);
    if (result) {
      for (int j = 0; result[j]; j++) {
        ck_assert_int_eq(result[j], tolower(text_test[i][j]));
      }
      free(result);
    }
  }
}
END_TEST

START_TEST(test_to_upper) {
  for (int i = 0; i <= 6; i++) {
    char *result = s21_to_upper(text_test[i]);
    if (result) {
      for (int j = 0; result[j]; j++) {
        ck_assert_int_eq(result[j], toupper(text_test[i][j]));
      }
      free(result);
    }
  }
}
END_TEST

START_TEST(test_trim) {
  for (int i = 0; i <= 6; i++) {
    char *result = s21_trim(text_test[i], " ");
    if (result) {
      free(result);
    }
  }
}
END_TEST

START_TEST(test_strncat) {
  char dest1[256];
  char dest2[256];
  for (int i = 0; i <= 6; i++) {
    strcpy(dest1, text_test[i]);
    strcpy(dest2, text_test[i]);
    ck_assert_str_eq(s21_strncat(dest1, "123", 2), strncat(dest2, "123", 2));
  }
}
END_TEST

START_TEST(test_strspn) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_uint_eq(s21_strspn(text_test[i], text_test[2]),
                      strspn(text_test[i], text_test[2]));
  }
}
END_TEST

START_TEST(test_strstr) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_ptr_eq(s21_strstr(text_test[i], text_test[2]),
                     strstr(text_test[i], text_test[2]));
  }
}
END_TEST

START_TEST(test_strtok) {
  char str1[256], str2[256];
  char *delim = " ,.-";
  for (int i = 0; i <= 6; i++) {
    strcpy(str1, text_test[i]);
    strcpy(str2, text_test[i]);
    char *token1 = s21_strtok(str1, delim);
    char *token2 = strtok(str2, delim);
    while (token1 && token2) {
      ck_assert_str_eq(token1, token2);
      token1 = s21_strtok(NULL, delim);
      token2 = strtok(NULL, delim);
    }
    ck_assert_ptr_eq(token1, token2);
  }
}
END_TEST

START_TEST(test_strpbrk) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_ptr_eq(s21_strpbrk(text_test[i], text_test[2]),
                     strpbrk(text_test[i], text_test[2]));
  }
}
END_TEST

START_TEST(test_strlen) {
  for (int i = 0; i <= 6; i++) {
    ck_assert_uint_eq(s21_strlen(text_test[i]), strlen(text_test[i]));
  }
}
END_TEST

START_TEST(test_strerror) {
  for (int i = 0; i < 200; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_integer_format) {
  char buffer[256];
  char expected[256];

  s21_sprintf(buffer, "%d", 123);
  sprintf(expected, "%d", 123);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%+d", 123);
  sprintf(expected, "%+d", 123);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%d", -123);
  sprintf(expected, "%d", -123);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_float_format) {
  char buffer[256];
  char expected[256];

  s21_sprintf(buffer, "%.2f", 123.456);
  sprintf(expected, "%.2f", 123.456);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%+f", 123.456);
  sprintf(expected, "%+f", 123.456);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%f", -123.456);
  sprintf(expected, "%f", -123.456);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_string_format) {
  char buffer[256];
  char expected[256];

  s21_sprintf(buffer, "%s", "Hello, world!");
  sprintf(expected, "%s", "Hello, world!");
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_char_format) {
  char buffer[256];
  char expected[256];

  s21_sprintf(buffer, "%c", 'A');
  sprintf(expected, "%c", 'A');
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_unsigned_format) {
  char buffer[256];
  char expected[256];

  s21_sprintf(buffer, "%u", 4294967295u);
  sprintf(expected, "%u", 4294967295u);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

Suite *sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_integer_format);
  tcase_add_test(tc_core, test_float_format);
  tcase_add_test(tc_core, test_string_format);
  tcase_add_test(tc_core, test_char_format);
  tcase_add_test(tc_core, test_unsigned_format);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *all_test(void) {
  Suite *su;
  TCase *tcase_strcspn, *tcase_memcmp, *tcase_strcmp, *tcase_strncmp,
      *tcase_memcpy, *tcase_memset, *tcase_strcpy, *tcase_strncpy,
      *tcase_memchr, *tcase_strchr, *tcase_strrchr, *tcase_insert,
      *tcase_to_lower, *tcase_to_upper, *tcase_trim, *tcase_strncat,
      *tcase_strspn, *tcase_strstr, *tcase_strtok, *tcase_strpbrk,
      *tcase_strlen, *tcase_strerror;

  su = suite_create("string.h functions");

  tcase_strcspn = tcase_create("strcspn");
  tcase_memcmp = tcase_create("memcmp");
  tcase_strcmp = tcase_create("strcmp");
  tcase_strncmp = tcase_create("strncmp");
  tcase_memcpy = tcase_create("memcpy");
  tcase_memset = tcase_create("memset");
  tcase_strcpy = tcase_create("strcpy");
  tcase_strncpy = tcase_create("strncpy");
  tcase_memchr = tcase_create("memchr");
  tcase_strchr = tcase_create("strchr");
  tcase_strrchr = tcase_create("strrchr");
  tcase_insert = tcase_create("insert");
  tcase_to_lower = tcase_create("to_lower");
  tcase_to_upper = tcase_create("to_upper");
  tcase_trim = tcase_create("trim");
  tcase_strncat = tcase_create("strncat");
  tcase_strspn = tcase_create("strspn");
  tcase_strstr = tcase_create("strstr");
  tcase_strtok = tcase_create("strtok");
  tcase_strpbrk = tcase_create("strpbrk");
  tcase_strlen = tcase_create("strlen");
  tcase_strerror = tcase_create("strerror");

  tcase_add_test(tcase_strcspn, test_strcspn);
  tcase_add_test(tcase_memcmp, test_memcmp);
  tcase_add_test(tcase_strcmp, test_strcmp);
  tcase_add_test(tcase_strncmp, test_strncmp);
  tcase_add_test(tcase_memcpy, test_memcpy);
  tcase_add_test(tcase_memset, test_memset);
  tcase_add_test(tcase_strcpy, test_strcpy);
  tcase_add_test(tcase_strncpy, test_strncpy);
  tcase_add_test(tcase_memchr, test_memchr);
  tcase_add_test(tcase_strchr, test_strchr);
  tcase_add_test(tcase_strrchr, test_strrchr);
  tcase_add_test(tcase_insert, test_insert);
  tcase_add_test(tcase_to_lower, test_to_lower);
  tcase_add_test(tcase_to_upper, test_to_upper);
  tcase_add_test(tcase_trim, test_trim);
  tcase_add_test(tcase_strncat, test_strncat);
  tcase_add_test(tcase_strspn, test_strspn);
  tcase_add_test(tcase_strstr, test_strstr);
  tcase_add_test(tcase_strtok, test_strtok);
  tcase_add_test(tcase_strpbrk, test_strpbrk);
  tcase_add_test(tcase_strlen, test_strlen);
  tcase_add_test(tcase_strerror, test_strerror);

  suite_add_tcase(su, tcase_strcspn);
  suite_add_tcase(su, tcase_memcmp);
  suite_add_tcase(su, tcase_strcmp);
  suite_add_tcase(su, tcase_strncmp);
  suite_add_tcase(su, tcase_memcpy);
  suite_add_tcase(su, tcase_memset);
  suite_add_tcase(su, tcase_strcpy);
  suite_add_tcase(su, tcase_strncpy);
  suite_add_tcase(su, tcase_memchr);
  suite_add_tcase(su, tcase_strchr);
  suite_add_tcase(su, tcase_strrchr);
  suite_add_tcase(su, tcase_insert);
  suite_add_tcase(su, tcase_to_lower);
  suite_add_tcase(su, tcase_to_upper);
  suite_add_tcase(su, tcase_trim);
  suite_add_tcase(su, tcase_strncat);
  suite_add_tcase(su, tcase_strspn);
  suite_add_tcase(su, tcase_strstr);
  suite_add_tcase(su, tcase_strtok);
  suite_add_tcase(su, tcase_strpbrk);
  suite_add_tcase(su, tcase_strlen);
  suite_add_tcase(su, tcase_strerror);

  return su;
}

int main() {
  Suite *s;
  SRunner *sr;
  s = all_test();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);

  s = sprintf_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}
