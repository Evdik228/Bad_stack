#include <stdio.h>

#include "headers/utilits.h"
#include "headers/stack_implementation.h"

bool Verification (bad_stack * stack) {

    if (stack == NULL ) {
        printf("error: The pointer to the stack structure is zero!\n");
        return false;
    } 
    if (stack->stack_data == NULL ) {
        printf("error: The pointer to the stack is zero!\n");
        return false;
    }
    if (stack->capacity < stack->size ) {
        printf("error: The current stack size exceeds the maximum!\n");
        return false;
    } 
    if (stack->capacity < STACK_SIZE_DEFAULT) {
        printf("error: The current maximum stack size is less than the allowed one!\n");
        return false;
    } 
    if (stack->size < 0 ) {
        printf("error: The number of the first element of the stack is less than zero!\n");
        return false;
    } 

    return true;
}

void Dumper(bad_stack * stack) {
    
}