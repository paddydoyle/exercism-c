#include "armstrong_numbers.h"
#include <math.h>

// Helper function.
int _countDigits(int num);
int _countDigits(int num) {
	int count = 0;

	for (; num > 0; num /= 10) {
		count++;
	}

	return count;
}

bool isArmstrongNumber(int num) {
	int origNum = num;
	int sum = 0;
	int numDigits, digit;

	numDigits = _countDigits(num);

	while (num > 0) {
		digit = num % 10;

		sum += (int)pow(digit, numDigits);

		num /= 10;
	}

	return origNum == sum;
}
