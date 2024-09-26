#include<stdio.h>
#include<stdlib.h>

#include"../headers/stack_implementation.h"
#include"../headers/utilits.h"

FILE * Logfile = fopen("report.txt", "w");

bool Stack_ctor(bad_stack * b_stk, size_t size) {
    
    stack_elem_t * data = (stack_elem_t *)calloc(size, sizeof(stack_elem_t));

    if (data != NULL) {

        b_stk->stack_data = data;
        b_stk->capacity = size;

    } else {
        fprintf (Logfile,"Error in memory allocation(Stack_ctor)!\n");
        return false;
    }

    fprintf(Logfile, "stack created!\n");
    return Verification(b_stk);
}


bool Stack_dtor(bad_stack * b_stk) {

    free(b_stk->stack_data);
    fprintf(Logfile, "stack determinate!\n");
    return Verification(b_stk);

}


bool Stack_increase(bad_stack * b_stk) {
    stack_elem_t * new_data = (stack_elem_t *)realloc(b_stk->stack_data, 2 * b_stk->capacity);
    if (new_data != NULL) {
        b_stk->capacity *= 2;
        b_stk->stack_data = new_data;
        return Verification(b_stk);
    } else {
        return false;
    }
}


bool Stack_push(bad_stack * b_stk, stack_elem_t elem_t) {
    b_stk->size += 1; 
    if (b_stk->capacity <= b_stk->size) {

        if (Stack_increase(b_stk)) {
            fprintf(Logfile,"Stack size increased to:%lu \n", b_stk->capacity);

        } else {
            fprintf(Logfile, "Error in increasing stack`s size\n");
            return false;
        }
    }
    *(b_stk->stack_data + b_stk->size) = elem_t;
    fprintf(Logfile,"The element was successfully added to the stack!\n");
    return Verification(b_stk);
}



bool Stack_decrease(bad_stack * b_stk) {
    stack_elem_t * new_data = (stack_elem_t *)realloc(b_stk->stack_data, b_stk->capacity / 2);   //TODO: maby copypast?*
    if (new_data != NULL) {

        b_stk->capacity /= 2;
        b_stk->stack_data = new_data;

        return true;
    } else {
        return false;
    }
}

stack_elem_t Stack_pop(bad_stack * b_stk) {

    if (b_stk->size == 0) {
        fprintf (Logfile,"The stack is empty!\n");
        return 0;
    }
    
    if (b_stk->capacity > b_stk->size * 2 && b_stk->capacity > STACK_SIZE_DEFAULT)  {

        if (Stack_decrease(b_stk)) {
            fprintf(Logfile,"Stack size decreased to:%lu \n", b_stk->capacity);

        } else {
            fprintf(Logfile, "Error in decreasing stack`s size\n");
            return false;
        }
    }
    stack_elem_t elem_out = *(b_stk->stack_data + b_stk->size);
    *(b_stk->stack_data + b_stk->size) = 0;
    b_stk->size--;
    fprintf (Logfile, "The element has left the stack!\n");
    
    return elem_out;
}

void View_stack_data_double(bad_stack * b_stk) {
     fprintf (Logfile, "Stack data: ");
     for (int elem = b_stk->size; elem > 0; elem--) {
        fprintf (Logfile, "%f ", *(b_stk->stack_data + elem));
     }
     fprintf (Logfile, "\n");
}






























