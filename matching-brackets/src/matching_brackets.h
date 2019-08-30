#ifndef MATCHING_BRACKETS_H
#define MATCHING_BRACKETS_H

#include <stdbool.h>
#include <stdlib.h>


// Helper struct: Simple stack structure.
typedef struct stack {
	char *text;
	int size;
	int index;
} stack_t;

// Helper functions for the stack.
stack_t* _create_stack(size_t size);
void _destroy_stack(stack_t *stack);
bool _stack_push(stack_t *stack, char bracket);
bool _stack_pop(stack_t *stack, char *bracket);
bool _stack_is_empty(stack_t *stack);

// Helper function for matching
bool _brackets_match(char opening, char closing);


bool is_paired(const char *input);

#endif
