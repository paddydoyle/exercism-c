#include "matching_brackets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Indices into the strings below
#define OPENING "[{("
#define CLOSING "]})"
#define BRACKETS "[{()}]"
#define EMPTY_INDEX -1

// Helper struct: Simple stack structure.
typedef struct stack {
	char *text;
	int size;
	int index;
} stack_t;

stack_t* _create_stack(size_t size);
stack_t* _create_stack(size_t size) {
	stack_t *stack;

	// Simple char array stack. Only needs to be half as
	if ((stack = malloc(sizeof(stack_t))) == NULL) {
		// Ran out of memory!
		return false;
	}

	// Simple char array stack. Only needs to be half as
	if ((stack->text = malloc(size + 1)) == NULL) {
		// Ran out of memory!
		return false;
	}

	// Init members.
	stack->size = size;
	stack->index = EMPTY_INDEX;

	// For ease of debug/printing - make it a terminated string
	memset(stack->text, '\0', size + 1);
	printf("malloc ok\n");

	return stack;
}

void _destroy_stack(stack_t *stack);
void _destroy_stack(stack_t *stack) {
	if (stack == NULL) {
		return;
	}

	free (stack->text);
	free (stack);
}

// Helper function: push char to stack
bool _stack_push(stack_t *stack, char bracket);
bool _stack_push(stack_t *stack, char bracket) {
	if (stack->index + 1 >= stack->size) {
		// stack is full!
		return false;
	}

	printf("_stack_push: index = %d\n", stack->index);
	stack->index++;
	printf("_stack_push: index = %d\n", stack->index);
	stack->text[stack->index] = bracket;
	printf("_stack_push: top = %c\n", stack->text[stack->index]);

	return true;
}

// Helper function: pop char from stack
bool _stack_pop(stack_t *stack, char *bracket);
bool _stack_pop(stack_t *stack, char *bracket) {
	if (stack->index == EMPTY_INDEX) {
		// stack is empty
		return false;
	}

	printf("_stack_pop: index = %d\n", stack->index);
	printf("_stack_pop: char = %c\n", stack->text[stack->index]);
	*bracket = stack->text[stack->index];
	printf("_stack_pop: char = %c\n", *bracket);
	stack->index--;
	printf("_stack_pop: index = %d\n", stack->index);

	return true;
}

// Helper function: test for matching brackets.
bool _brackets_match(char opening, char closing);
bool _brackets_match(char opening, char closing) {
	switch (opening) {
		case '[':
			return closing == ']';
		case '{':
			return closing == '}';
		case '(':
			return closing == ')';
		default:
			return false;
	}
}

bool is_paired(const char *input) {
	unsigned int i = 0;
	char popped;
	char *opening, *closing;

	stack_t *stack;
	bool result = true;

	if (input == NULL) {
		printf("NULL input\n");
		return false;
	}

	if (strlen(input) == 0) {
		printf("EMPTY input\n");
		return true;
	}

	stack = _create_stack(strlen(input));

	// Method:
	// Use a stack to push on opening brackets as we find them,
	// and pop closing as we find them.
	// If we pop and the brackets don't match, then it's a
	// counter-example.

	for (i=0; i < strlen(input); i++) {
		printf("i = %d; char = %c\n", i, input[i]);
		// Three cases:
		// - non-bracket
		// - opening bracket
		// - closing bracket

		// Search for opening and closing brackets
		opening = strchr(OPENING, input[i]);
		closing = strchr(CLOSING, input[i]);

		// Ignore non-bracket chars
		if (opening == NULL && closing == NULL) {
			printf("non-bracket char, continue\n");
			continue;
		} else if (opening) {
			// Opening: push to stack
			printf("opening bracket char, pushing\n");
			if (!_stack_push(stack, *opening)) {
				// Stack problems! Abort!
				result = false;
				break;
			}
			printf("opening bracket char: stack = %s\n", stack->text);
		} else if (closing) {
			// Closing: pop from stack and see if they match
			printf("closing bracket char, popping\n");
			if (!_stack_pop(stack, &popped)) {
				// Stack problems! Abort!
				// Tidy up
				_destroy_stack(stack);

				return false;
			}
			printf("opening bracket char: stack = %s\n", stack->text);
			printf("opening bracket char: popped = %c\n", popped);

			// Match?
			if (!_brackets_match(popped, *closing)) {
				printf("COUNTER EXAmple\n");
				// Found counter-example.
				// Tidy up
				_destroy_stack(stack);

				return false;
			}
		}
	}

	// Is the stack empty? If so, we matched everything.
	result = (stack->index == EMPTY_INDEX);

	// Tidy up
	_destroy_stack(stack);

	return result;
}
