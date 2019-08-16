#include "pangram.h"

#include <ctype.h>
#include <string.h>

#define N_CHARS 26

#define SET_BIT(mask, pos) (mask |= (1 << (pos)))
#define GET_BIT(mask, pos) ((mask >> (pos)) & 1)


bool is_pangram(const char *sentence) {
	unsigned int i;
	char c;
	// Assuming int is at least 32-bit, to allow for at least
	// 26 bit positions representing 'a' to 'z'.
	unsigned int mask = 0;
	unsigned int pangram_mask = 0;

	// Test for edge case.
	if (sentence == NULL) {
		return false;
	}

	// We want to mark the first 26 bits as 1; simplest way
	// is to set only the 27th bit (or the 26th, when you start
	// counting from 0), and then subtract 1.
	// This could be set as a constant.
	SET_BIT(pangram_mask, N_CHARS);
	pangram_mask--;

	// Search for a counter-example.
	for (i=0; i<strlen(sentence); i++) {
		c = sentence[i];

		// Ignore non-alpha chars.
		if (!isalpha(c)) {
			continue;
		}

		c = tolower(c);

		// Already in the mask?
		if (GET_BIT(mask, c - 'a')) {
			continue;
		}

		// Mark the char as already encountered.
		SET_BIT(mask, c - 'a');
	}

	// We've marked all the chars we found. Are there any holes?
	return mask == pangram_mask;
}
