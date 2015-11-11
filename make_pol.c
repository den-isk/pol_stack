#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "functions.h"
#include <errno.h>
int stack_size;
void check_op_stack(char *num, char *op, int *num_p, int *op_p, char data)
{
	char countainer=0;
	if (!stack_empty(*op_p))
	{
		stack_push(op, op_p, data);
	}	
	else
	{
		switch(data)
		{
			case '^':
				stack_push(op, op_p, data);
				break;
			case '(':
				stack_push(op, op_p, data);
				break;
			case '*':
				while(1)
				{

					countainer=stack_pop(op, op_p);
					if((countainer == '*') || (countainer == '/'))
						stack_push(num, num_p, countainer);
					else
					{
						stack_push(op, op_p, countainer);
						stack_push(op, op_p, data);
						break;
					}
				}
				break;
			case '/':
				while(1)
				{
					countainer=stack_pop(op, op_p);
					if((countainer == '*') || (countainer == '/'))
						stack_push(num, num_p, countainer);
					else
					{
						stack_push(op, op_p, countainer);
						stack_push(op, op_p, data);
						break;
					}
				}
				break;
			case '+':
				while(1)
				{
					countainer=stack_pop(op, op_p);
					if((countainer == '-') || (countainer == '+'))
						stack_push(num, num_p, countainer);
					else
					{
						stack_push(op, op_p, countainer);
						stack_push(op, op_p, data);
						break;
					}
				}
				break;
			case '-':
				while(1)
				{
					countainer=stack_pop(op, op_p);
					if((countainer == '-') || (countainer == '+'))
						stack_push(num, num_p, countainer);
					else
					{
						stack_push(op, op_p, countainer);
						stack_push(op, op_p, data);
						break;
					}
				}
				break;
			case ')':
				while(1)
				{
					countainer=stack_pop(op, op_p);
					if(countainer != '(')
					{
						stack_push(num, num_p, countainer);
					}
					else
						break;
				}			
				break;
				
		}
	}
}
int main()
{
	char *num=NULL, *op=NULL; /* pointers for stack of numbers and stack of operations */
	size_t n=0; /* for getline() */
	char *buffer=NULL; /* for getline() */
	int str_len=0; /* entered string length */
	int i; /* counter */
	int num_p=-1;
	int op_p=-1; /* stack's pointers*/
	int countainer = 0;

	str_len = getline(&buffer, &n, stdin) - 1;/**/
	num = create_stack(str_len+1);
	op = create_stack(str_len+1);
	stack_size = str_len;

	for(i=0; i<str_len; i++)
	{
		if((buffer[i] >='0')&&(buffer[i] <= '9'))
			stack_push(num, &num_p, buffer[i]);
		else 
		if ((buffer[i] >= '(')&&(buffer[i] <= '/')&&(buffer[i] != ',')&&(buffer[i] != '.')||(buffer[i] == '^'))
		check_op_stack(num, op, &num_p, &op_p, buffer[i]);
		//printf("OP_P is %d\n", op_p);
	}
	num[str_len]='\0';
	while(stack_empty(op_p))
	{
		stack_push(num, &num_p, stack_pop(op, &op_p));
	}
	printf("%s\n", num);
	free(buffer);
	return 0;
}