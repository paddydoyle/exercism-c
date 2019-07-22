#include "isogram.h"
#include <string.h>

bool is_isogram(const char phrase[]) {
	unsigned int i, j;
	const char STOP_LETTERS[] = " -";

	// Test input
	if (phrase == NULL) {
		return false;
	}

	// Search for a counter-example.
	for (i=0; i<strlen(phrase); i++) {
		for (j=i+1; j<strlen(phrase); j++) {
			if (strchr(STOP_LETTERS, phrase[i])) {
				continue;
			}
			if (phrase[i] == phrase[j]) {
				// Counter-example found.
				return false;
			}
		}
	}

	return true;
}
