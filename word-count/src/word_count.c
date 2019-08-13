#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <regex.h>

#include "word_count.h"

int _is_already_found(const char *word, word_count_word_t * words);

int word_count(const char *input_text, word_count_word_t * words) {
	int count = 0;
	int already_found;
	int words_index = 0;
	int err_no;

	//char *pattern = "[[:alnum:]]+'?[[:alnum:]]+";
	char *pattern = "[[:alnum:]]\\+'\\?[[:alnum:]]*";
	//char *pattern = "[[:alnum:]]";
	regex_t *regex;

	char buffer[MAX_WORD_LENGTH+1];

	regmatch_t *result;
	int start=0; /* The offset from the beginning of the line */

	printf("input_text = %s\n", input_text);

	/* Make space for the regular expression */
	regex = (regex_t *) malloc(sizeof(regex_t));
	memset(regex, 0, sizeof(regex_t));

	/* Compile the regex */
	if((err_no = regcomp(regex, pattern, 0)) != 0) {
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

	while(regexec(regex, input_text+start, no_sub, result, 0) == 0) /* Found a match */
	{
		printf("\n-- start: %d; end: %d; word = %s", result->rm_so, result->rm_eo, input_text+start);

		strncpy(buffer, input_text+start, (result->rm_eo - result->rm_so));
		printf("buffer = %s\n", buffer);

		if ((already_found = _is_already_found(buffer, words)) != -1) {
			printf("already found buffer = %s\n", buffer);
			words[already_found].count += 1;
		} else {
			printf("NOT already found buffer = %s\n", buffer);
			strncpy(words[words_index].text, buffer, (result->rm_eo - result->rm_so));
			words[words_index].count = 1;

			words_index++;
		}

		start += result->rm_eo; /* Update the offset */
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
