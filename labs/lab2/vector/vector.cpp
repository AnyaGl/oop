#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

void ReadArray(std::istream& input, std::vector<double>& array)
{
	std::copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), std::back_inserter(array));
}

int main()
{
	std::vector<double> array;
	ReadArray(std::cin, array);

	copy(array.begin(), array.end(), std::ostream_iterator<double>(std::cout, ", "));

	return 0;
}