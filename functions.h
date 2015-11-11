#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.h"
char * create_stack(int);
int delete_stack(int *);
int free_place(int, int);
int stack_empty(int);
void stack_push(char *, int *, char);
char stack_pop(char *, int *);
//int stack_size(int );
void interface(void);
#endif