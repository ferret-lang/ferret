#ifndef FERRET_LANG_SNAPHS_H
#define FERRET_LANG_SNAPHS_H

#include <stdbool.h>
#include <stddef.h>

#define SNAPSHOTS_DIR "snaps"

bool snapshot_generate();
bool snapshot_validate();

#endif
