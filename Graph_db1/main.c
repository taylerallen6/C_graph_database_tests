#include "main.h"


int main()
{
    int num_slots = 10;

    Managed_index_array* managed_index_arr = managed_index_array_create(num_slots);
    float weights[num_slots];

    Managed_int_array* connections_arrs[num_slots];
    int num_connections = 5;
    
    for (int i = 0; i < num_slots; i++)
    {
        connections_arrs[i] = managed_int_array_create(num_connections);
        managed_int_array_print_all(connections_arrs[i]);
    }
    


    int new_index;
    managed_index_array_index_create(managed_index_arr, &new_index);
    weights[new_index] = 315.52;

    managed_index_array_index_create(managed_index_arr, &new_index);
    weights[new_index] = 9385.52;

    managed_index_array_index_create(managed_index_arr, &new_index);
    weights[new_index] = 33805.2;

    managed_index_array_index_create(managed_index_arr, &new_index);
    weights[new_index] = 564.52;

    managed_index_array_index_create(managed_index_arr, &new_index);
    weights[new_index] = 87363.2;


    for (int i = 0; i < managed_index_arr->num_used_slots; i++)
    {
        if (managed_index_array_slot_is_available(managed_index_arr, i) == false)
            printf("%f, ", weights[i]);
    }
    printf("\n");
    

    managed_index_array_index_delete(managed_index_arr, 2);

    for (int i = 0; i < managed_index_arr->num_used_slots; i++)
    {
        if (managed_index_array_slot_is_available(managed_index_arr, i) == false)
            printf("%f, ", weights[i]);
    }
    printf("\n");


    
    managed_int_array_unique_insert(connections_arrs[0], 1);
    managed_int_array_unique_insert(connections_arrs[0], 2);
    managed_int_array_unique_insert(connections_arrs[1], 2);
    managed_int_array_unique_insert(connections_arrs[1], 2);

    for (int i = 0; i < 7; i++)
    {
        managed_int_array_unique_insert(connections_arrs[3], i);
    }
    

    for (int i = 0; i < managed_index_arr->num_used_slots; i++)
    {
        if (managed_index_array_slot_is_available(managed_index_arr, i) == false)
            managed_int_array_print_all(connections_arrs[i]);
    }
    printf("\n");


    return 0;
}