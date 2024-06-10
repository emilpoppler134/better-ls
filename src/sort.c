#include "include/sort.h"

void swap(item_t *a, item_t *b)
{
  item_t temp = *a;
  memcpy(a, b, sizeof(item_t));
  memcpy(b, &temp, sizeof(item_t));
}

int partition(item_t *arr, int low, int high)
{
  item_t *pivot = &arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
  {
    if ((arr[j].hidden && !pivot->hidden) ||
        (arr[j].type == TYPE_DIR && arr[j].hidden && !pivot->hidden) ||
        (arr[j].type == TYPE_FILE && arr[j].hidden && !pivot->hidden) ||
        (!arr[j].hidden && arr[j].type == TYPE_DIR && !pivot->hidden) ||
        (!arr[j].hidden && arr[j].type == TYPE_FILE && !pivot->hidden && strcmp(arr[j].extension, pivot->extension) < 0))
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void quicksort(item_t *arr, int low, int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quicksort(arr, low, pi - 1);
    quicksort(arr, pi + 1, high);
  }
}
