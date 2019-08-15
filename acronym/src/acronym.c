#include "acronym.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
	char *phrase_copy = NULL;
	char *token;
	const char *delim = " -";
	char *abbrev = NULL;
	int i = 0;

	if (phrase == NULL || strlen(phrase) == 0) {
		return NULL;
	}

	// For result string
	if ((abbrev = malloc(sizeof(char) * strlen(phrase))) == 0) {
		fprintf(stderr, "Malloc failed.");
		exit(EXIT_FAILURE);
	}

	// strtok destroys the input string, which is declared as 'const' here
	if ((phrase_copy = malloc(sizeof(char) * strlen(phrase) + 1)) == 0) {
		fprintf(stderr, "Malloc failed.");
		exit(EXIT_FAILURE);
	}

	strncpy(phrase_copy, phrase, strlen(phrase));

	token = strtok(phrase_copy, delim);

	while (token != NULL) {
		if (token == NULL) {
			break;
		}
		abbrev[i++] = toupper(token[0]);

		token = strtok(NULL, delim);
	}

	abbrev[i] = '\0';

	// Clean up.
	free(phrase_copy);

	return abbrev;
}
