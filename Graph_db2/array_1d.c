#include <stdio.h>
#include <stdlib.h>
#include "main.h"


Array_1d* array_1d_create(int length)
{
    Array_1d* arr = malloc(sizeof(Array_1d));
    arr->length = length;
    arr->data = calloc(sizeof(int), arr->length);

    return arr;
}

void array_1d_assign_range(Array_1d* arr)
{
    for (int i = 0; i < arr->length; i++)
        arr->data[i] = i;
}

void array_1d_assign_available(Array_1d* arr)
{
  for (int i = 0; i < arr->length; i++)
    arr->data[i] = -1;
}

int array_1d_get(Array_1d* arr, int index)
{
    return arr->data[index];
}

void array_1d_set(Array_1d* arr, int index, int new_value)
{
    arr->data[index] = new_value;
}

void array_1d_resize(Array_1d* arr, int new_length)
{
    int* new_data;
    if (new_data = realloc(arr->data, sizeof(int) * new_length))
    {
        arr->data = new_data;
        arr->length = new_length;
    }
    else
        printf("ERROR: could now reallocate memory\n");
}

void array_1d_print(Array_1d* arr)
{
    for (int i = 0; i < arr->length; i++)
    {
        printf("%d, ", arr->data[i]);
    }
    printf("\n");
}

void array_1d_free(Array_1d* arr)
{
    free(arr->data);
    free(arr);
}




// int main()
// {
//     Array_1d* arr1 = array_1d_create(10);
//     array_1d_print(arr1);

//     printf("\n");

//     array_1d_assign_range(arr1);
//     array_1d_print(arr1);

//     printf("\n");

//     int data;
//     data = array_1d_get(arr1, 1);
//     printf("data: %d\n", data);

//     array_1d_set(arr1, 3, 666);

//     data = array_1d_get(arr1, 3);
//     printf("data: %d\n", data);
//     array_1d_print(arr1);

//     printf("\n");
//     array_1d_print(arr1);

//     array_1d_resize(arr1, 20);
//     array_1d_print(arr1);

//     printf("\n");

//     array_1d_assign_range(arr1);
//     array_1d_print(arr1);

//     array_1d_free(arr1);


//     return 0;
// }