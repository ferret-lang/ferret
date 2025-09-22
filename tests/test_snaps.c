#include "lib/snaps.c"
#include "lib/snaps.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

#define SNAPSHOT_TEST_DATA "Sample"

static void test_snapshot_filepath_generation(void **state) {
  char *filepath = get_snapshot_filepath(__func__);
  assert_string_equal("snaps/test_snapshot_filepath_generation.snap", filepath);
  free(filepath);
}

static void test_snapshot_generation(void **state) {
  assert_int_equal(1, snapshot_generate(__func__, SNAPSHOT_TEST_DATA));
  FILE *snapshot_file = fopen(get_snapshot_filepath(__func__), "r");
  assert_ptr_not_equal(NULL, snapshot_file);
  if (!(snapshot_file == NULL)) {
    fclose(snapshot_file);
  }
}

static void test_snapshot_validation(void **state) {
  assert_int_equal(1, snapshot_validate(__func__, SNAPSHOT_TEST_DATA));
}

static void test_wrong_snapshot_validation(void **state) {
  assert_int_equal(1, snapshot_validate(__func__, SNAPSHOT_TEST_DATA));
  assert_int_not_equal(1, snapshot_validate(__func__, "Wrong Data"));
}

int main(void) {
  // Defining the test suite.
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_snapshot_filepath_generation),
      cmocka_unit_test(test_snapshot_generation),
      cmocka_unit_test(test_snapshot_validation),
      cmocka_unit_test(test_wrong_snapshot_validation)};

  // Running the tests.
  return cmocka_run_group_tests(tests, NULL, NULL);
}
