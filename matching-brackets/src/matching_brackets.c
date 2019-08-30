#include "matching_brackets.h"
#include <string.h>

// Indices into the strings below
#define OPENING "[{("
#define CLOSING "]})"
#define EMPTY_INDEX -1

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

	return stack;
}

void _destroy_stack(stack_t *stack) {
	if (stack == NULL) {
		return;
	}

	free (stack->text);
	free (stack);
}

// Helper function: push char to stack
bool _stack_push(stack_t *stack, char bracket) {
	if (stack->index + 1 >= stack->size) {
		// stack is full!
		return false;
	}

	stack->index++;
	stack->text[stack->index] = bracket;

	return true;
}

// Helper function: pop char from stack
bool _stack_pop(stack_t *stack, char *bracket) {
	if (stack->index == EMPTY_INDEX) {
		// stack is empty
		return false;
	}

	*bracket = stack->text[stack->index];
	stack->index--;

	return true;
}

// Helper function: is_empty?
bool _stack_is_empty(stack_t *stack) {
	return (stack->index == EMPTY_INDEX);
}

// Helper function: test for matching brackets.
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

/*
 * Methodology:
 * Use a stack to push on opening brackets and pop when a closing bracket
 * is met.
 * If we pop and the brackets don't match, then it's a
 * counter-example.
 */
bool is_paired(const char *input) {
	unsigned int i = 0;
	char popped;
	char *opening, *closing;

	stack_t *stack;
	bool result = true;

	// Simple edge cases.
	if (input == NULL || strlen(input) == 0) {
		return true;
	}

	stack = _create_stack(strlen(input));

	for (i=0; i < strlen(input); i++) {
		// Three cases:
		// - non-bracket
		// - opening bracket
		// - closing bracket

		// Search for opening and closing brackets
		opening = strchr(OPENING, input[i]);
		closing = strchr(CLOSING, input[i]);

		// Ignore non-bracket chars
		if (opening == NULL && closing == NULL) {
			continue;
		} else if (opening) {
			if (!_stack_push(stack, *opening)) {
				// Stack problems! Abort!
				// Tidy up
				_destroy_stack(stack);

				return false;
			}
		} else if (closing) {
			if (!_stack_pop(stack, &popped)) {
				// Stack problems! Abort!
				// Tidy up
				_destroy_stack(stack);

				return false;
			}

			// Match?
			if (!_brackets_match(popped, *closing)) {
				// Found counter-example.
				// Tidy up
				_destroy_stack(stack);

				return false;
			}
		}
	}

	// Is the stack empty? If so, we matched everything.
	result = _stack_is_empty(stack);

	// Tidy up
	_destroy_stack(stack);

	return result;
}
