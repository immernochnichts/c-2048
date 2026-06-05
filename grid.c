#include "grid.h"
#include <stdio.h>

// get grid value at (x, y)
// (0, 0) is at bottom left;
// x is horizontal
// if out_x and out_y are not null
// store wrapped coords into them
int*
at(struct grid *g, int x, int y)
{
    return &g->array[x + y * g->size];
}

void grid_init(struct grid* g, int* array, int size)
{
    if (g == 0)
    {
        printf("passing null grid to grid_init");
        return;
    }
    if (size < 0)
    {
        printf("warning: passing size < 0 to grid_init");
    }
    if (array == 0)
    {
        printf("warning: passing null array to grid_init");
    }

    g->array = array;
    g->size = size;
}

// 4 debug
void
display(struct grid *g)
{
    for (int i = g->size - 1; i >= 0; i--)
    {
        for (int j = 0; j < g->size; j++)
        {
            printf("%d \t", *at(g, j, i));
        }
        printf("\n");
    }
    printf("\n");
}

void
display_array(int a[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
}