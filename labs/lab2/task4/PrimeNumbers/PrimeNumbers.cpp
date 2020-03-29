#include "PrimeNumbers.h"
#include <vector>

std::vector<bool> SelectPrimeNumbers(uint32_t upperBound)
{
	std::vector<bool> flags((uint64_t)upperBound + 1, true);
	for (uint32_t i = 2; i * i <= upperBound; i++)
	{
		if (flags[i])
		{
			for (uint32_t j = i * i; j <= upperBound; j += i)
			{
				flags[j] = false;
			}
		}
	}
	return flags;
}

std::set<int> GenerateSet(const std::vector<bool>& numbers)
{
	std::set<int> selectedNumbers;
	for (auto i = 2; i < numbers.size(); i++)
	{
		if (numbers[i])
		{
			selectedNumbers.insert(i);
		}
	}
	return selectedNumbers;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
	{
		return std::set<int>{};
	}

	std::vector<bool> numbers = SelectPrimeNumbers(upperBound);

	std::set<int> primeNumbers = GenerateSet(numbers);

	return primeNumbers;
}
