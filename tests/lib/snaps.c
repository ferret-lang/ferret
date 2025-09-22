#include "lib/snaps.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snapshot_status_string_equivalent(SnapshotStatus_e status_e) {
  switch (status_e) {
  case SNAPSHOT_STATUS_PENDING:
    return "needs review";
  case SNAPSHOT_STATUS_ACCEPTED:
    return "accepted";
  }
}

char *snapshot_extension_string_equivalent(SnapshotExtension_e extension_e) {
  for (int i = 0; i < sizeof(snapshot_extensions) / sizeof(SnapshotExtension_t);
       i++) {
    if (snapshot_extensions[i].extension_e == extension_e) {
      return snapshot_extensions[i].extension;
    }
  }
  fprintf(stderr, "No extension found!");
  exit(EXIT_FAILURE);
}

// Function to get the filepath to the snapshot file.
char *get_snapshot_filepath(const char *test_name) {
  // Allocating memory for storing filepath.
  char *snapshot_extension =
      snapshot_extension_string_equivalent(SNAPSHOT_EXTENSION_DATA);
  char *filepath =
      (char *)malloc(strlen(SNAPSHOTS_DIR) + 1 + strlen(test_name) +
                     strlen(snapshot_extension) + 1);
  if (filepath == NULL) {
    fprintf(stderr, "Failed to allocate memory for the snap filepath.");
    exit(EXIT_FAILURE);
  }

  sprintf(filepath, "%s/%s%s", SNAPSHOTS_DIR, test_name, snapshot_extension);
  return filepath;
}

// Function to generate the snapshot file.
bool snapshot_generate(const char *test_name, const char *data) {
  char *snapshot_filepath = get_snapshot_filepath(test_name);

  // Getting the pointer the file in writing mode.
  FILE *snapshot_file = fopen(snapshot_filepath, "w");
  if (snapshot_filepath == NULL) {
    fprintf(stderr, "Failed to write the snapshot: %s\n", snapshot_filepath);
    free(snapshot_filepath);
    return false;
  }

  // Writing the snapshot data.
  fprintf(snapshot_file, "%s", data);
  fclose(snapshot_file);
  return true;
}

// Function to compare the snapshot output.
bool snapshot_validate(const char *test_name, const char *data) {
  // Getting the path to the snapshot file on the system.
  char *snapshot_filepath = get_snapshot_filepath(test_name);

  // Open the file in reading mode.
  FILE *snapshot_file = fopen(snapshot_filepath, "r");
  if (snapshot_file == NULL) {
    snapshot_generate(test_name, data);
    fprintf(stderr, "Failed to open the snapshot file: %s\n",
            snapshot_filepath);
    free(snapshot_filepath);
    return true;
  }

  // Reading the snapshot file.
  fseek(snapshot_file, 0, SEEK_END);
  size_t buffer_length = ftell(snapshot_file);
  fseek(snapshot_file, 0, SEEK_SET);

  char *snapshot = (char *)(malloc(buffer_length + 1));
  if (snapshot == NULL) {
    fprintf(stderr, "Failed to allocate memory for the snapshot contents: %s\n",
            snapshot_filepath);
    fclose(snapshot_file);
    free(snapshot_filepath);
    return false;
  }
  fread(snapshot, 1, buffer_length, snapshot_file);
  snapshot[buffer_length] = '\0';

  // Compare the snapshot.
  bool result = strcmp(snapshot, data) == 0;
  free(snapshot);
  fclose(snapshot_file);
  free(snapshot_filepath);

  return result;
}
