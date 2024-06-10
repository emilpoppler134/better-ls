#include "include/common.h"
#include "include/sort.h"
#include "include/item.h"

#include "sort.c"
#include "item.c"

int main(int argc, char **argv)
{
  struct timespec start, end;
  long seconds, nseconds;
  double elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  setlocale(LC_ALL, "");

  if (argc > 1)
  {
    for (int i = 1; i < argc; i++)
    {
      if (strcmp(argv[i], "-f") == 0) mode = MODE_FILES;
      else if (strcmp(argv[i], "-d") == 0) mode = MODE_DIRECTORIES;
      else if (strcmp(argv[i], "-v") == 0) mode = MODE_VISIBLE;
      else if (strcmp(argv[i], "-h") == 0) mode = MODE_HIDDEN;
      else strcpy(directory, argv[i]);
    }
  }

  DIR *d = opendir(directory);
  if (d == NULL)
  {
    printf("Couldn't open ./%s.\n", directory);
    return 1;
  }

  int item_count = 0;

  struct dirent *dir;
  while ((dir = readdir(d)) != NULL)
  {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
    switch (mode)
    {
      case MODE_FILES:
        if (dir->d_type != DT_REG) continue;
        break;
      case MODE_DIRECTORIES:
        if (dir->d_type != DT_DIR) continue;
        break;
      case MODE_VISIBLE:
        if (dir->d_name[0] == '.') continue;
        break;
      case MODE_HIDDEN:
        if (dir->d_name[0] != '.') continue;
        break;
      default:
        break;
    }
    item_count++;
  }
  rewinddir(d);

  item_t *item_list = (item_t *)malloc(item_count * sizeof(item_t));
  int item_index = 0;

  while ((dir = readdir(d)) != NULL)
  {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
    switch (mode)
    {
      case MODE_FILES:
        if (dir->d_type != DT_REG) continue;
        break;
      case MODE_DIRECTORIES:
        if (dir->d_type != DT_DIR) continue;
        break;
      case MODE_VISIBLE:
        if (dir->d_name[0] == '.') continue;
        break;
      case MODE_HIDDEN:
        if (dir->d_name[0] != '.') continue;
        break;
      default:
        break;
    }
    item_list[item_index] = init_item(dir);
    item_index++;
  }
  closedir(d);

  quicksort(item_list, 0, item_count - 1);

  for (int i = 0; i < item_count; i++)
  {
    print_item(item_list[i]);
  }

  free(item_list);

  clock_gettime(CLOCK_MONOTONIC, &end);
  seconds  = end.tv_sec  - start.tv_sec;
  nseconds = end.tv_nsec - start.tv_nsec;
  elapsed = seconds + nseconds/1000000.0;
  printf("%s%s %s%.2f ms%s\n", "\x1B[38;2;80;95;95m", "\U000f199f", "\e[3m", elapsed, PRINT_RESET);

  return 0;
}
