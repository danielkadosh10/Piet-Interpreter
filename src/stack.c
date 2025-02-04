#include <stdio.h>
#include "stack.h"

Stack* init_stack(int capacity)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (!stack) {
		return NULL;
	}
	stack->data = (int*)malloc(sizeof(int*) * capacity);
	if (!stack->data) {
		free(stack);
		return NULL;
	}
	stack->size = 0;
	stack->capacity = capacity;
	return stack;
}

void push(Stack* stack, int item)
{
	if(stack->size >= stack->capacity) {
		int newCap = stack->capacity * 2;
		int* newData = (int*)realloc(stack->data, sizeof(int*) * newCap);
		if(!newData) {
			printf("Error: push");
			exit(1);
		}
		stack->data = newData;
		stack->capacity = newCap;
	}

	stack->data[stack->size++] = item;
}

int pop(Stack* stack)
{
	if(isEmpty(stack))
		return -1;
	return stack->data[--stack->size];
}

int peek(Stack* stack)
{
	return stack->data[stack->size - 1];
}

void add(Stack* stack)
{
	int a = pop(stack);
	int b = pop(stack);
	push(stack, a + b);
}

void subtract(Stack* stack)
{
	int a = pop(stack);
	int b = pop(stack);
	push(stack, b - a);
}

void multiply(Stack* stack)
{

	int a = pop(stack);
	int b = pop(stack);
	push(stack, a * b);
}


void divide(Stack* stack)
{
	int a = pop(stack);
	int b = pop(stack);
	if (b != 0)
		push(stack, b/a);
	else
	{
		push(stack, b);
		push(stack, a);
	}
}

void mod(Stack* stack)
{	
	int a = pop(stack);
	int b = pop(stack);
	if (b != 0)
	{
		if(b < 0)
			push(stack, (b + a)%a);
		else
			push(stack, b%a);
	}
	else
	{
		push(stack, b);
		push(stack, a);
	}
}


void not(Stack* stack)
{
	int a = pop(stack);
	if(a != 0)
		push(stack, 0);
	else
		push(stack, 1);
}

void greater(Stack* stack)
{
	int a = pop(stack);
	int b = pop(stack);
	if (b > a)
		push(stack, 1);
	else
		push(stack, 0);
}

void pointer(Stack* stack, DP *dp)
{
    int times = pop(stack) % 4;

    if (times < 0) {
        times += 4;  // Convert negative rotation to equivalent positive
    }

    dp->direction = ((dp->direction + times - 1) % 4) + 1;
}

void swap(Stack* stack, CC *cc)
{
    if (pop(stack) % 2 != 0)
        cc->direction ^= 2;
}

void duplicate(Stack* stack)
{
	push(stack, peek(stack));
}

void roll(Stack* stack)
{
    if (stack->size < 2) {
        return;  // Not enough values to perform roll
    }

    int rolls = pop(stack);
    int depth = pop(stack);

    if (depth <= 0 || depth > stack->size) {
        return;  // Ignore invalid depth
    }

    rolls %= depth;  // Optimize the number of rolls (rolling depth times is a no-op)
    if (rolls == 0) {
        return;  // No need to roll if it's effectively zero
    }

    if (rolls > 0) {
        // Move top value downwards by `depth`
        for (int r = 0; r < rolls; r++) {
            int temp = stack->data[stack->size - 1];  // Store top value
            for (int i = stack->size - 1; i >= stack->size - depth + 1; i--) {
                stack->data[i] = stack->data[i - 1];  // Shift values up
            }
            stack->data[stack->size - depth] = temp;  // Place stored value
        }
    } else {
        // Move bottom of depth upwards
        rolls = -rolls;
        for (int r = 0; r < rolls; r++) {
            int temp = stack->data[stack->size - depth];  // Store bottom of depth
            for (int i = stack->size - depth; i < stack->size - 1; i++) {
                stack->data[i] = stack->data[i + 1];  // Shift values down
            }
            stack->data[stack->size - 1] = temp;  // Place stored value on top
        }
    }
}

void in_num(Stack* stack)
{
    return;
}

void in_char(Stack* stack)
{
    return;
}

void out_char(Stack* stack)
{
	char character = (int)pop(stack);
	printf("%c", character);
}

void out_num(Stack* stack)
{
    printf("HERE\n");
	int num = pop(stack);
	printf("%d", num);
}

int isEmpty(Stack* stack)
{
	return stack->size == 0;
}

int size(Stack* stack)
{
	return stack->size;
}

void destroyStack(Stack* stack)
{
    if (stack) {
	if (stack->data) {
		free(stack->data);
	}
	free(stack);
    }
}
