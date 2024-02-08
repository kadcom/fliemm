#include "file_utils.h"
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>

static LARGE_INTEGER start_time, frequency;

void start_timer(void) {
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start_time);
}

float stop_timer(void) {
  LARGE_INTEGER end_time;
  QueryPerformanceCounter(&end_time);
  return (float)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
}


/* get filename from arguments but if not, then open file dialog */
int get_file_name(int argc, char **argv, char *filename, size_t fnsize) {
  static char fn[MAX_PATH];
  OPENFILENAME ofn;
  char *filter = "All Files\0*.*\0\0";
  if (argc < 2) {
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = fn;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(fn);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == 0) {
      printf("Error: %lu\n", CommDlgExtendedError());
      return 0;
    }

    strncpy(filename, fn, fnsize);
    return 0;
  }

  strncpy(filename, argv[1], fnsize);
  return 0;
}

/* use windows file api to count lines in file */
int count_lines_file_api(const char *filename, int *lines) {
  HANDLE hFile;
  DWORD nRead;
  int n;
  char c;

  hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE) {
    printf("Error: %lu\n", GetLastError());
    return 1;
  }

  n = 0;
  while (1) {
    if (ReadFile(hFile, &c, 1, &nRead, NULL) == 0) {
      printf("Error: %lu\n", GetLastError());
      CloseHandle(hFile);
      return 1;
    }
    if (nRead == 0) break;
    if (c == '\n') n++;
  }

  *lines = n;

  CloseHandle(hFile);
  return 0;
}

/* Use Windows MMAP to count lines in file */
int count_lines_mmap(const char *filename, int *lines) {
  HANDLE hFile;
  HANDLE hMap;
  char *p;
  int n;
  DWORD i, size;

  hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE) {
    printf("Error: %lu\n", GetLastError());
    return 1;
  }

  size = GetFileSize(hFile, NULL);
  if (size == INVALID_FILE_SIZE) {
    printf("Error: %lu\n", GetLastError());
    CloseHandle(hFile);
    return 1;
  }

  hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
  if (hMap == NULL) {
    printf("Error: %lu\n", GetLastError());
    CloseHandle(hFile);
    return 1;
  }

  p = (char *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
  if (p == NULL) {
    printf("Error: %lu\n", GetLastError());
    CloseHandle(hMap);
    CloseHandle(hFile);
    return 1;
  }

  n = 0;
  for (i = 0; i < size; i++) {
    if (p[i] == '\n') n++;
  }

  UnmapViewOfFile(p);
  CloseHandle(hMap);
  CloseHandle(hFile);


  *lines = n;
  return 0;
}

