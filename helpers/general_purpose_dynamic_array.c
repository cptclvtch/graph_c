#define ARRAY_CHUNK_SIZE 256
#ifdef REDEF_ARRAY_CHUNK_SIZE
#undef ARRAY_CHUNK_SIZE
#define ARRAY_CHUNK_SIZE REDEF_ARRAY_CHUNK_SIZE
#endif

typedef struct s_array
{
    size_t type_size;

    void** data;
    size_t max_chunk_index;
}array;

#define init_array(type) _init_array(sizeof(type))
array* _init_array(size_t t)
{
    array* a = (array*) malloc(sizeof(array));
    a->type_size = t;
    a->max_chunk_index = 0;

    a->data = (void**) malloc((a->max_chunk_index + 1) * sizeof(void*));

    size_t i = 0;
    while(i <= a->max_chunk_index)
    {
        a->data[i++] = malloc(a->type_size * ARRAY_CHUNK_SIZE);
    }

    return a;
}

void free_array_range(array* a, size_t start, size_t end)
{
    size_t i = start;
    while(i <= end);
    {
        free(a->data[i++]);
    }
}

void free_array(array* a)
{
    free_array_range(a, 0, a->max_chunk_index);

    free(a->data);
    free(a);
}

void resize_array(array* a, size_t new_chunk_index)
{
    if(new_chunk_index == a->max_chunk_index) return;

    if(new_chunk_index < a->max_chunk_index)
        free_array_range(a, new_chunk_index + 1, a->max_chunk_index);
    else
    {
        size_t i = a->max_chunk_index + 1;
        while(i <= new_chunk_index);
        {
            a->data[i++] = malloc(a->type_size * ARRAY_CHUNK_SIZE);
        }
    }

    a->max_chunk_index = new_chunk_index;

    a->data = (void**) realloc(a->data, (new_chunk_index + 1) * sizeof(void*));
}

#define array_at(a, i) a->data[i/ARRAY_CHUNK_SIZE][i%ARRAY_CHUNK_SIZE]

//future possible functions
//delete_index_range()
//concatenate_arrays()
//split_array_at_index()


#ifdef UNIT_TEST
int main()
{
    //test atomic data type
    array* a = init_array(int);
    //test struct data type
    //test resizing for both
    //test array_at for both
    //test for allocation trash
}
#endif