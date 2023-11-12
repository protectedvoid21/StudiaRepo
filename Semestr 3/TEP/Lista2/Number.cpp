#include "Number.h"

void Number::convertIntToDigitArray(int value)
{
	if (value == 0)
	{
		_digitCount = 1;
		_digitsArr = new int[_digitCount];
		_digitsArr[0] = 0;
		return;
	}

	_isNegative = value < 0;
	value = abs(value);

	int temp = value;
	_digitCount = 0;
	while (temp > 0)
	{
		temp /= NUMERIC_BASE;
		_digitCount++;
	}
	temp = value;

	_digitsArr = new int[_digitCount];
	int i = 0;
	while (temp > 0)
	{
		_digitsArr[i] = temp % NUMERIC_BASE;
		temp /= NUMERIC_BASE;
		i++;
	}
}

void Number::trimLeadingZeros(Number &number)
{
	int zeroDigitCount = 0;
	while (number._digitsArr[zeroDigitCount] == 0)
	{
		zeroDigitCount++;
	}
	int *trimmedArr = new int[number._digitCount - zeroDigitCount];

	for (int j = 0; j < number._digitCount - zeroDigitCount; j++)
	{
		trimmedArr[j] = number._digitsArr[zeroDigitCount + j];
	}
	number._digitCount -= zeroDigitCount;
	delete[] number._digitsArr;

	number._digitsArr = trimmedArr;
}

Number::Number(const Number &otherNumber)
{
	_isNegative = otherNumber._isNegative;
	_digitCount = otherNumber._digitCount;
	_digitsArr = new int[otherNumber._digitCount];
	for (int i = 0; i < otherNumber._digitCount; i++)
	{
		_digitsArr[i] = otherNumber._digitsArr[i];
	}
}

Number::Number(int *digitsArr, int digitCount, bool isNegative)
{
	_digitsArr = digitsArr;
	_digitCount = digitCount;
	_isNegative = isNegative;
}

Number::Number()
{
	_isNegative = false;
	_digitCount = DEFAULT_DIGIT_COUNT;
	_digitsArr = new int[_digitCount];
	_digitsArr[0] = 0;
}

Number::Number(int value)
{
	convertIntToDigitArray(value);
}

Number::~Number()
{
	delete[] _digitsArr;
}

void Number::operator=(const int &num)
{
	convertIntToDigitArray(num);
}

void Number::operator=(const Number &otherNumber)
{
	_isNegative = otherNumber._isNegative;
	_digitCount = otherNumber._digitCount;
	_digitsArr = new int[_digitCount];
	for (int i = 0; i < _digitCount; i++)
	{
		_digitsArr[i] = otherNumber._digitsArr[i];
	}
}

int Number::cmp(const Number &otherNumber)
{
	if (_isNegative != otherNumber._isNegative)
	{
		return _isNegative ? -1 : 1;
	}

	if (_digitCount != otherNumber._digitCount)
	{
		if (_isNegative)
		{
			return _digitCount > otherNumber._digitCount ? -1 : 1;
		}
		return _digitCount > otherNumber._digitCount ? 1 : -1;
	}

	for (int i = _digitCount - 1; i >= 0; i--)
	{
		if (_digitsArr[i] != otherNumber._digitsArr[i])
		{
			int compareResult = _digitsArr[i] > otherNumber._digitsArr[i] ? 1 : -1;
			return compareResult * (_isNegative ? -1 : 1);
		}
	}

	return 0;
}

int Number::absCmp(const Number &otherNumber)
{
	if (_digitCount != otherNumber._digitCount)
	{
		return _digitCount > otherNumber._digitCount ? 1 : -1;
	}

	for (int i = _digitCount - 1; i >= 0; i--)
	{
		if (_digitsArr[i] != otherNumber._digitsArr[i])
		{
			return _digitsArr[i] > otherNumber._digitsArr[i] ? 1 : -1;
		}
	}

	return 0;
}

