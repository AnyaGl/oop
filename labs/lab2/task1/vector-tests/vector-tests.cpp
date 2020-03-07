#define  CATCH_CONFIG_MAIN  
#include "catch2/catch.hpp"
#include "../vector/ProcessVector.h"

TEST_CASE("...")
{
	std::vector<double> numbers = { 2, 1, -4};
	ProcessVector(numbers);
	std::vector<double> required = { 4.000, 5.000, -8.000};

	CHECK(numbers == required);

}