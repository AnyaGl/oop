#include "PrimeNumbers.h"
#include <vector>

std::vector<bool> SelectPrimeNumbers(uint32_t upperBound)
{
	std::vector<bool> numbers((uint64_t)upperBound + 1, true);
	for (uint32_t i = 2; i * i <= upperBound; i++)
	{
		if (numbers[i])
		{
			for (uint32_t j = i * i; j <= upperBound; j += i)
			{
				numbers[j] = false;
			}
		}
	}
	return numbers;
}

std::set<int> GenerateSet(std::vector<bool>& numbers)
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

bool IsGoodBound(int bound)
{
	return bound > 1;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (!IsGoodBound(upperBound))
	{
		return std::set<int>{};
	}

	std::vector<bool> numbers = SelectPrimeNumbers(upperBound);

	std::set<int> primeNumbers = GenerateSet(numbers);

	return primeNumbers;
}
