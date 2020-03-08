#define  CATCH_CONFIG_MAIN  
#include "catch2/catch.hpp"
#include "../vector/ProcessVector.h"

TEST_CASE("Сheck the result of ProcessVector()")
{
	std::vector<double> numbers;
	ProcessVector(numbers);
	std::vector<double> required;

	CHECK(numbers == required);


	numbers = { 2, 1, -4};
	ProcessVector(numbers);
	required = { 4, 5, -8};

	CHECK(numbers == required);


	numbers = { 1.2333, -2.45, -1, -4, -2.55};
	ProcessVector(numbers);
	required = { 2.4666, 7.55, -2, 6, -5.1};

	CHECK(numbers == required);

}