#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* array_reverse_stack */
typedef struct
{
    int* data;
    int total_length;
    int current_length;
    int head;
} Array_reverse_stack;

Array_reverse_stack* array_reverse_stack_create(int total_length);
void array_reverse_stack_free(Array_reverse_stack* stack);
bool array_reverse_stack_is_full(Array_reverse_stack* stack);
bool array_reverse_stack_is_empty(Array_reverse_stack* stack);
bool array_reverse_stack_enqueue(Array_reverse_stack* stack, int value);
bool array_reverse_stack_dequeue(Array_reverse_stack* stack, int* output);
void array_reverse_stack_assign_range(Array_reverse_stack* stack);
void array_reverse_stack_assign_reverse_range(Array_reverse_stack* stack);
void array_reverse_stack_print(Array_reverse_stack* stack);
void array_reverse_stack_increase_total_length(Array_reverse_stack* stack, int increase_amount);
void array_reverse_stack_increase_total_length_refill_reverse_range(Array_reverse_stack* stack, int increase_amount);


/* array_1d */
typedef struct
{
  int* data;
  int length; 
} Array_1d;

Array_1d* array_1d_create(int length);
void array_1d_assign_range(Array_1d* arr);
void array_1d_assign_available(Array_1d* arr);
int array_1d_get(Array_1d* arr, int index);
void array_1d_set(Array_1d* arr, int index, int new_value);
void array_1d_resize(Array_1d* arr, int new_length);
void array_1d_print(Array_1d* arr);
void array_1d_free(Array_1d* arr);


/* managed_index_array */
typedef struct
{
    bool* data;
    Array_reverse_stack* empty_slots;
    int total_length;
    int current_length;
    int num_used_slots;
} Managed_index_array;

Managed_index_array* managed_index_array_create(int total_length);
void managed_index_array_free(Managed_index_array* managed_index_array);
void managed_index_array_resize(Managed_index_array* managed_index_array, int new_total_length);
void managed_index_array_increase_size(Managed_index_array* managed_index_array, int increase_amount);
bool managed_index_array_is_full(Managed_index_array* managed_index_array);
bool managed_index_array_slot_is_available(Managed_index_array* managed_index_array, int index);
bool managed_index_array_index_create(Managed_index_array* managed_index_array, int* output_index);
bool managed_index_array_index_delete(Managed_index_array* managed_index_array, int index);
void managed_index_array_print(Managed_index_array* managed_index_array);
void managed_index_array_print_all(Managed_index_array* managed_index_array);


/* managed_int_array */
typedef struct
{
    int* data;
    Array_reverse_stack* empty_slots;
    int total_length;
    int current_length;
    int num_used_slots;
} Managed_int_array;

Managed_int_array* managed_int_array_create(int total_length);
void managed_int_array_free(Managed_int_array* managed_int_array);
void managed_int_array_resize(Managed_int_array* managed_int_array, int new_total_length);
void managed_int_array_increase_size(Managed_int_array* managed_int_array, int increase_amount);
bool managed_int_array_is_full(Managed_int_array* managed_int_array);
bool managed_int_array_slot_is_available(Managed_int_array* managed_int_array, int index);
bool managed_int_array_insert(Managed_int_array* managed_int_array, int value);
bool managed_int_array_unique_insert(Managed_int_array* managed_int_array, int value);
bool managed_int_array_remove(Managed_int_array* managed_int_array, int* output, int index);
void managed_int_array_print(Managed_int_array* managed_int_array);
void managed_int_array_print_all(Managed_int_array* managed_int_array);