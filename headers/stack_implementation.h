#ifndef  STACK_IMP_H_
#define  STACK_IMP_H_

#include<stdio.h>

typedef int stack_elem_t;
#define STACK_TYPE() "%d"

const size_t STACK_SIZE_DEFAULT = 20;
const 

enum error_types {
    
    ZERO_POINTER = 0,
    //TODO
};



struct bad_stack {
    double Chicksa1;
    stack_elem_t * stack_data;
    size_t size;
    size_t capacity;
    size_t error_code;
    FILE *logFile;
    double Chicksa2;
};

bool Stack_ctor( bad_stack * b_stk, size_t size);
bool Stack_dtor(bad_stack * b_stk);
bool Stack_push(bad_stack * b_stk, stack_elem_t elem_t);
stack_elem_t Stack_pop(bad_stack * b_stk);
void View_stack_data_double(bad_stack * b_stk);



#endif