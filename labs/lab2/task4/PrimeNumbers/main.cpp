#include "PrimeNumbers.h"
#include <iostream>
const int MAX_VALUE = 100000000;

void PrintNumbers(std::set<int> numbers)
{
	for (auto it = numbers.begin(); it != numbers.end(); it++)
	{
		std::cout << *(it) << '\n';
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout
			<< "Invalid number of arguments\n"
			<< "Use: PrimeNumbers.exe <upper bound>\n";
		return 1;
	}
	int upperBound = atoi(argv[1]);

	if (upperBound > MAX_VALUE)
	{
		std::cout
			<< "Use upper bound <= 100'000'000\n";
		return 1;
	}

	std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintNumbers(primeNumbers);
	return 0;
}
