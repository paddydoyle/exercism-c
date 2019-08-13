#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <regex.h>

#include "word_count.h"

int _is_already_found(const char *word, word_count_word_t * words);
void _safe_strncpy(char *dest, const char *src, size_t n);
void _str_tolower(char *str, int len);

int word_count(const char *input_text, word_count_word_t * words) {
	int already_found;
	int words_found = 0;
	int err_no;

	char *pattern = "[[:alnum:]]+('?[[:alnum:]]+)?";
	regex_t *regex;

	char buffer[MAX_WORD_LENGTH+1];

	regmatch_t *result;

	// Umm ok so we're re-using the 'actual' array in all of the tests
	// and have to clear it completely.
	memset(words, 0, MAX_WORDS * sizeof(*words));

	printf("---------------------------------------------------------\ninput_text = %s\n", input_text);
	printf("words[0].text = %s\n", words[0].text);
	printf("words[0].count = %d\n", words[0].count);

	/* Make space for the regular expression */
	regex = (regex_t *) malloc(sizeof(regex_t));
	memset(regex, 0, sizeof(regex_t));

	/* Compile the regex */
	if((err_no = regcomp(regex, pattern, REG_EXTENDED | REG_ICASE)) != 0) {
		perror("Regex failed to compile.\n");
		exit(EXIT_FAILURE);
	}

	printf("hi: %s\n", input_text);

	size_t no_sub = regex->re_nsub+1; /* How many matches are there in a line? */                                                                                                                                        
	printf("hi: %d\n", (int)no_sub);

	if((result = (regmatch_t *) malloc(sizeof(regmatch_t) * no_sub))==0) {
		perror("Not enough memory for regmatch_t.\n");
		exit(EXIT_FAILURE);
	}

	while(regexec(regex, input_text, no_sub, result, 0) == 0) /* Found a match */
	{
		printf("\n-- START: (%s)\n", input_text);
		printf("start: %d; end: %d; word = %s\n", result->rm_so, result->rm_eo, input_text);

		if ((result->rm_eo - result->rm_so) > MAX_WORD_LENGTH) {
			regfree(regex); /* Free the regular expression data structure */
			free(regex);
			return EXCESSIVE_LENGTH_WORD;
		}

		_safe_strncpy(buffer, input_text+result->rm_so, (result->rm_eo - result->rm_so));
		printf("buffer = '%s'\n", buffer);
		_str_tolower(buffer, MAX_WORD_LENGTH);
		printf("buffer NOW = '%s'\n", buffer);

		if ((already_found = _is_already_found(buffer, words)) != -1) {
			printf("already found buffer = %s\n", buffer);
			words[already_found].count += 1;
			printf("already found count = %d\n", words[already_found].count);
		} else {
			printf("NOT already found buffer = %s\n", buffer);
			_safe_strncpy(words[words_found].text, buffer, (result->rm_eo - result->rm_so));
			words[words_found].count = 1;
			printf("NOT already found count = %d\n", words[already_found].count);

			words_found++;
		}

		input_text += result->rm_eo; /* Update the offset */
	}

	printf("hi: words_found: %d\n", words_found);

	regfree(regex); /* Free the regular expression data structure */
	free(regex);

	return words_found;
}

// Horrible linear search of array. Dicts are nice.
int _is_already_found(const char *word, word_count_word_t * words) {
	int i;

	for (i=0; i<MAX_WORDS; i++) {
		// Short-cut the search if possible.
		if (words[i].text[0] == '\0') {
			return -1;
		}

		if (strncasecmp(word, words[i].text, MAX_WORD_LENGTH) == 0) {
			return i;
		}
	}

	return -1;	
}

// Horrible safe string copy, including null termination.
void _safe_strncpy(char *dest, const char *src, size_t n) {
	strncpy(dest, src, n);

	// Properly null terminate.
	dest[n] = '\0';
}

void _str_tolower(char *str, int len) {
	int i;

	for (i=0; i<len; i++) {
		str[i] = tolower(str[i]);
	}
}
