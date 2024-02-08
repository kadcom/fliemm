#ifndef KADCOM_FILE_UTILS_H_
#define KADCOM_FILE_UTILS_H_

#include <stddef.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

int count_lines_file_api(const char *filename, int *lines);
int count_lines_mmap(const char *filename, int *lines);

int get_file_name(int argc, char **argv, char *filename, size_t fnsize);

void start_timer(void);
float stop_timer(void);

#endif /* KADCOM_FILE_UTILS_H_ */
