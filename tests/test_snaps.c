#include "lib/snaps.c"
#include "lib/snaps.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

#define SNAPSHOT_TEST_DATA "Sample"

static void test_snapshot_filepath_generation(void **state) {
  char *filepath = generate_filepath(__func__, SNAPSHOT_EXTENSION_DATA);
  assert_string_equal("snaps/test_snapshot_filepath_generation.snap", filepath);
  free(filepath);
}

static void test_snapshot_validation(void **state) {
  assert_int_equal(1, snapshot_validate(__func__, SNAPSHOT_TEST_DATA));
}

int main(void) {
  // Defining the test suite.
  const struct CMUnitTest tests[] =
  { cmocka_unit_test(test_snapshot_filepath_generation),
    cmocka_unit_test(test_snapshot_validation),
  };

  // Running the tests.
  return cmocka_run_group_tests(tests, NULL, NULL);
}
