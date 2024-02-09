#include "file_utils.h"
#include <stdio.h>

int main(int argc, char**argv) {
  char filename[MAX_PATH];
  int lines;
  int ret;
  float elapsedms;
  size_t file_size, page_size;

  ret = get_file_name(argc, argv, filename, sizeof(filename));
  if (ret != 0) {
    return -1;
  }

  file_size = get_file_size(filename);
  page_size = get_page_size();
  printf("Reading file %s\n", filename);
  printf("Page Size: %lu\n", (unsigned long) page_size);
  printf("File Size: %lu\n", (unsigned long) file_size);
  printf("Aligned Size: %lu\n", (unsigned long) ALIGN_TO_SIZE(file_size, page_size));

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
