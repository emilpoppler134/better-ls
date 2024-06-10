#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <wchar.h>
#include <locale.h>

#define PRINT_RESET "\033[0m"

typedef enum mode_e
{
  MODE_ALL,
  MODE_FILES,
  MODE_DIRECTORIES,
  MODE_VISIBLE,
  MODE_HIDDEN,
  MODE_LENGTH
} mode_e;

mode_e mode = MODE_ALL;
char directory[FILENAME_MAX] = ".";

#endif
