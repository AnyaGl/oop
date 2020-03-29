#define CATCH_CONFIG_MAIN
#include "../PrimeNumbers/PrimeNumbers.h"
#include "catch2/catch.hpp"

std::set<int> result;
std::set<int> required;

TEST_CASE("If upper bound < 2, empty set must be returned")
{
	required = {};

	CHECK(GeneratePrimeNumbersSet(0) == required);
	CHECK(GeneratePrimeNumbersSet(1) == required);
	CHECK(GeneratePrimeNumbersSet(-1) == required);
}

TEST_CASE("If upper bound >= 2, prime numbers set must be returned")
{
	result = GeneratePrimeNumbersSet(2);
	required = { 2 };
	CHECK(result == required);

	result = GeneratePrimeNumbersSet(3);
	required = { 2, 3 };
	CHECK(result == required);

	result = GeneratePrimeNumbersSet(4);
	required = { 2, 3 };
	CHECK(result == required);

	result = GeneratePrimeNumbersSet(11);
	required = { 2, 3, 5, 7, 11 };
	CHECK(result == required);
}

#if !_DEBUG
TEST_CASE("If upper bound == max value (100'000'000), prime numbers set must be contains 5761455 numbers")
{
	result = GeneratePrimeNumbersSet(100'000'000);
	CHECK(result.size() == 5761455);
}
#endif