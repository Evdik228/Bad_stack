
#include<stdio.h>

#include"../headers/stack_implementation.h"
#include"../headers/utilits.h"

//#define is_error(function) ()

int main(int argc, char const *argv[]) {

    FILE * Logfile = fopen("report.txt", "w");
    
    bad_stack stack = {};      
    
    Stack_ctor(&stack, "stack");

    //stack.logFile = Logfile;

    for(int i = 10; i <= 170; i+=10) {
        Stack_push(&stack, i);
    }
   
    

    Stack_pop(&stack);
    

    Dumper(&stack, "stack", "main");
 
    Stack_dtor(&stack);    //error

    return 0;
}
