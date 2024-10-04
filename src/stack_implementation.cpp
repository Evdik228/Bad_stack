#include <stdio.h>
#include <stdlib.h>

// TODO -I compilation flag
#include "../headers/stack_implementation.h"
#include "../headers/utilits.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE

#define IS_ERROR(stack, name, function)     \
    if (Verification(stack) != OKEY) {      \
        Dumper(stack, name, "Stack_ctor");  \
        return stack->error_code;           \
    }  

#else

#define IS_ERROR(stack, name, function) ;

#endif
    
error_types Stack_ctor(bad_stack * stack,  const char * stack_name) {

    IS_ERROR(stack, stack->stack_name, "Stack_ctor");

    stack->stack_name = stack_name;    
    stack->capacity = STACK_SIZE_DEFAULT;

    stack->logFile = stdout;
    
    char * data = (char *)calloc(1, stack->capacity * sizeof(stack_elem_t) + 2 * sizeof(CHICKSA_OK));

    if (data == NULL) {
        fprintf (stack->logFile,"Error in memory allocation(Stack_ctor)!\n");
        return ZERO_POINTER_STACK;
    }
    stack->error_code = OKEY;

    stack->stack_data = data;

    *((long long *)stack->stack_data) = CHICKSA_OK; 
    stack->stack_data += sizeof(CHICKSA_OK);
    *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))) = CHICKSA_OK;  
    
    stack->mother_chicksa1 = CHICKSA_OK;
    stack->mother_chicksa2 = CHICKSA_OK;
   
    fprintf(stack->logFile, "stack created!\n");
 
    stack->hash_sum = Hash_count(stack);
  
    IS_ERROR(stack, stack->stack_name, "Stack_ctor");
   
    return OKEY;
}

error_types Stack_dtor(bad_stack * stack) {
    if (stack == NULL) {
        stack->error_code = ZERO_POINTER_STACK;
        return ZERO_POINTER_STRUCT;
    }
    
    free(stack->stack_data - sizeof(CHICKSA_OK));
    stack->stack_data = NULL;

    stack->size = 0;
    stack->capacity = 0;

    fprintf(stack->logFile, "stack determinate!\n");
    stack->logFile = stdout;
    return OKEY;
}

 error_types Stack_increase(bad_stack * stack) {
    IS_ERROR(stack, stack->stack_name, "Stack_increase");

    stack->stack_data -= sizeof(CHICKSA_OK);

    char * new_data = (char *)realloc(stack->stack_data, 2 * stack->capacity * sizeof(stack_elem_t) + sizeof(CHICKSA_OK));

    if (new_data == NULL) {
        stack->error_code = REALLOC_ERR;
        return REALLOC_ERR;
    }

    stack->stack_data = new_data;
    stack->stack_data += sizeof(CHICKSA_OK);
    *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))) = 0;
    stack->capacity *= 2;
    *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))) = CHICKSA_OK;
    
    IS_ERROR(stack, stack->stack_name, "Stack_increase");

    return OKEY;
}

error_types Stack_push(bad_stack * stack, stack_elem_t elem_t) {
    
    IS_ERROR(stack, stack->stack_name, "Stack_push");

    stack->size += 1;

    if (stack->capacity <= stack->size) {    

        if (Stack_increase(stack) == OKEY) {
            fprintf(stack->logFile,"Stack size increased to:%lu \n", stack->capacity);
        } else {
            fprintf(stack->logFile, "Error in increasing stack`s size\n");
            stack->error_code = REALLOC_ERR;
            return REALLOC_ERR; 
        }
    }

    *((stack_elem_t *)(stack->stack_data + stack->size * sizeof(stack_elem_t))) = elem_t;

    fprintf(stack->logFile,"The element was successfully added to the stack!\n");

    IS_ERROR(stack, stack->stack_name, "Stack_push");

    return OKEY;
}

error_types Stack_decrease(bad_stack * stack) {

    IS_ERROR(stack, stack->stack_name, "Stack_decrease");

    stack->capacity /= 2;

    char * new_data = (char *)realloc(stack->stack_data - sizeof(CHICKSA_OK), stack->capacity * sizeof(stack_elem_t) + 2 * sizeof(CHICKSA_OK)); 
    
    if (new_data == NULL) {
        stack->error_code = REALLOC_ERR;
        return REALLOC_ERR;
    }

    stack->stack_data = new_data;
    
    stack->stack_data += sizeof(CHICKSA_OK);
    *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))) = CHICKSA_OK;
    

    return OKEY;
}

error_types Stack_pop(bad_stack * stack) {

    IS_ERROR(stack, stack->stack_name, "Stack_decrease");
    
    if (stack->size == 0) {
        fprintf (stack->logFile,"The stack is empty!\n");
        stack->error_code == ERROR;
        return ERROR;
    }
   
    if (stack->capacity > stack->size * 4 && stack->capacity > STACK_SIZE_DEFAULT)  {

        if (Stack_decrease(stack) == OKEY) {
            fprintf(stack->logFile,"Stack size decreased to:%lu \n", stack->capacity);

        } else {
            fprintf(stack->logFile, "Error in decreasing stack`s size\n");
            Dumper(stack, stack->stack_name, "Stack_decrease");
            return stack->error_code;
        }
    }

    stack_elem_t elem_out = *((stack_elem_t *)(stack->stack_data + stack->size * sizeof(stack_elem_t)));
    stack->last_pop_element = elem_out;

    *((stack_elem_t *)(stack->stack_data + stack->size * sizeof(stack_elem_t))) = 0;        //how to make NULL all box memset

    stack->size--;
    fprintf (stack->logFile, "The element has left the stack!\n");
    
    IS_ERROR(stack, stack->stack_name, "Stack_decrease");

    return OKEY;
}
/*
error_types View_stack_data_double(bad_stack * stack) {

    IS_ERROR(stack, stack->stack_name, "View_stack_data_double(bad_stack");

    fprintf (stack->logFile, "Stack data: ");

    for (int elem = stack->size; elem > 0; elem--) {
       fprintf (stack->logFile, "%f ", *(stack->stack_data + elem));
    }
    fprintf (stack->logFile, "\n");
}

*/

//TODO: Check null adress(not verificator if null adress);