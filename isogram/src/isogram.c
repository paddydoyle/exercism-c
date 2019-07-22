#include "isogram.h"
#include <ctype.h>
#include <string.h>

bool is_isogram(const char phrase[]) {
	unsigned int i, j;
	const char STOP_CHARS[] = " -";
	char c;

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

		for (j=i+1; j<strlen(phrase); j++) {
			if (strchr(STOP_CHARS, phrase[j])) {
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
