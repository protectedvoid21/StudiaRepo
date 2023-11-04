#pragma once
#include <string>

class Number
{
	int *_digitsArr;
	int _digitCount;
	bool _isNegative;

	void convertIntToDigitArray(int value);
	void trimLeadingZeros(Number &number);
	int cmp(const Number &otherNumber);
	int absCmp(const Number &otherNumber);
public:
	Number();
	Number(int value);
	Number(const Number &otherNumber);
	~Number();
	void operator=(const int num);
	void operator=(const Number &otherNumber);
	bool operator==(const Number &otherNumber);
	bool operator>(const Number &otherNumber);
	bool operator>=(const Number &otherNumber);
	bool operator<=(const Number &otherNumber);
	bool operator<(const Number &otherNumber);
	Number operator+(const Number &otherNumber);
	Number operator-(const Number &otherNumber);
	Number operator*(const Number &otherNumber);
	Number operator/(const Number &otherNumber);
	std::string toString();
	std::string displayInfo();

	static const int MAX_DIGIT_VALUE = 9;
	static const int DEFAULT_DIGIT_COUNT = 1;
};

