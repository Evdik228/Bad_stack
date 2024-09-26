#ifndef  STACK_IMP
#define  STACK_IMP

#include<stdio.h>


typedef double stack_elem_t;

const size_t STACK_SIZE_DEFAULT = 20;

struct bad_stack {

    stack_elem_t * stack_data;
    size_t size;
    size_t capacity;

};

bool Stack_ctor( bad_stack * b_stk, size_t size);
bool Stack_dtor(bad_stack * b_stk);
bool Stack_push(bad_stack * b_stk, stack_elem_t elem_t);
stack_elem_t Stack_pop(bad_stack * b_stk);
void View_stack_data_double(bad_stack * b_stk);



#endif