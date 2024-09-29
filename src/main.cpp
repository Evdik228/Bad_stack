
#include<stdio.h>

#include"../headers/stack_implementation.h"

//#define is_error(function) ()

int main(int argc, char const *argv[]) {

    FILE * Logfile = fopen("report.txt", "w");

    bad_stack b_stk = {}; 

    if (!Stack_ctor(&b_stk, STACK_SIZE_DEFAULT)) {     //TODO: Define 
        return 0;
    } 
    if (!Stack_push(&b_stk, 100)) {
        return 0;
    }

    View_stack_data_double(&b_stk);

    if (!Stack_push(&b_stk, 200)) {
        return 0;
    }
    
    if (!Stack_push(&b_stk, 300)) {
        return 0;
    }

    View_stack_data_double(&b_stk);
    
    stack_elem_t elem = Stack_pop(&b_stk);
    elem = Stack_pop(&b_stk);

    View_stack_data_double(&b_stk);

    if (!Stack_dtor(&b_stk)) {
        return 0;
    }
    
    fclose(Logfile);
    return 0;
}
