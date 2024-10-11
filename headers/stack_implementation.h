#ifndef  STACK_IMP_H_
#define  STACK_IMP_H_

#include<stdio.h>

typedef int stack_elem_t;
#define PRINTF_SPECIFIER "%d"

const size_t STACK_SIZE_DEFAULT = 16;
const long long CHICKSA_OK = 0XBADDED600DDED;  

enum error_types {
    OKEY                = 0,
    ERROR               = 3,
    ZERO_POINTER_STRUCT = 2,                    //<< 1,  log or  --> |
    ZERO_POINTER_STACK  = 3,
    STACK_OVERFLOW      = 4,
    HASH_ERR            = 5,
    BIG_CANARY_DIE      = 6,
    SMALL_CANARY_DIE    = 7,
    SIZE_ERR            = 8,
    CAPACITY_ERR        = 9,
    FILE_ERR            = 10,
    REALLOC_ERR         = 11,
};

struct bad_stack { // TODO: rename
    long long mother_chicksa1; // TODO: rename

    char* stack_data;
    size_t size;
    size_t capacity;
    error_types error_code;
    FILE *logFile;
    const char *stack_name;
    stack_elem_t last_pop_element;    //TODO: pop result
    size_t hash_sum;

    long long mother_chicksa2;

};

error_types Stack_ctor(bad_stack * stack, const char * stack_name); // TODO: rename
error_types Stack_dtor(bad_stack * stack);
error_types Stack_push(bad_stack * stack, stack_elem_t elem_t);
error_types Stack_pop(bad_stack * stack);
error_types View_stack_data_double(bad_stack * stack);

#endif