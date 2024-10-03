#include <stdio.h>

#include "../headers/utilits.h"
#include "../headers/stack_implementation.h"

// TODO: Verificataor can report only about one error
error_types Verification (bad_stack * stack) { \

    if (stack == NULL ) {
        printf("error: The pointer to the stack structure is zero!\n");
        stack->error_code = ZERO_POINTER_STRUCT;
        return ZERO_POINTER_STRUCT;
    }

    if (stack->capacity == 0 && stack->error_code == 0 && stack->stack_data == NULL) {
        return OKEY;
    }

    if (stack->logFile == NULL) {
        fprintf(stack->logFile, "error: Bad file!");
        stack->error_code = FILE_ERR;
        return FILE_ERR;
    }

    if (stack->stack_data == NULL ) {
        fprintf(stack->logFile, "error: The pointer to the stack is zero!\n");
        stack->error_code = ZERO_POINTER_STACK;
        return ZERO_POINTER_STACK;
    }

    if (stack->capacity < stack->size ) {
        fprintf(stack->logFile, "error: The current stack size exceeds the maximum!\n");
        stack->error_code = STACK_OVERFLOW;
        return STACK_OVERFLOW;
    } 

    if (stack->capacity < STACK_SIZE_DEFAULT) {
        fprintf(stack->logFile, "error: The current maximum stack size is less than the allowed one!\n");
        stack->error_code = CAPACITY_ERR;
        return CAPACITY_ERR;
    }

    if (stack->size < 0 ) {
        fprintf(stack->logFile, "error: The number of the first element of the stack is less than zero!\n");
        stack->error_code = SIZE_ERR;
        return SIZE_ERR;
    } 

    if (stack->mother_chicksa1 != CHICKSA_OK || stack->mother_chicksa2 != CHICKSA_OK) {
        fprintf(stack->logFile, "error: Data become bad!\n");
        stack->error_code = BIG_CANARY_DIE;
        return BIG_CANARY_DIE;
    }
    if (*((long long *)(stack->stack_data - sizeof(CHICKSA_OK))) != CHICKSA_OK ||
        *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))) != CHICKSA_OK) {

        fprintf(stack->logFile, "error: Data become bad!\n");
        stack->error_code = SMALL_CANARY_DIE;
        return SMALL_CANARY_DIE;    
    }

    return OKEY;
}

void Dumper(bad_stack * stack, const char * stack_name, const char * function) { // TODO: rename

    fprintf(stack->logFile, "Stack, named $%s$ [%p] from function: %s()\n", stack->stack_name, stack, function);
    fprintf(stack->logFile, "Stack %s {\n", stack_name);

    fprintf(stack->logFile, "Big canary one: %X", stack->mother_chicksa1);
            stack->mother_chicksa2 == CHICKSA_OK ? fprintf(stack->logFile, "[OK]\n") : fprintf(stack->logFile, "[ERR]\n");

    fprintf(stack->logFile, "   1. Capacity: %lu \n", stack->capacity);
    fprintf(stack->logFile, "   2. Size: %lu \n", stack->size);
    fprintf(stack->logFile, "   3. Hash_sum: %lu \n", stack->hash_sum);

    fprintf(stack->logFile, "   4. Last pop element: {");
    fprintf(stack->logFile, PRINTF_SPECIFIER, stack->last_pop_element);
    fprintf(stack->logFile, "}\n");

    fprintf(stack->logFile, "   5. ");
    Print_error(stack);

    fprintf(stack->logFile, "   6. Data[%p] {\n", stack->stack_data);

    fprintf(stack->logFile, "       canary one: %X", *((long long *)(stack->stack_data - sizeof(CHICKSA_OK))));  
          *((long long *)(stack->stack_data - sizeof(CHICKSA_OK))) == CHICKSA_OK ? fprintf(stack->logFile, "[OK]\n") : fprintf(stack->logFile, "[ERR]\n");

    for (size_t i = stack->size; i > 0; i --) {
        fprintf(stack->logFile, "       -[%i] = ", stack->size - i);
        fprintf(stack->logFile, PRINTF_SPECIFIER, *((stack_elem_t *)(stack->stack_data + i * sizeof(stack_elem_t))));
        fprintf(stack->logFile, "\n");
    }
    fprintf(stack->logFile, "       canary two: %X", *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))));
          *((long long *)(stack->stack_data + stack->capacity * sizeof(stack_elem_t))) == CHICKSA_OK ? fprintf(stack->logFile, "[OK]\n") : fprintf(stack->logFile, "[ERR]\n");
    fprintf(stack->logFile,"    }\n");

    fprintf(stack->logFile, "Big canary two: %X", stack->mother_chicksa1);
            stack->mother_chicksa2 == CHICKSA_OK ? fprintf(stack->logFile, "[OK]\n") : fprintf(stack->logFile, "[ERR]\n");
    fprintf(stack->logFile,"}\n");
}

size_t Hash_count(bad_stack * stack) {

    size_t HS1 = 0xDED;
    size_t HS2 = 0xAD;
    size_t total = 0;

    total = stack->capacity * HS1 + stack->size * HS1 + stack->mother_chicksa1 * HS2 + 
            stack->mother_chicksa2 * HS2 + (size_t)(stack->stack_data) * (HS1 + HS2);
    return total;
}

void Print_error(bad_stack * stack) {
    switch (stack->error_code) {

    case OKEY:
        fprintf(stack->logFile, "Error code: okey\n");
        break;

    case ZERO_POINTER_STRUCT:
        fprintf(stack->logFile, "Error code: zero pointer on struct!\n");
        break;

    case ZERO_POINTER_STACK:
        fprintf(stack->logFile, "Error code: zero pointer on stack!\n");
        break;

    case STACK_OVERFLOW:
        fprintf(stack->logFile, "Error code: stack overflow!\n");
        break;

    case HASH_ERR:
        fprintf(stack->logFile, "Error code: hash sum don`t right!\n");
        break;

    case BIG_CANARY_DIE:
        fprintf(stack->logFile, "Error code: data in struct become bad!\n");
        break;

    case SMALL_CANARY_DIE:
        fprintf(stack->logFile, "Error code: data in stack become bad!\n");
        break;

    case SIZE_ERR:
        fprintf(stack->logFile, "Error code: size < 0 \n");
        break;

    case CAPACITY_ERR:
        fprintf(stack->logFile, "Error code: capacity < 0\n");
        break;

    case FILE_ERR:
        fprintf(stack->logFile, "Error code: file not opened!\n");
        break;

    case REALLOC_ERR:
        fprintf(stack->logFile, "Error code: realloc error!\n");
        break;

    default:
        fprintf(stack->logFile, "Error code: error not recognized!\n");
    }
}