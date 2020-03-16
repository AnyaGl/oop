#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../vector/ProcessVector.h"

TEST_CASE("Сheck ProcessVector(): empty vector")
{
	std::vector<double> numbers;
	ProcessVector(numbers);
	std::vector<double> required;

	CHECK(numbers == required);
}

TEST_CASE("Сheck ProcessVector(): int numbers (with zero)")
{
	std::vector<double> numbers = { 2, 0, -4 };
	ProcessVector(numbers);
	std::vector<double> required = { 4, -2, -8 };

	CHECK(numbers == required);
}

TEST_CASE("Сheck ProcessVector(): double numbers")
{
	std::vector<double> numbers = { 1.2, -2.4, 1, -4, -2.55 };
	ProcessVector(numbers);
	std::vector<double> required = { 2.4, -4.6, 2, -6.2, -5.1 };

	CHECK(numbers == required);
}
