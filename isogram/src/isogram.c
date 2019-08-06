#include "isogram.h"
#include <ctype.h>
#include <string.h>

#define SET_BIT(mask, pos) (mask |= (1 << (pos)))
#define GET_BIT(mask, pos) ((mask >> (pos)) & 1)

bool is_isogram(const char phrase[]) {
	unsigned int i;
	const char STOP_CHARS[] = " -";
	char c;
	// Assuming int is at least 32-bit, to allow for at least
	// 26 bit positions representing 'a' to 'z'.
	unsigned int mask = 0;

	// Test for edge case.
	if (phrase == NULL) {
		return false;
	}

	// Search for a counter-example.
	for (i=0; i<strlen(phrase); i++) {
		c = phrase[i];

		// Ignore non-alpha chars.
		if (!isalpha(c) || strchr(STOP_CHARS, phrase[i])) {
			continue;
		}

		c = tolower(c);

		// Already in the mask?
		if (GET_BIT(mask, c - 'a')) {
			return false;
		}

		// Mark the char as already encountered.
		SET_BIT(mask, c - 'a');
	}

	return true;
}
