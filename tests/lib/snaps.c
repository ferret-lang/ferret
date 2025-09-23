#include "lib/snaps.h"
#include "helpers.c"
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
char *generate_filepath(const char *test_name,
                        SnapshotExtension_e extension_e) {
  // Allocating memory for storing filepath.
  char *snapshot_extension = snapshot_extension_string_equivalent(extension_e);
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
bool snapshot_update(const char *test_name, const char *data) {
  char *filepath = generate_filepath(test_name, SNAPSHOT_EXTENSION_DATA);
  // Getting the pointer the file in writing mode.
  FILE *snapshot_file = fopen(filepath, "w");
  if (snapshot_file == NULL) {
    fprintf(stderr, "Failed to write the snapshot: %s\n", filepath);
    free(filepath);
    return false;
  }

  // Writing the snapshot data.
  fprintf(snapshot_file, "%s", data);
  fclose(snapshot_file);
  free(filepath);
  return true;
}

bool snapshot_status_update(const char *test_name, SnapshotStatus_e status) {
  char *filepath = generate_filepath(test_name, SNAPSHOT_EXTENSION_STATUS);
  FILE *snapshot_status_file = fopen(filepath, "w");
  if (snapshot_status_file == NULL) {
    fprintf(stderr, "Failed to write the snapshot status: %s", filepath);
    free(filepath);
    return false;
  }

  fprintf(snapshot_status_file, "%s",
          snapshot_status_string_equivalent(status));
  fclose(snapshot_status_file);
  free(filepath);
  return true;
}

// Function to check if the snapshot file exists.
bool snapshot_exists(const char *test_name, SnapshotExtension_e extension_e) {
  char *filepath = generate_filepath(test_name, extension_e);
  if (!file_exists(filepath)) {
    free(filepath);
    return false;
  }
  free(filepath);
  return true;
}

char *get_snapshot_contents(const char *test_name,
                            SnapshotExtension_e extension_e) {
  char *filepath = generate_filepath(test_name, extension_e);
  char *file_contents = get_file_contents(filepath);
  free(filepath);
  return file_contents;
}

// Function to compare the snapshot output.
bool snapshot_validate(const char *test_name, const char *data) {
  if (!snapshot_exists(test_name, SNAPSHOT_EXTENSION_DATA)) {
    snapshot_update(test_name, data);
    snapshot_status_update(test_name, SNAPSHOT_STATUS_PENDING);
    return false;
  }

  if (!snapshot_exists(test_name, SNAPSHOT_EXTENSION_STATUS)) {
    snapshot_status_update(test_name, SNAPSHOT_STATUS_PENDING);
    return false;
  }

  // Reading the files.
  char *snapshot = get_snapshot_contents(test_name, SNAPSHOT_EXTENSION_DATA);
  char *snapshot_status =
      get_snapshot_contents(test_name, SNAPSHOT_EXTENSION_STATUS);

  // Strip any trailing newlines or spaces from snapshot_status
  char *status_trimmed = strdup(snapshot_status);
  status_trimmed[strcspn(status_trimmed, "\n")] =
      '\0'; // Remove newline at the end

  if (strcmp(status_trimmed, snapshot_status_string_equivalent(
                                 SNAPSHOT_STATUS_ACCEPTED)) != 0) {
    free(status_trimmed);
    free(snapshot);
    free(snapshot_status);
    return false;
  }

  // Compare the snapshot data
  bool result = (strcmp(snapshot, data) == 0);
  free(status_trimmed);
  free(snapshot);
  free(snapshot_status);
  return result;
}