bool Number::operator!=(const Number &otherNumber)
{
	return cmp(otherNumber) != 0;
}

bool Number::operator==(const Number &otherNumber)
{
	return cmp(otherNumber) == 0;
}

bool Number::operator>(const Number &otherNumber)
{
	return cmp(otherNumber) > 0;
}

bool Number::operator>=(const Number &otherNumber)
{
	return cmp(otherNumber) >= 0;
}

bool Number::operator<=(const Number &otherNumber)
{
	return cmp(otherNumber) <= 0;
}

bool Number::operator<(const Number &otherNumber)
{
	return cmp(otherNumber) < 0;
}

Number Number::operator+(const Number &otherNumber)
{
	if (_isNegative != otherNumber._isNegative)
	{
		Number otherNumberCopy = otherNumber;
		otherNumberCopy._isNegative = !otherNumber._isNegative;
		return *this - otherNumberCopy;
	}

	int newDigitCount = _digitCount > otherNumber._digitCount ? _digitCount : otherNumber._digitCount;
	int *sumArr = new int[newDigitCount];

	int sumExcess = 0;

	for (int i = 0; i < newDigitCount; i++)
	{
		int firstAdd = i < _digitCount ? _digitsArr[i] : 0;
		int secondAdd = i < otherNumber._digitCount ? otherNumber._digitsArr[i] : 0;

		int digitSum = firstAdd + secondAdd + sumExcess;

		if (digitSum > MAX_DIGIT_VALUE)
		{
			sumExcess = 1;
			digitSum -= NUMERIC_BASE;
		}
		else
		{
			sumExcess = 0;
		}
		sumArr[i] = digitSum;
	}

	if (sumExcess > 0)
	{
		newDigitCount++;
		int *sumArrWithExcess = new int[newDigitCount];
		for (int i = 0; i < newDigitCount - 1; i++)
		{
			sumArrWithExcess[i] = sumArr[i];
		}
		sumArrWithExcess[newDigitCount - 1] = sumExcess;

		delete[] sumArr;
		sumArr = sumArrWithExcess;
	}

	int absCompareResult = absCmp(otherNumber);

	return Number(sumArr, newDigitCount, (absCompareResult > 0 && _isNegative) || (absCompareResult < 0 && otherNumber._isNegative));
}

Number Number::operator-(const Number &otherNumber)
{
	int absCompareResult = absCmp(otherNumber);

	Number *biggerNumber = this;
	Number *smallerNumber = (Number *)&otherNumber;
	bool swapped = false;

	if (absCompareResult < 0)
	{
		swapped = true;
		biggerNumber = (Number *)&otherNumber;
		smallerNumber = this;

		if (biggerNumber->_isNegative)
		{
			if (!smallerNumber->_isNegative)
			{
				biggerNumber->_isNegative = false;
				return *biggerNumber + *smallerNumber;
			}
			smallerNumber->_isNegative = false;
		}
		else if (smallerNumber->_isNegative)
		{
			smallerNumber->_isNegative = false;
			Number result = *biggerNumber + *smallerNumber;
			result._isNegative = true;
			return result;
		}
	}

	int maxSize = biggerNumber->_digitCount;
	int *resultDigits = new int[maxSize];
	int borrow = 0;

	for (int i = 0; i < maxSize; i++)
	{
		int firstDigit = (i < biggerNumber->_digitCount) ? biggerNumber->_digitsArr[i] : 0;
		int secondDigit = (i < smallerNumber->_digitCount) ? smallerNumber->_digitsArr[i] : 0;

		int diff = firstDigit - secondDigit - borrow;
		if (diff < 0)
		{
			diff += NUMERIC_BASE;
			borrow = 1;
		}
		else
		{
			borrow = 0;
		}

		resultDigits[i] = diff;
	}

	int resultSize = maxSize;
	while (resultSize > 1 && resultDigits[resultSize - 1] == 0)
	{
		--resultSize;
	}

	return Number(resultDigits, resultSize, swapped ? !biggerNumber->_isNegative : biggerNumber->_isNegative);
}

