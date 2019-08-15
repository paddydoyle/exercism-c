#include "acronym.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
	char *phrase_copy;
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
	if ((phrase_copy = malloc(sizeof(char) * strlen(phrase))) == 0) {
		fprintf(stderr, "Malloc failed.");
		exit(EXIT_FAILURE);
	}

	for (token = strtok(phrase_copy, delim); token == NULL; token = strtok(NULL, delim)) {
		abbrev[i++] = token[0];
	}

	abbrev[i] = '\0';

	// Clean up.
	free(phrase_copy);

	return abbrev;
}
