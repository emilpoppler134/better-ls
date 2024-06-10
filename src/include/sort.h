#ifndef __SORT_H__
#define __SORT_H__

#include "common.h"
#include "item.h"

void swap(item_t *, item_t *);
int partition(item_t *, int, int);
void quicksort(item_t *, int, int);

#endif