Number Number::operator*(const Number &otherNumber)
{
	int newDigitCount = _digitCount + otherNumber._digitCount;
	int *productArr = new int[newDigitCount];

	for (int i = 0; i < newDigitCount; i++)
	{
		productArr[i] = 0;
	}

	for (int i = 0; i < _digitCount; i++)
	{
		for (int j = 0; j < otherNumber._digitCount; j++)
		{
			productArr[i + j] += _digitsArr[i] * otherNumber._digitsArr[j];
		}
	}

	for (int i = 0; i < newDigitCount - 1; i++)
	{
		productArr[i + 1] += productArr[i] / NUMERIC_BASE;
		productArr[i] %= NUMERIC_BASE;
	}

	if (productArr[newDigitCount - 1] == 0)
	{
		newDigitCount--;
	}

	return Number(productArr, newDigitCount, _isNegative != otherNumber._isNegative);
}

Number Number::operator/(const Number &otherNumber)
{
	if (otherNumber.isZero())
	{
		return Number();
	}

	int newDigitCount = _digitCount - otherNumber._digitCount + 1;
	int *quotientArr = new int[newDigitCount];

	for (int i = 0; i < newDigitCount; i++)
	{
		quotientArr[i] = 0;
	}

	Number tempNumber = *this;
	Number tempOtherNumber = otherNumber;

	tempNumber._isNegative = false;
	tempOtherNumber._isNegative = false;

	for (int i = 0; i < newDigitCount; i++)
	{
		while (tempNumber >= tempOtherNumber)
		{
			tempNumber = tempNumber - tempOtherNumber;
			quotientArr[i]++;
			if (quotientArr[i] == MAX_DIGIT_VALUE + 1)
			{
				quotientArr[i] = 0;
				quotientArr[i + 1]++;
			}
		}
	}

	return Number(quotientArr, newDigitCount, _isNegative != otherNumber._isNegative);
}

Number Number::mod(const Number &otherNumber, Number **divisionResult)
{
	int newDigitCount = _digitCount - otherNumber._digitCount + 1;
	int *quotientArr = new int[newDigitCount];

	for (int i = 0; i < newDigitCount; i++)
	{
		quotientArr[i] = 0;
	}

	Number moduloNumber = *this;
	Number tempOtherNumber = otherNumber;

	moduloNumber._isNegative = false;
	tempOtherNumber._isNegative = false;

	for (int i = 0; i < newDigitCount; i++)
	{
		while (moduloNumber >= tempOtherNumber)
		{
			moduloNumber = moduloNumber - tempOtherNumber;
			quotientArr[i]++;
			if (quotientArr[i] == MAX_DIGIT_VALUE + 1)
			{
				quotientArr[i] = 0;
				quotientArr[i + 1]++;
			}
		}
	}

	int leadingZeroCount = 0;
	for (int i = 0; i < newDigitCount; i++)
	{
		if (quotientArr[i] == 0)
		{
			leadingZeroCount++;
		}
	}
	newDigitCount -= leadingZeroCount;
	int *quotientWithoutZero = new int[newDigitCount];
	for (int i = 0; i < newDigitCount; i++)
	{
		quotientWithoutZero[i] = quotientArr[i + leadingZeroCount];
	}
	delete[] quotientArr;

	*divisionResult = new Number(quotientWithoutZero, newDigitCount, false);
	return moduloNumber;
}

bool Number::isZero() const
{
	return _digitCount == 1 && _digitsArr[0] == 0;
}

std::string Number::toString()
{
	std::string text = _isNegative ? "-" : "";
	for (int i = _digitCount - 1; i >= 0; i--)
	{
		text += std::to_string(_digitsArr[i]);
	}
	return text;
}
