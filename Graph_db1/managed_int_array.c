#include <stdbool.h>
#include <limits.h>
#include "main.h"


#define AVAILABLE (-1)

Managed_int_array* managed_int_array_create(int total_length)
{   
    Managed_int_array* managed_int_array = malloc(sizeof(Managed_int_array));

    managed_int_array->total_length = total_length;
    managed_int_array->current_length = 0;
    managed_int_array->num_used_slots = 0;

    managed_int_array->data = malloc(sizeof(int) * managed_int_array->total_length);
    for (int i = 0; i < managed_int_array->total_length; i++)
        managed_int_array->data[i] = AVAILABLE;

    managed_int_array->empty_slots = array_reverse_stack_create(managed_int_array->total_length);
    array_reverse_stack_assign_reverse_range(managed_int_array->empty_slots);

    return managed_int_array;
}

void managed_int_array_free(Managed_int_array* managed_int_array)
{
    array_reverse_stack_free(managed_int_array->empty_slots);
    free(managed_int_array->data);
    free(managed_int_array);
}

void managed_int_array_resize(Managed_int_array* managed_int_array, int new_total_length)
{
    managed_int_array->data = realloc(managed_int_array->data, sizeof(int) * new_total_length);
    for (int i = managed_int_array->total_length; i < new_total_length; i++)
        managed_int_array->data[i] = AVAILABLE;

    int increase_amount = new_total_length - managed_int_array->total_length;
    array_reverse_stack_increase_total_length_refill_reverse_range(managed_int_array->empty_slots, increase_amount);

    managed_int_array->total_length = new_total_length;
}

void managed_int_array_increase_size(Managed_int_array* managed_int_array, int increase_amount)
{   
    int new_total_length = managed_int_array->total_length + increase_amount;
    managed_int_array->data = realloc(managed_int_array->data, sizeof(int) * new_total_length);
    for (int i = managed_int_array->total_length; i < new_total_length; i++)
        managed_int_array->data[i] = AVAILABLE;

    array_reverse_stack_increase_total_length_refill_reverse_range(managed_int_array->empty_slots, increase_amount);

    managed_int_array->total_length = new_total_length;
}

bool managed_int_array_is_full(Managed_int_array* managed_int_array)
{
    bool is_full = false;
    
    if (managed_int_array->current_length == managed_int_array->total_length)
        is_full = true;
    
    return is_full;
}

bool managed_int_array_slot_is_available(Managed_int_array* managed_int_array, int index)
{
    return (managed_int_array->data[index] == AVAILABLE);
}

bool managed_int_array_insert(Managed_int_array* managed_int_array, int value)
{
    if (managed_int_array_is_full(managed_int_array))
    {
        printf("ERROR: array is full. Increasing size.\n");
        managed_int_array_increase_size(managed_int_array, 5);
        // return false;
    }

    int index;
    if (array_reverse_stack_dequeue(managed_int_array->empty_slots, &index) == false)
    {
        printf("ERROR: stack error.\n");
        return false;
    }

    if (index >= managed_int_array->num_used_slots)
        managed_int_array->num_used_slots = index+1;

    managed_int_array->data[index] = value;
    managed_int_array->current_length++;

    return true;
}

bool managed_int_array_unique_insert(Managed_int_array* managed_int_array, int value)
{
    for (int i = 0; i < managed_int_array->num_used_slots; i++)
    {
        if (managed_int_array->data[i] != AVAILABLE)
        {
            if (managed_int_array->data[i] == value)
            {
                printf("ERROR: already exists.\n");
                return false;
            }
        }
    }

    return managed_int_array_insert(managed_int_array, value);
}

bool managed_int_array_remove(Managed_int_array* managed_int_array, int* output, int index)
{
    if (index >= managed_int_array->total_length)
    {
        printf("ERROR: index larger than array size.\n");
        return false;
    }

    int value = managed_int_array->data[index];

    if (value == AVAILABLE)
    {
        printf("ERROR: slot already empty.\n");
        return false;
    }

    *output = value;
    managed_int_array->data[index] = AVAILABLE;
    if (array_reverse_stack_enqueue(managed_int_array->empty_slots, index) == false)
        return false;

    managed_int_array->current_length--;

    return true;
}

void managed_int_array_print(Managed_int_array* managed_int_array)
{
    for (int i = 0; i < managed_int_array->num_used_slots; i++)
    {
        if (managed_int_array->data[i] != AVAILABLE)
            printf("%d, ", managed_int_array->data[i]);
    }

    printf("\n");
}

void managed_int_array_print_all(Managed_int_array* managed_int_array)
{
    for (int i = 0; i < managed_int_array->total_length; i++)
        printf("%d, ", managed_int_array->data[i]);

    printf("\n");
}


// int main()
// {
//     int num_slots = 10;

//     Managed_int_array* marr = managed_int_array_create(num_slots);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_int_array_print(marr);

//     for (int i = 0; i < 8; i++)
//     {
//         printf("%d\n", i);
//         managed_int_array_insert(marr, i);

//         printf("stack: ");
//         array_reverse_stack_print(marr->empty_slots);
//         printf("marr: ");
//         managed_int_array_print(marr);
//         managed_int_array_print_all(marr);
//         printf("marr length: %d\n", marr->current_length);
//         printf("marr num_used_slots: %d\n", marr->num_used_slots);
//     }

//     printf("\n");

//     int index;
//     int output;

//     // index = 9;
//     // managed_int_array_remove(marr, &output, index);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // index = 4;
//     // managed_int_array_remove(marr, &output, index);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // index = 2;
//     // managed_int_array_remove(marr, &output, index);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // index = 7;
//     // managed_int_array_remove(marr, &output, index);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // index = 8;
//     // managed_int_array_remove(marr, &output, index);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // printf("\n");
    

//     // managed_int_array_insert(marr, 44);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // managed_int_array_unique_insert(marr, 44);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // printf("\n");

    
//     // managed_int_array_remove(marr, &output, 4);
//     // printf("stack: ");
//     // array_reverse_stack_print(marr->empty_slots);
//     // printf("marr: ");
//     // managed_int_array_print(marr);
//     // managed_int_array_print_all(marr);
//     // printf("marr length: %d\n", marr->current_length);
//     // printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     // printf("\n");


//     managed_int_array_increase_size(marr, 5);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_int_array_print(marr);
//     managed_int_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     printf("\n");

//     // for (int i = 0; i < 9; i++)
//     // {
//     //     managed_int_array_insert(marr, i);
//     //     printf("stack: ");
//     //     array_reverse_stack_print(marr->empty_slots);
//     //     printf("marr: ");
//     //     managed_int_array_print(marr);
//     //     managed_int_array_print_all(marr);
//     //     printf("marr length: %d\n", marr->current_length);
//     //     printf("marr num_used_slots: %d\n", marr->num_used_slots);
//     // }


//     managed_int_array_unique_insert(marr, 4);
//     managed_int_array_unique_insert(marr, 9);
//     managed_int_array_unique_insert(marr, 2);
//     managed_int_array_unique_insert(marr, 7);


//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_int_array_print(marr);
//     managed_int_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     for (int i = 0; i < 9; i++)
//     {
//         managed_int_array_insert(marr, i);
//         printf("stack: ");
//         array_reverse_stack_print(marr->empty_slots);
//         printf("marr: ");
//         managed_int_array_print(marr);
//         managed_int_array_print_all(marr);
//         printf("marr length: %d\n", marr->current_length);
//         printf("marr num_used_slots: %d\n", marr->num_used_slots);
//     }

//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_int_array_print(marr);
//     managed_int_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     managed_int_array_free(marr);

//     return 0;
// }