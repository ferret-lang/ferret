#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "utils.h"

static void test_exit_success(void **state) {
  assert_int_equal(get_exit_code(), 0);
}

int main(void) {
  // Defining the test suite.
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_exit_success),
  };
  
  // Running the tests.
  return cmocka_run_group_tests(tests, NULL, NULL);
}


