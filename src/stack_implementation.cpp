#include <stdio.h>
#include <stdlib.h>

// TODO -I compilation flag
#include "../headers/stack_implementation.h"
#include "../headers/utilits.h"

FILE * Logfile = fopen("report.txt", "w");

bool Stack_ctor(bad_stack * stack, size_t size) {
    // TODO varificator
    
    stack_elem_t * data = (stack_elem_t *)calloc(size, sizeof(stack_elem_t));

    if (data == NULL) {
        fprintf (Logfile,"Error in memory allocation(Stack_ctor)!\n");
        return false;
    }

    stack->stack_data = data;
    stack->capacity = size;

    fprintf(Logfile, "stack created!\n");
    return Verification(stack);
}

bool Stack_dtor(bad_stack * stack) {
    if (stack == NULL) {
        return false;
    }

    free(stack->stack_data);
    stack->stack_data = NULL;

    stack->size = 0;
    stack->capacity = 0;

    fprintf(Logfile, "stack determinate!\n");

    return true;
}

bool Stack_increase(bad_stack * stack) {
    // TODO verification

    stack_elem_t * new_data = (stack_elem_t *)realloc(stack->stack_data, 2 * stack->capacity);

    if (new_data == NULL) {
        return false;
    }

    stack->capacity *= 2;
    stack->stack_data = new_data;
    return Verification(stack);
}

// TODO 
//#define PRINT_SPECIFIER "%lf"
//
//void Print_value(stack_elem_t value) {
//    printf(PRINT_SPECIFIER, value);
//}

bool Stack_push(bad_stack * stack, stack_elem_t elem_t) {
    // TODO verify

    stack->size += 1;

    if (stack->capacity <= stack->size) {

        // TODO print log status
        // LOG_INFO(logfile, ...) fprintf(logfile, "[INFO]: " ...)
        if (Stack_increase(stack)) {
            fprintf(Logfile,"Stack size increased to:%lu \n", stack->capacity);
        } else {
            fprintf(Logfile, "Error in increasing stack`s size\n");
            return false;
        }
    }

    *(stack->stack_data + stack->size) = elem_t;

    fprintf(Logfile,"The element was successfully added to the stack!\n");

    return Verification(stack);
}

bool Stack_decrease(bad_stack * stack) {
    stack_elem_t * new_data = (stack_elem_t *)realloc(stack->stack_data, stack->capacity / 2);   //TODO: maby copypast?*
    
    // TODO invert if
    if (new_data == NULL) {
        return false;
    }

    stack->capacity /= 2;
    stack->stack_data = new_data;
    return true;
}

// TODO error code
stack_elem_t Stack_pop(bad_stack * stack) {

    if (stack->size == 0) {
        fprintf (Logfile,"The stack is empty!\n");
        return 0;
    }
    
    if (stack->capacity > stack->size * 2 && stack->capacity > STACK_SIZE_DEFAULT)  {

        if (Stack_decrease(stack)) {
            fprintf(Logfile,"Stack size decreased to:%lu \n", stack->capacity);

        } else {
            fprintf(Logfile, "Error in decreasing stack`s size\n");
            return false;
        }
    }
    stack_elem_t elem_out = *(stack->stack_data + stack->size);
    *(stack->stack_data + stack->size) = 0;
    stack->size--;
    fprintf (Logfile, "The element has left the stack!\n");
    
    return elem_out;
}

void View_stack_data_double(bad_stack * stack) {
    fprintf (Logfile, "Stack data: ");
    for (int elem = stack->size; elem > 0; elem--) {
       fprintf (Logfile, "%f ", *(stack->stack_data + elem));
    }
    fprintf (Logfile, "\n");
}






























