#include <stdio.h>

#include "headers/utilits.h"
#include "headers/stack_implementation.h"

bool Verification (bad_stack * b_stk) {

    if (b_stk == NULL ) {
        printf("error: The pointer to the stack structure is zero!\n");
        return false;
    } 
    if (b_stk->stack_data == NULL ) {
        printf("error: The pointer to the stack is zero!\n");
        return false;
    }
    if (b_stk->capacity < b_stk->size ) {
        printf("error: The current stack size exceeds the maximum!\n");
        return false;
    } 
    if (b_stk->capacity < STACK_SIZE_DEFAULT) {
        printf("error: The current maximum stack size is less than the allowed one!\n");
        return false;
    } 
    if (b_stk->size < 0 ) {
        printf("error: The number of the first element of the stack is less than zero!\n");
        return false;
    } 

    return true;

}