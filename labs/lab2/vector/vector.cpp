#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

void ProcessVector(std::vector<double>& numbers)
{
	double sumNegativeNum = 0;
	for (double& number : numbers)
	{
		if (number < 0)
		{
			sumNegativeNum += number;
		}
	}

	for (int i = 0; i < numbers.size(); i++)
	{
		if (i % 2 == 0)
		{
			numbers[i] *= 2;
		}
		else
		{
			numbers[i] -= sumNegativeNum;
		}
	}
}

int main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

	ProcessVector(numbers);
	
	std::sort(numbers.begin(), numbers.end());

	std::cout << std::fixed << std::setprecision(3);
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));

	return 0;
}