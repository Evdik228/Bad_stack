// TODO UTILITIES_H
#ifndef  UTILITIES_H
#define  UTILITIES_H

// #pragma once

#include "../headers/stack_implementation.h"

error_types Verification (bad_stack * stack);
void Dumper(bad_stack * stack, const char * stack_name, const char * function);
size_t Hash_count(bad_stack * stack);
void Print_error(bad_stack * stack);

#endif