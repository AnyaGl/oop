#include "catch2/catch.hpp"
#include "../Rational/Rational.h"
#include <iostream>
#include <sstream>

TEST_CASE("Constructor that doesn't have parameters must create fraction 0/1")
{
	CRational rational;
	CHECK(0 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());
}

TEST_CASE("Constructor that have 1 parameter must create fraction n/1")
{
	CRational rational(3);
	CHECK(3 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());
}

TEST_CASE("Constructor that have 2 parameters must create fraction n/d")
{
	CRational rational(2, 3);
	CHECK(2 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());
}

TEST_CASE("If constructor takes denominator = 0, then fraction 0/1 must be created")
{
	CRational rational(6, 0);
	CHECK(0 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());
}

TEST_CASE("Rational number must be stored in normalized form")
{
	CRational rational(6, 3);
	CHECK(2 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());

	rational = CRational(-4, 8);
	CHECK(-1 == rational.GetNumerator());
	CHECK(2 == rational.GetDenominator());
}

TEST_CASE("If constructor takes denominator < 0, then '-' goes to numerator")
{
	CRational rational(1, -3);
	CHECK(-1 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());

	rational = CRational(-1, -3);
	CHECK(1 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());
}

TEST_CASE("ToDouble() returns ratio of numerator to denominator as a double")
{
	CRational rational(1, 2);
	CHECK(0.5 == rational.ToDouble());
}

TEST_CASE("ToCompoundFraction() returns rational number as mixed fraction")
{
	CRational rational(9, 4);
	std::pair <int, CRational> fractional = rational.ToCompoundFraction();
	CHECK(fractional.first == 2);
	CHECK(fractional.second == CRational(1, 4));

	rational *= -1;
	fractional = rational.ToCompoundFraction();
	CHECK(fractional.first == -2);
	CHECK(fractional.second == CRational(-1, 4));
}

TEST_CASE("Unary plus must return number equal to the current")
{
	CRational rational(5, 6);
	CRational resRational = +rational;
	CHECK(5 == resRational.GetNumerator());
	CHECK(6 == resRational.GetDenominator());
}

TEST_CASE("Unary minus must return a number with the opposite sign")
{
	CRational rational(5, 6);
	CRational resRational = -rational;
	CHECK(-5 == resRational.GetNumerator());
	CHECK(6 == resRational.GetDenominator());

	resRational = -resRational;
	CHECK(5 == resRational.GetNumerator());
	CHECK(6 == resRational.GetDenominator());
}

TEST_CASE("Binary plus must return sum of numbers")
{
	CRational rational1(1, 2);
	CRational rational2(-1, 6);
	CRational result = rational1 + rational2;
	CHECK(1 == result.GetNumerator());
	CHECK(3 == result.GetDenominator());

	rational2 = CRational(1, 6);
	result = rational1 + rational2;
	CHECK(2 == result.GetNumerator());
	CHECK(3 == result.GetDenominator());

	result = rational1 + 1;
	CHECK(3 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());

	result = 1 + rational1;
	CHECK(3 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());
}

TEST_CASE("Binary minus must return difference of numbers")
{
	CRational rational1(1, 2);
	CRational rational2(-1, 6);
	CRational result = rational1 - rational2;
	CHECK(2 == result.GetNumerator());
	CHECK(3 == result.GetDenominator());

	result = rational2 - rational1;
	CHECK(-2 == result.GetNumerator());
	CHECK(3 == result.GetDenominator());

	result = rational1 - 1;
	CHECK(-1 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());

	result = 1 - rational1;
	CHECK(1 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());
}

TEST_CASE("Multiplication must return the product of numbers")
{
	CRational rational1(1, 2);
	CRational rational2(2, 3);
	CRational result = rational1 * rational2;
	CHECK(1 == result.GetNumerator());
	CHECK(3 == result.GetDenominator());

	result = rational1 * (-3);
	CHECK(-3 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());

	result = 7 * rational2;
	CHECK(14 == result.GetNumerator());
	CHECK(3 == result.GetDenominator());
}

