#ifndef KADCOM_FILE_UTILS_H_
#define KADCOM_FILE_UTILS_H_

int count_lines_file_api(const char *filename, int *lines);
int count_lines_mmap(const char *filename, int *lines);

int get_file_name(int argc, char **argv, char **filename);

void start_timer(void);
float stop_timer(void);

#endif  // KADCOM_FILE_UTILS_H_
