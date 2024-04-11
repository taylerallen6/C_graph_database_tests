#include <stdbool.h>
#include <limits.h>
#include "main.h"


#define AVAILABLE (false)
#define FILLED (true)

Managed_index_array* managed_index_array_create(int total_length)
{
    Managed_index_array* managed_index_array = malloc(sizeof(Managed_index_array));

    managed_index_array->total_length = total_length;
    managed_index_array->current_length = 0;
    managed_index_array->num_used_slots = 0;

    managed_index_array->data = malloc(sizeof(bool) * managed_index_array->total_length);
    for (int i = 0; i < managed_index_array->total_length; i++)
        managed_index_array->data[i] = AVAILABLE;

    managed_index_array->empty_slots = array_reverse_stack_create(managed_index_array->total_length);
    array_reverse_stack_assign_reverse_range(managed_index_array->empty_slots);

    return managed_index_array;
}

void managed_index_array_free(Managed_index_array* managed_index_array)
{
    array_reverse_stack_free(managed_index_array->empty_slots);
    free(managed_index_array->data);
    free(managed_index_array);
}

void managed_index_array_resize(Managed_index_array* managed_index_array, int new_total_length)
{
    managed_index_array->data = realloc(managed_index_array->data, sizeof(bool) * new_total_length);
    for (int i = managed_index_array->total_length; i < new_total_length; i++)
        managed_index_array->data[i] = AVAILABLE;

    int increase_amount = new_total_length - managed_index_array->total_length;
    array_reverse_stack_increase_total_length_refill_reverse_range(managed_index_array->empty_slots, increase_amount);

    managed_index_array->total_length = new_total_length;
}

void managed_index_array_increase_size(Managed_index_array* managed_index_array, int increase_amount)
{   
    int new_total_length = managed_index_array->total_length + increase_amount;
    managed_index_array->data = realloc(managed_index_array->data, sizeof(bool) * new_total_length);
    for (int i = managed_index_array->total_length; i < new_total_length; i++)
        managed_index_array->data[i] = AVAILABLE;

    array_reverse_stack_increase_total_length_refill_reverse_range(managed_index_array->empty_slots, increase_amount);

    managed_index_array->total_length = new_total_length;
}

bool managed_index_array_is_full(Managed_index_array* managed_index_array)
{
    bool is_full = false;
    
    if (managed_index_array->current_length == managed_index_array->total_length)
        is_full = true;
    
    return is_full;
}

bool managed_index_array_slot_is_available(Managed_index_array* managed_index_array, int index)
{
    return (managed_index_array->data[index] == AVAILABLE);
}

bool managed_index_array_index_create(Managed_index_array* managed_index_array, int* output_index)
{
    if (managed_index_array_is_full(managed_index_array))
    {
        printf("ERROR: array is full.\n");
        return false;
    }

    int index;
    if (array_reverse_stack_dequeue(managed_index_array->empty_slots, &index) == false)
    {
        printf("ERROR: empty_slots stack is empty.\n");
        return false;
    }

    if (index >= managed_index_array->num_used_slots)
        managed_index_array->num_used_slots = index+1;

    managed_index_array->data[index] = FILLED;
    managed_index_array->current_length++;

    *output_index = index;

    return true;
}

bool managed_index_array_index_delete(Managed_index_array* managed_index_array, int index)
{
    if (index >= managed_index_array->total_length)
    {
        printf("ERROR: index larger than array size.\n");
        return false;
    }

    int value = managed_index_array->data[index];

    if (value == AVAILABLE)
    {
        printf("ERROR: slot already empty.\n");
        return false;
    }

    managed_index_array->data[index] = AVAILABLE;
    if (array_reverse_stack_enqueue(managed_index_array->empty_slots, index) == false)
        return false;

    managed_index_array->current_length--;

    return true;
}

void managed_index_array_print(Managed_index_array* managed_index_array)
{
    for (int i = 0; i < managed_index_array->num_used_slots; i++)
    {
        if (managed_index_array->data[i] != AVAILABLE)
            printf("%d, ", managed_index_array->data[i]);
    }

    printf("\n");
}

void managed_index_array_print_all(Managed_index_array* managed_index_array)
{
    for (int i = 0; i < managed_index_array->total_length; i++)
        printf("%d, ", managed_index_array->data[i]);

    printf("\n");
}


// int main()
// {
//     int num_slots = 10;

//     Managed_index_array* marr = managed_index_array_create(num_slots);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);

//     int new_index;
//     for (int i = 0; i < 8; i++)
//     {
//         printf("%d\n", i);
//         managed_index_array_index_create(marr, &new_index);

//         printf("stack: ");
//         array_reverse_stack_print(marr->empty_slots);
//         printf("marr: ");
//         managed_index_array_print(marr);
//         managed_index_array_print_all(marr);
//         printf("marr length: %d\n", marr->current_length);
//         printf("marr num_used_slots: %d\n", marr->num_used_slots);
//     }

//     printf("\n");

//     int index;
//     int output;

//     index = 9;
//     managed_index_array_index_delete(marr, index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     index = 4;
//     managed_index_array_index_delete(marr, index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     index = 2;
//     managed_index_array_index_delete(marr, index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     index = 7;
//     managed_index_array_index_delete(marr, index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     index = 8;
//     managed_index_array_index_delete(marr, index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     printf("\n");
    

//     managed_index_array_index_create(marr, &new_index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     managed_index_array_index_create(marr, &new_index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     printf("\n");

    
//     index = 4;
//     managed_index_array_index_delete(marr, index);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     printf("\n");


//     managed_index_array_increase_size(marr, 5);
//     printf("stack: ");
//     array_reverse_stack_print(marr->empty_slots);
//     printf("marr: ");
//     managed_index_array_print(marr);
//     managed_index_array_print_all(marr);
//     printf("marr length: %d\n", marr->current_length);
//     printf("marr num_used_slots: %d\n", marr->num_used_slots);

//     printf("\n");

//     for (int i = 0; i < 9; i++)
//     {
//         managed_index_array_index_create(marr, &new_index);
//         printf("stack: ");
//         array_reverse_stack_print(marr->empty_slots);
//         printf("marr: ");
//         managed_index_array_print(marr);
//         managed_index_array_print_all(marr);
//         printf("marr length: %d\n", marr->current_length);
//         printf("marr num_used_slots: %d\n", marr->num_used_slots);
//     }


//     managed_index_array_free(marr);

//     return 0;
// }