#define CATCH_CONFIG_MAIN
#include "../MyString/MyString.h"
#include "catch2/catch.hpp"
#include <sstream>

using namespace std::literals;

TEST_CASE("Конструктор по умолчанию формирует строку нулевой длины")
{
	CMyString str;
	CHECK(str.GetLength() == 0);
	CHECK(str.GetStringData() == std::string(""));
}

TEST_CASE("Конструктор, принимающий строку stl, инициализирует строку данными этой строки")
{
	CMyString str("asdbcd"s);
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == std::string("asdbcd"));
}

TEST_CASE("Конструктор, принимающий указатель на массив символов, инициализирует строку данными строки с завершающим нулевым символом")
{
	CMyString str("asdbcd");
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == std::string("asdbcd"));
}

TEST_CASE("Конструктор, принимающий указатель на массив символов и длину, инициализирует строку данными из массива заданной длины")
{
	CMyString str("asd\0bcd", 7);
	CHECK(str.GetLength() == 7);
	CHECK(std::string(str.GetStringData(), 7) == std::string("asd\0bcd", 7));
}

TEST_CASE("SubString() должен возвращать подстроку с заданной позиции длиной не больше length символов")
{
	CMyString str("123\0qwerty", 10);

	CMyString substr = str.SubString(1);
	CHECK(substr.GetLength() == 9);
	CHECK(std::string(substr.GetStringData(), 9) == std::string("23\0qwerty", 9));

	substr = str.SubString(3, 2);
	CHECK(substr.GetLength() == 2);
	CHECK(std::string(substr.GetStringData(), 2) == std::string("\0q", 2));

	substr = str.SubString(3, 15);
	CHECK(substr.GetLength() == 7);
	CHECK(std::string(substr.GetStringData(), 7) == std::string("\0qwerty", 7));

	CHECK_THROWS(str.SubString(10));
}

TEST_CASE("Clear() должен очищать строку (строка становится нулевой длины)")
{
	CMyString str("123\0qwerty", 10);
	str.Clear();
	CHECK(str.GetLength() == 0);
	CHECK(str.GetStringData() == std::string(""));
}

TEST_CASE("оператор копирования = должен присваивать переменной значение другой переменной")
{
	CMyString str1;
	CMyString str2("123");
	str1 = str2;
	CHECK(str1.GetLength() == 3);
	CHECK(str1.GetStringData() == std::string("123"));

	str1 = str1;
	CHECK(str1.GetLength() == 3);
	CHECK(str1.GetStringData() == std::string("123"));
}

TEST_CASE("оператор перемещения = должен присваивать переменной значение другой переменной, которая в итоге обнулится")
{
	CMyString str1;
	CMyString str2("123");
	str1 = std::move(str2);

	CHECK(str1.GetLength() == 3);
	CHECK(str1.GetStringData() == std::string("123"));

	CHECK(str2.GetLength() == 0);
	CHECK(str2.GetStringData() == nullptr);

	str1 = std::move(str1);
	CHECK(str1.GetLength() == 3);
	CHECK(str1.GetStringData() == std::string("123"));
}

TEST_CASE("+ должен выполнять конкатенацию двух строк")
{
	CMyString resString = "123" + CMyString("\0qwerty", 7);
	CHECK(resString.GetLength() == 10);
	CHECK(std::string(resString.GetStringData(), 10) == std::string("123\0qwerty", 10));

	resString = "123"s + CMyString("qwerty");
	CHECK(resString.GetLength() == 9);
	CHECK(std::string(resString.GetStringData()) == std::string("123qwerty"));

	resString = CMyString("123") + CMyString("qwerty");
	CHECK(resString.GetLength() == 9);
	CHECK(std::string(resString.GetStringData()) == std::string("123qwerty"));
}

TEST_CASE("+= должен выполнять конкатенацию двух строк с присваиванием")
{
	CMyString resString("123\0", 4);
	resString += CMyString("qwerty");
	CHECK(resString.GetLength() == 10);
	CHECK(std::string(resString.GetStringData(), 10) == std::string("123\0qwerty", 10));

	resString += resString;
	CHECK(resString.GetLength() == 20);
	CHECK(std::string(resString.GetStringData(), 20) == std::string("123\0qwerty123\0qwerty", 20));
}

TEST_CASE("== должен проверить две строки на равенство")
{
	CMyString str1("123\0", 4);
	CMyString str2("123", 3);
	CHECK(!(str1 == str2));
	str2 += CMyString("\0", 1);
	CHECK(str1 == str2);
}

TEST_CASE("!= должен проверить две строки на неравенство")
{
	CMyString str1("123\0", 4);
	CMyString str2("123", 3);
	CHECK(str1 != str2);

	str2 += CMyString("\0", 1);
	CHECK(!(str1 != str2));
}

TEST_CASE("<, >, <=, >= должны сравнивать две строки")
{
	CMyString str1("1235");
	CMyString str2("1234");
	CHECK(str1 > str2);
	CHECK(str1 >= str2);
	CHECK(str2 < str1);

	str2 += CMyString("\0", 1);
	CHECK(str1 < str2);
	CHECK(str1 <= str2);
}

TEST_CASE("[] должен осуществлять индексированный доступ к символам строки по целочисленному индексу для чтения или записи")
{
	CMyString str("123\0q", 5);
	CHECK(str[3] == '\0');
	str[3] = '4';
	CHECK(str[3] == '4');
}

TEST_CASE(">> должен считывать из входного потока")
{
	CMyString str;
	std::stringstream ss;
	ss << "123\0q";
	ss >> str;
	CHECK(str.GetLength() == 3);
	CHECK(str.GetStringData() == std::string("123"));
}

TEST_CASE("<< должен записывать в выходной поток")
{
	CMyString str("123\0q", 5);
	std::stringstream ss;
	ss << str;
	CHECK(ss.str() == std::string("123\0q", 5));
}