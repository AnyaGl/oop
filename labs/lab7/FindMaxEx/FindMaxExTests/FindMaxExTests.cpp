#define CATCH_CONFIG_MAIN
#include "../FindMaxEx/FindMaxEx.h"
#include "../FindMaxEx/Sportsman.h"
#include "catch2/catch.hpp"

TEST_CASE("FindMax() must find the maximum value of vector<double>")
{
	std::vector<double> intVector = { 9.8, 14.12, 5.6, 44.7, 23, 31.3 };
	double maxValue;
	CHECK(FindMax(intVector, maxValue, std::less<double>()));
	CHECK(maxValue == 44.7);
}

TEST_CASE("FindMax() must find the maximum value of vector<char>")
{
	std::vector<char> strVector = { 'a', 'b', 'z', 'y' };
	char maxValue;
	CHECK(FindMax(strVector, maxValue, std::less<char>()));
	CHECK(maxValue == 'z');
}

TEST_CASE("If vector<T> is empty, FindMax() must return false")
{
	std::vector<int> strVector;
	int maxValue;
	CHECK_FALSE(FindMax(strVector, maxValue, std::less<int>()));
}

std::vector<Sportsman> sportsmen = {
	{ "Vladimir", 185.6, 73.5 },
	{ "Andrey", 190, 85 },
	{ "Ivan", 183.4, 90 }
};

TEST_CASE("FindMax() must find sporstman with max height in vector<Sportsman>")
{
	Sportsman sportsman;
	CHECK(FindMax(sportsmen, sportsman, IsLessHeight));
	CHECK(sportsman.name == "Andrey");
	CHECK(sportsman.height == 190);
	CHECK(sportsman.weight == 85);
}

TEST_CASE("FindMax() must find sporstman with max weight in vector<Sportsman>")
{
	Sportsman sportsman;
	CHECK(FindMax(sportsmen, sportsman, IsLessWeight));
	CHECK(sportsman.name == "Ivan");
	CHECK(sportsman.height == 183.4);
	CHECK(sportsman.weight == 90);
}
