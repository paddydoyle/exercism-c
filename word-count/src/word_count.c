#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <regex.h>

#include "word_count.h"

int _is_already_found(const char *word, word_count_word_t * words);
void _safe_strncpy(char *dest, const char *src, size_t n);

int word_count(const char *input_text, word_count_word_t * words) {
	int count = 0;
	int already_found;
	int words_index = 0;
	int err_no;

	//char *pattern = "[[:alnum:]]+'?[[:alnum:]]+";
	char *pattern = "[[:alnum:]]+'?[[:alnum:]]*";
	//char *pattern = "[[:alnum:]]";
	regex_t *regex;

	char buffer[MAX_WORD_LENGTH+1];

	regmatch_t *result;

	printf("input_text = %s\n", input_text);

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

		_safe_strncpy(buffer, input_text+result->rm_so, (result->rm_eo - result->rm_so));
		printf("buffer = '%s'\n", buffer);

		if ((already_found = _is_already_found(buffer, words)) != -1) {
			printf("already found buffer = %s\n", buffer);
			words[already_found].count += 1;
		} else {
			printf("NOT already found buffer = %s\n", buffer);
			_safe_strncpy(words[words_index].text, buffer, (result->rm_eo - result->rm_so));
			words[words_index].count = 1;

			words_index++;
		}

		input_text += result->rm_eo; /* Update the offset */
		count++;
	}

	printf("hi: count: %d\n", count);

	regfree(regex); /* Free the regular expression data structure */
	free(regex);

	return count;
}

// Horrible linear search of array. Dicts are nice.
int _is_already_found(const char *word, word_count_word_t * words) {
	int i;

	for (i=0; i<MAX_WORDS; i++) {
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
