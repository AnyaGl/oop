#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>
#include "ProcessVector.h"

int main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

	ProcessVector(numbers);

	std::sort(numbers.begin(), numbers.end());

	std::cout << std::fixed << std::setprecision(3);
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));

	return 0;
}