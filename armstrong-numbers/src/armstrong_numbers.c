#include "armstrong_numbers.h"
#include <math.h>
#include <stdio.h>

int _countDigits(int num);
int _countDigits(int num) {
	int count = 0;

	for (; num > 0; num /= 10) {
		count++;
	}

	printf("_countDigits; num = %d; count = %d\n", num, count);

	return count;
}

bool isArmstrongNumber(int num) {
	int origNum = num;
	int sum = 0;
	int numDigits, digit;

	numDigits = _countDigits(num);

	printf("isArm; num = %d; count = %d\n", num, numDigits);

	while (num > 0) {
		digit = num % 10;
		printf("isArm; digit = %d\n", digit);

		sum += (int)pow(digit, numDigits);
		printf("isArm; sum = %d\n", sum);

		num /= 10;

		printf("isArm; num = %d; sum = %d; digit = %d\n", num, sum, digit);
	}

	return origNum == sum;
}
