#ifndef FERRET_LANG_SNAPHS_H
#define FERRET_LANG_SNAPHS_H

#include <stdbool.h>
#include <stddef.h>

#define SNAPSHOTS_DIR "snaps"

typedef enum {
  SNAPSHOT_STATUS_PENDING,
  SNAPSHOT_STATUS_ACCEPTED
} SnapshotStatus_e;

typedef struct {
  const char *status;
  SnapshotStatus_e status_e;
} SnapshotStatus_t;

typedef enum {
  SNAPSHOT_EXTENSION_DATA,
  SNAPSHOT_EXTENSION_STATUS
} SnapshotExtension_e;

typedef struct {
  size_t length;
  char *extension;
  SnapshotExtension_e extension_e;
} SnapshotExtension_t;

static const SnapshotExtension_t snapshot_extensions[] = {
    {.extension = ".snap", .length = 5, .extension_e = SNAPSHOT_EXTENSION_DATA},
    {.extension = ".sstat",
     .length = 6,
     .extension_e = SNAPSHOT_EXTENSION_STATUS}};

char *snapshot_status_string_equivalent(SnapshotStatus_e status_e);
char *snapshot_extension_string_equivalent(SnapshotExtension_e extension_e);
char *generate_filepath(const char *test_name, SnapshotExtension_e extension_e);
bool snapshot_update(const char *filepath, const char *data);
bool snapshot_status_update(const char *filepath, SnapshotStatus_e status_e);
bool snapshot_validate(const char *test_name, const char *data);

#endif
