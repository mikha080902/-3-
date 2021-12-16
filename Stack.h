#pragma once
#include <cstdlib>
#define STACK_INIT_SIZE 10000000

typedef struct Stack {
	size_t size;
	size_t limit;
	int* data;
} Stack;

Stack* createStack() {
	Stack* tmp = (Stack*)malloc(sizeof(Stack));
	tmp->limit = STACK_INIT_SIZE;
	tmp->size = 0;
	tmp->data = (int*)malloc(tmp->limit * sizeof(int));
	return tmp;
}

void freeStack(Stack** s) {
	free((*s)->data);
	free(*s);
	*s = NULL;
}

void push(Stack* s, int item) {
	if (s->size >= s->limit) {
		s->limit *= 2;
		s->data = (int*)realloc(s->data, s->limit * sizeof(int));
	}
	s->data[s->size++] = item;
}

int pop(Stack* s) {
	if (s->size == 0) {
		exit(7);
	}
	s->size--;
	return s->data[s->size];
}