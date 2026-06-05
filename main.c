#include "grid.h"
#include "2048.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// takes array of pointers to grid cells
// to modify the grid immediately
// [0][1][2][3]
//  
// [.][0][.][.]
// [.][1][.][.]
// [.][2][.][.]
// [.][3][.][.]
void
collapse(int* a[])
{
    for (int i = 0; i < 3; i++)
    {
        int j = i + 1;
        while (j > 0)
        {
            if (*a[j - 1] == 0)
            {
                *a[j - 1] = *a[j];
                *a[j] = 0;
            }
            else if (*a[j - 1] == *a[j])
            {
                *a[j - 1] += *a[j];
                *a[j] = 0;
                break;
            }
            j--;
        }
    }
}

// returns array of pointers to grid cells
// row/column of the grid
// the pointer must later be freed
int**
get_slice(struct grid* g, int index, int isrow, int isreversed)
{
    int** a = malloc(4 * sizeof(int*));
    if (isreversed != 0)
    {
        isreversed = 1;
    }

    for (int i = 0; i < 4; i++)
    {
        int j = 3 - i;

        if (isrow)
        {
            a[i] = at(g, i * !isreversed + j * isreversed, index);
        }
        else
        {
            a[i] = at(g, index, i * !isreversed + j * isreversed);
        }
    }

    return a;
}

void step(struct grid* g, enum dir d)
{
    for (int i = 0; i < 4; i++)
    {
        int** s = get_slice(g, i, d == RIGHT || d == LEFT, d == RIGHT || d == UP);
        collapse(s);
        free(s);
    }
}

// spawns 2 or 4 on the grid
// returns success code
// 0 means fine, 1 means gameover
int
spawn_piece(struct grid* g)
{
    int piece = 2 * (rand() % 2 + 1);

    int* cell;
    int ctr = 0;
    while ((*(cell = at(g, rand() % 4, rand() % 4)) != 0) && ctr++ <= 16)
        ;
    
    if (ctr > 16)
    {
        return 1;
    }

    *cell = piece;
    return 0;
}

__declspec( dllexport ) int api_step(int* board, int direction)
{
    struct grid g;

    grid_init(&g, board, 4);

    step(&g, direction);

    return spawn_piece(&g);
}

__declspec( dllexport ) int api_init(int* board)
{
    struct grid g;
    grid_init(&g, board, 4);
    spawn_piece(&g);
    return spawn_piece(&g);
}

void
listen4input(struct grid* g)
{
    display(g);
    char c;
    while ((c = getchar()) != 'q')
    {
        if (c == 'w')
        {
            step(g, UP);
        }
        else if (c == 'a')
        {
            step(g, LEFT);
        }
        else if (c == 's')
        {
            step(g, DOWN);
        }
        else if (c == 'd')
        {
            step(g, RIGHT);
        }
        else
        {
            continue;
        }

        int x = spawn_piece(g);
        if (x == 1)
        {
            printf("\nGAEM OVAH PAL!\n");
            return;
        }

        display(g);
    }
}

int
main()
{
    srand(time(NULL));
    struct grid g;
    int a[16] = { 0 };
    grid_init(&g, a, 4);
    spawn_piece(&g);
    spawn_piece(&g);

    listen4input(&g);
}