#include "lib/snaps.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *snapshot_extension = ".snap";
size_t snapshot_directory_length = strlen(SNAPSHOTS_DIR);

size_t get_snapshot_extension_length() { return strlen(snapshot_extension); }

// Function to get the filepath to the snapshot file.
static char *get_snapshot_filepath(const char *test_name) {
  // Allocating memory for storing filepath.
  char *filepath =
      (char *)malloc(snapshot_directory_length + 1 + strlen(test_name) +
                     get_snapshot_extension_length() + 1);
  if (filepath == NULL) {
    fprintf(stderr, "Failed to allocate memory for the snap filepath.");
    exit(EXIT_FAILURE);
  }

  sprintf(filepath, "%s/%s%s", SNAPSHOTS_DIR, test_name, snapshot_extension);
  return filepath;
}
