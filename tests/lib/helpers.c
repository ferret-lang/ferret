// Helper function to read the file contents.
#include <stdio.h>
#include <stdlib.h>

bool file_exists(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    return false;
  }
  fclose(file);
  return true;
}

char *get_file_contents(const char *filepath) {
  // Open the file in reading mode.
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open the snapshot file: %s\n", filepath);
    free(file);
    return NULL;
  }

  // Reading the snapshot file.
  fseek(file, 0, SEEK_END);
  size_t buffer_length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)(malloc(buffer_length + 1));
  if (buffer == NULL) {
    fprintf(stderr, "Failed to allocate memory for the snapshot contents: %s\n",
            filepath);
    fclose(file);
    exit(EXIT_FAILURE);
  }
  fread(buffer, 1, buffer_length, file);
  buffer[buffer_length] = '\0';
  return buffer;
}
