#include "catch2/catch.hpp"
#include "../Rational/Rational.h"
#include <iostream>
#include <sstream>

TEST_CASE("Конструктор не принимающий параметров должен создавать дробь 0/1")
{
	CRational rational;
	CHECK(0 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());
}

TEST_CASE("Конструктор принимающий 1 параметр должен создавать дробь n/1")
{
	CRational rational(3);
	CHECK(3 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());
}

TEST_CASE("Конструктор принимающий 2 параметрf должен создавать дробь n/d")
{
	CRational rational(2, 3);
	CHECK(2 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());
}

TEST_CASE("Если в констурктор передан знаменатель = 0, то формируется дробь 0/1")
{
	CRational rational(6, 0);
	CHECK(0 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());
}

TEST_CASE("Рациальнальное число должно храниться в нормализованном виде")
{
	CRational rational(6, 3);
	CHECK(2 == rational.GetNumerator());
	CHECK(1 == rational.GetDenominator());

	rational = CRational(-4, 8);
	CHECK(-1 == rational.GetNumerator());
	CHECK(2 == rational.GetDenominator());
}

TEST_CASE("Если получен отрицательный знаменатель, то знак '-' переходит в числитель")
{
	CRational rational(1, -3);
	CHECK(-1 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());

	rational = CRational(-1, -3);
	CHECK(1 == rational.GetNumerator());
	CHECK(3 == rational.GetDenominator());
}

TEST_CASE("ToDouble() возвращает отношение числителя к знаменателю в виде числа double")
{
	CRational rational(1, 5);
	double value = rational.ToDouble();
	CHECK(0.2 == value);
}

TEST_CASE("ToCompoundFraction() возвращает представление рационального числа в виде смешанной дроби")
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

TEST_CASE("Унарный плюс должен возвращать число, равное текущему")
{
	CRational rational(5, 6);
	CRational resRational = +rational;
	CHECK(5 == resRational.GetNumerator());
	CHECK(6 == resRational.GetDenominator());
}

TEST_CASE("Унарный минус должен возвращать число с противоположным знаком")
{
	CRational rational(5, 6);
	CRational resRational = -rational;
	CHECK(-5 == resRational.GetNumerator());
	CHECK(6 == resRational.GetDenominator());

	
	rational = -resRational;
	resRational = -rational;
	CHECK(5 == resRational.GetNumerator());
	CHECK(6 == resRational.GetDenominator());
}

TEST_CASE("Бинарный плюс возвращает сумму чисел")
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

TEST_CASE("Бинарный минус возвращает разность чисел")
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
	CHECK(3 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());

	result = 1 - rational1;
	CHECK(3 == result.GetNumerator());
	CHECK(2 == result.GetDenominator());
}

TEST_CASE("Умножение возвращает произведение чисел")
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

TEST_CASE("Деление возвращает частное чисел")
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

	SECTION("Деление на ноль")
	{
		CHECK_THROWS(rational1 /= 0);
	}
}

TEST_CASE("+= увеличивает рациональное число на величину другого числа")
{
	CRational rational1(1, 2);
	CRational rational2(1, 6);
	rational1 += rational2;
	CHECK(2 == rational1.GetNumerator());
	CHECK(3 == rational1.GetDenominator());

	rational1 += 1;
	CHECK(3 == rational1.GetNumerator());
	CHECK(2 == rational1.GetDenominator());
}

TEST_CASE("-= уменьшает рациональное число на величину другого числа")
{
	CRational rational1(1, 2);
	CRational rational2(1, 6);
	rational1 -= rational2;
	CHECK(1 == rational1.GetNumerator());
	CHECK(3 == rational1.GetDenominator());

	rational1 -= 1;
	CHECK(-1 == rational1.GetNumerator());
	CHECK(2 == rational1.GetDenominator());
}

TEST_CASE("*= умножает рациональное число на величину другого числа")
{
	CRational rational1(1, 2);
	CRational rational2(2, 3);
	rational1 *= rational2;
	CHECK(1 == rational1.GetNumerator());
	CHECK(3 == rational1.GetDenominator());

	rational1 *= 3;
	CHECK(3 == rational1.GetNumerator());
	CHECK(2 == rational1.GetDenominator());
}

TEST_CASE("/= делит рациональное число на величину другого числа")
{
	CRational rational1(1, 2);
	CRational rational2(2, 3);
	rational1 /= rational2;
	CHECK(3 == rational1.GetNumerator());
	CHECK(4 == rational1.GetDenominator());

	rational1 /= 3;
	CHECK(1 == rational1.GetNumerator());
	CHECK(6 == rational1.GetDenominator());

	SECTION("Деление на ноль")
	{
		CHECK_THROWS(rational1 /= 0);
	}
}

TEST_CASE("== проверяет числа на равенство")
{
	CRational rational1(1, 2);

	CHECK(!(rational1 == CRational(2, 3)));
	CHECK(rational1 == CRational(1, 2));
	CHECK(!(rational1 == 3));
	CHECK(3 == CRational(3, 1));
}

TEST_CASE("!= проверяет числа на неравенство")
{
	CRational rational1(1, 2);

	CHECK(rational1 != CRational(2, 3));
	CHECK(!(rational1 != CRational(1, 2)));
	CHECK(rational1 != 3);
	CHECK(!(3 != CRational(3, 1)));
}

TEST_CASE("<=, <, >, >= сравнивают числа")
{
	CRational rational1(1, 2);

	CHECK(CRational(1, 2) >= CRational(2, 3));
	CHECK(!(CRational(1, 2) <= CRational(2, 3)));
	CHECK(CRational(3, 1) > 2);
	CHECK(CRational(1, 2) < 7);
	CHECK(3 <= CRational(7, 2));
	CHECK(!(3 >= CRational(8, 2)));
}

TEST_CASE("Вывод и считывание должны быть в формате n/d")
{
	CRational rational(2, 3);
	std::stringstream ss;
	ss << rational;
	CHECK("2/3" == ss.str());
	
	ss.clear();
	ss << CRational(-3, 7);
	ss >> rational;	
	CHECK(-3 == rational.GetNumerator());
	CHECK(7 == rational.GetDenominator());
}