#include "file_utils.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>

static struct timespec start_time;

void start_timer(void) {
  clock_gettime(CLOCK_MONOTONIC, &start_time);
}

/* elapsed in milliseconds */
float stop_timer(void) {
  struct timespec end_time;
  float elapsed;

  clock_gettime(CLOCK_MONOTONIC, &end_time);
  elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

  return elapsed;
}

size_t get_page_size(void) {
  return sysconf(_SC_PAGESIZE);
}

size_t get_file_size(const char *filename) {
  struct stat sb;

  if (stat(filename, &sb) == -1) {
    return -1;
  }

  return sb.st_size;
}

int get_file_name(int argc, char **argv, char *filename, size_t fnsize) {
  if (argc != 2) {
    return -1;
  }

  strncpy(filename, argv[1], fnsize);

  return 0;
}

int count_lines_file_api(const char *filename, int *lines) {
  int fd, n;
  uint8_t c;

  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return -1;
  }
  n = 0;


  while (read(fd, &c, 1) > 0) {
    if (c == '\n') {
        n++;
    }
  }

  close(fd);

  *lines = n;

  return 0;
}

int count_lines_mmap(const char *filename, int *lines) {
  int fd, n;
  struct stat sb;
  uint8_t *data;
  off_t i;
  size_t sz;

  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return -1;
  }

  if (fstat(fd, &sb) == -1) {
    close(fd);
    return -1;
  }

  n = 0;
  sz = ALIGN_TO_SIZE(sb.st_size, get_page_size());

  data = mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
  if (data == MAP_FAILED) {
    close(fd);
    return -1;
  }

  for (i = 0; i < sb.st_size; i++) {
    if (data[i] == '\n') {
      n++;
    }
  }

  munmap(data, sb.st_size);
  close(fd);

  *lines = n;

  return 0;
} 
