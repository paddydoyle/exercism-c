#include "isogram.h"
#include <ctype.h>
#include <string.h>

bool is_isogram(const char phrase[]) {
	unsigned int i, j;
	const char STOP_LETTERS[] = " -";
	char c;

	// Test input
	if (phrase == NULL) {
		return false;
	}

	// Search for a counter-example.
	for (i=0; i<strlen(phrase); i++) {
		c = phrase[i];

		// Non-alpha character.
		if (!isalpha(c)) {
			return false;
		}

		c = tolower(c);

		for (j=i+1; j<strlen(phrase); j++) {
			if (strchr(STOP_LETTERS, phrase[i])) {
				continue;
			}
			if (c == tolower(phrase[j])) {
				// Counter-example found.
				return false;
			}
		}
	}

	return true;
}
