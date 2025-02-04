#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "image.h"
#include "color.h"
#include "dp.h"

typedef struct Stack {
	int* data;
	int size;
	int capacity;
} Stack;

Stack* init_stack(int capacity);
void push(Stack* stack, int item);
int pop(Stack* stack);
int peek(Stack* stack);
void add(Stack* stack);
void subtract(Stack* stack);
void multiply(Stack* stack);
void divide(Stack* stack);
void mod(Stack* stack);
void not(Stack* stack);
void greater(Stack* stack);
void pointer(Stack* stack, DP *dp);
void swap(Stack* stack, CC *cc);
void duplicate(Stack* stack);
void roll(Stack* stack);

void in_num(Stack* stack);
void in_char(Stack* stack);
void out_num(Stack* stack);
void out_char(Stack* stack);

int isEmpty(Stack* stack);
int size(Stack* stack);
void destroyStack(Stack* stack);
