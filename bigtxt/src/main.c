#include "file_utils.h"
#include <stdio.h>

int main(int argc, char**argv) {
  char filename[MAX_PATH];
  int lines;
  int ret;
  float elapsedms;

  ret = get_file_name(argc, argv, filename, sizeof(filename));
  if (ret != 0) {
    return -1;
  }

  printf("Reading file %s\n", filename);

  start_timer();
  ret = count_lines_file_api(filename, &lines);
  if (ret != 0) {
    return -1;
  }
  elapsedms = stop_timer();

  printf("File %s has %d lines\n", filename, lines);
  printf("Reading file %s with file API took %.2f ms\n", filename, elapsedms);


  start_timer();
  ret = count_lines_mmap(filename, &lines);
  if (ret != 0) {
    return -1;
  }
  elapsedms = stop_timer();

  printf("File %s has %d lines\n", filename, lines);
  printf("Reading file %s with mmap took %.2f ms\n", filename, elapsedms);

#if WIN32 
  system("pause");
#endif

  return 0;
}
