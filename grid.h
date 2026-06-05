struct grid
{
    int *array;
    int size;
};

int*            at(struct grid *g, int x, int y);
void            grid_init(struct grid* g, int* array, int size);
void            display(struct grid *g);
void            display_array(int a[], int len);