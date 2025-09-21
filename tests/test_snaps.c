#include "lib/snaps.c"
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>

#include <cmocka.h>

static void test_snapshot_filepath_generation(void **state) {
  char *filepath = get_snapshot_filepath("test_snapshot_filepath_generation");
  assert_string_equal("snaps/test_snapshot_filepath_generation.snap", filepath);
  free(filepath);
}

int main(void) {
  // Defining the test suite.
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_snapshot_filepath_generation),
  };

  // Running the tests.
  return cmocka_run_group_tests(tests, NULL, NULL);
}