TEST_CASE("Division must return the quotient of numbers")
{
	CRational rational1(1, 2);
	CRational rational2(2, 3);
	CRational result = rational1 / rational2;
	CHECK(3 == result.GetNumerator());
	CHECK(4 == result.GetDenominator());

	result = rational1 / 5;
	CHECK(1 == result.GetNumerator());
	CHECK(10 == result.GetDenominator());

	result = 7 / rational2;
	CHECK(21 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());

	SECTION("Division by zero must throw an exception")
	{
		CHECK_THROWS(rational1 /= 0);
	}
}

TEST_CASE("+= must increase rational number by another number")
{
	CRational rational1(1, 2);
	CRational rational2(1, 6);
	rational1 += rational2;
	CHECK(2 == rational1.GetNumerator());
	CHECK(3 == rational1.GetDenominator());

	rational2 += 1;
	CHECK(7 == rational2.GetNumerator());
	CHECK(6 == rational2.GetDenominator());
}

TEST_CASE("-= must decrease rational number by another number")
{
	CRational rational1(1, 2);
	CRational rational2(1, 6);
	rational1 -= rational2;
	CHECK(1 == rational1.GetNumerator());
	CHECK(3 == rational1.GetDenominator());

	rational2 -= 1;
	CHECK(-5 == rational2.GetNumerator());
	CHECK(6 == rational2.GetDenominator());
}

TEST_CASE("*= must multiply rational number by the value of another number")
{
	CRational rational1(1, 2);
	CRational rational2(2, 3);
	rational1 *= rational2;
	CHECK(1 == rational1.GetNumerator());
	CHECK(3 == rational1.GetDenominator());

	rational2 *= 3;
	CHECK(2 == rational2.GetNumerator());
	CHECK(1 == rational2.GetDenominator());
}

TEST_CASE("/= must divide the rational number by the value of another number")
{
	CRational rational1(1, 2);
	CRational rational2(2, 3);
	rational1 /= rational2;
	CHECK(3 == rational1.GetNumerator());
	CHECK(4 == rational1.GetDenominator());

	rational2 /= 3;
	CHECK(2 == rational2.GetNumerator());
	CHECK(9 == rational2.GetDenominator());

	SECTION("Division by zero must throw an exception")
	{
		CHECK_THROWS(rational1 /= 0);
	}
}

TEST_CASE("== must check equality of numbers")
{
	CRational rational1(1, 2);

	CHECK(!(rational1 == CRational(2, 3)));
	CHECK(rational1 == CRational(1, 2));
	CHECK(!(rational1 == 3));
	CHECK(3 == CRational(3, 1));
}

TEST_CASE("!= must check number inequality")
{
	CRational rational1(1, 2);

	CHECK(rational1 != CRational(2, 3));
	CHECK(!(rational1 != CRational(1, 2)));
	CHECK(rational1 != 3);
	CHECK(!(3 != CRational(3, 1)));
}

TEST_CASE("<=, <, >, >= must compare numbers")
{
	CRational rational1(1, 2);

	CHECK(CRational(2, 3) >= CRational(1, 2));
	CHECK(!(CRational(2, 3) <= CRational(1, 2)));
	CHECK(CRational(3, 1) > 2);
	CHECK(CRational(1, 2) < 7);
	CHECK(3 <= CRational(7, 2));
	CHECK(!(3 >= CRational(8, 2)));
}

TEST_CASE("Writing and reading must be in the format n/d")
{
	CRational rational(2, -3);
	std::stringstream ss;
	ss << rational;
	CHECK("-2/3" == ss.str());
	
	ss >> rational;	
	CHECK(-2 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());
}

TEST_CASE("If reading failed then the stream has a flag failbit")
{
	std::stringstream ss;
	ss << 2.5;
	CRational rational;
	ss >> rational;
	CHECK(ss.fail());
}