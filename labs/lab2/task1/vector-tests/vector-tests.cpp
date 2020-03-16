#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../vector/ProcessVector.h"

TEST_CASE("Empty vector must be empty")
{
	std::vector<double> numbers;
	ProcessVector(numbers);
	std::vector<double> required;

	CHECK(numbers == required);
}

TEST_CASE("Elements on even positions must be multiplied by 2, items on odd position are decreased by sum of non-negative elements")
{
	std::vector<double> numbers = { 2, 0, -4 };
	ProcessVector(numbers);
	std::vector<double> required = { 4, -2, -8 };

	CHECK(numbers == required);

	numbers = { 1.2, -2.4, 1, -4, -2.55 };
	ProcessVector(numbers);
	required = { 2.4, -4.6, 2, -6.2, -5.1 };

	CHECK(numbers == required);
}
