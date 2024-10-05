
#include<stdio.h>

#include"../headers/stack_implementation.h"
#include"../headers/utilits.h"

//#define is_error(function) ()

int main(int argc, char const *argv[]) {

    FILE * Logfile = fopen("report.txt", "w");
    
    bad_stack stack = {};      
    //TODO: another pointer on stack!!
    Stack_ctor(&stack, "stack");

    //stack.logFile = Logfile;

    for(int i = 10; i <= 170; i+=10) {
        Stack_push(&stack, i);
    }

    //Dumper(&stack, "stack_1", "main");

     for(int i = 10; i <= 180; i+=10) {
        Stack_pop(&stack);
    }
 
    Stack_dtor(&stack);    

    return 0;
}
