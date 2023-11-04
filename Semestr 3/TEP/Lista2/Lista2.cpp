#include <iostream>
#include "Number.h"
#include <vector>

struct TestCase
{
	int _first;
	int _second;
	int _expected;
	std::string _name;

	TestCase(int first, int second, int expected, std::string name)
	{
		_first = first;
		_second = second;
		_expected = expected;
		_name = name;
	}

	void run(int actual) const
	{
		display(actual);
		if (_expected != actual)
		{

		}
	}

	void display(int actual) const
	{
		std::string text = _expected == actual ? "[PASSED]" : "FAILED";
		std::cout << text << " " << _name << " -> First:" << _first << "\t Second:" << _second << "\t Expected:" << _expected << "\t Actual: " << actual << std::endl;
	}
};


void testAddition(const TestCase &testCase)
{
	Number firstNumber(testCase._first);
	Number secondNumber(testCase._second);
	Number result = firstNumber + secondNumber;
	int resultInt = std::stoi(result.toString());
	testCase.run(resultInt);
}

void testSubtraction(const TestCase &testCase)
{
	Number firstNumber(testCase._first);
	Number secondNumber(testCase._second);
	Number result = firstNumber - secondNumber;
	int resultInt = std::stoi(result.toString());
	testCase.run(resultInt);
}

void testMultiplication(const TestCase &testCase)
{
	Number firstNumber(testCase._first);
	Number secondNumber(testCase._second);
	Number result = firstNumber * secondNumber;
	int resultInt = std::stoi(result.toString());
	testCase.run(resultInt);
}

void testDivision(const TestCase &testCase)
{
	Number firstNumber(testCase._first);
	Number secondNumber(testCase._second);
	Number result = firstNumber / secondNumber;
	int resultInt = std::stoi(result.toString());
	testCase.display(resultInt);
}

void launchTests()
{
	testAddition(TestCase(32, 48, 80, "Addition"));
	testAddition(TestCase(99, 15, 114, "Addition"));
	testAddition(TestCase(1327, 92, 1419, "Addition"));
	testAddition(TestCase(0, 0, 0, "Addition"));
	testAddition(TestCase(0, 1, 1, "Addition"));
	testAddition(TestCase(1, 0, 1, "Addition"));
	testAddition(TestCase(-30, -42, -72, "Addition"));
	testAddition(TestCase(32, -48, -16, "Addition"));
	testAddition(TestCase(-32, 48, 16, "Addition"));
	testAddition(TestCase(40, -92, -52, "Addition"));
	testAddition(TestCase(-40, 92, 52, "Addition"));
	testAddition(TestCase(430, -1500, -1070, "Addition"));

	testSubtraction(TestCase(1327, 92, 1235, "Subtraction"));
	testSubtraction(TestCase(1327, 920, 407, "Subtraction"));
	testSubtraction(TestCase(3, 5, -2, "Subtraction"));
	testSubtraction(TestCase(3, -5, 8, "Subtraction"));
	testSubtraction(TestCase(-3, -5, 2, "Subtraction"));
	testSubtraction(TestCase(-3, 5, -8, "Subtraction"));
	testSubtraction(TestCase(32, 48, -16, "Subtraction"));
	testSubtraction(TestCase(-32, 48, -80, "Subtraction"));
	testSubtraction(TestCase(40, 92, -52, "Subtraction"));
	testSubtraction(TestCase(430, 1500, -1070, "Subtraction"));
	testSubtraction(TestCase(0, 0, 0, "Subtraction"));
	testSubtraction(TestCase(0, 1, -1, "Subtraction"));
	testSubtraction(TestCase(1, 0, 1, "Subtraction"));

	testMultiplication(TestCase(32, 48, 1536, "Multiplication"));
	testMultiplication(TestCase(1327, 92, 122084, "Multiplication"));
	testMultiplication(TestCase(0, 0, 0, "Multiplication"));
	testMultiplication(TestCase(0, 1, 0, "Multiplication"));
	testMultiplication(TestCase(1, 0, 0, "Multiplication"));
	testMultiplication(TestCase(1, 1, 1, "Multiplication"));
	testMultiplication(TestCase(-3, 5, -15, "Multiplication"));
	testMultiplication(TestCase(3, -5, -15, "Multiplication"));
	testMultiplication(TestCase(-3, -5, 15, "Multiplication"));

	testDivision(TestCase(32, 48, 0, "Division"));
	testDivision(TestCase(1327, 92, 14, "Division"));
	testDivision(TestCase(143, 5, 28, "Division"));
	testDivision(TestCase(0, 0, 0, "Division"));
	testDivision(TestCase(0, 1, 0, "Division"));
	testDivision(TestCase(1, 0, 0, "Division"));
	testDivision(TestCase(1, 1, 1, "Division"));
	testDivision(TestCase(-3, 5, 0, "Division"));
	testDivision(TestCase(3, -5, 0, "Division"));

	std::cout << "Test completed\n";
}

int main()
{
	launchTests();
}