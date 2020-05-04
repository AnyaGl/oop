#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../MyString/MyString.h"
#include <sstream>

using namespace std::literals;

TEST_CASE("Конструктор по умолчанию формирует строку нулевой длины")
{
	CMyString str;
	CHECK(str.GetLength() == 0);
	CHECK(str.GetStringData() == "\0");
}

TEST_CASE("Конструктор, принимающий строку stl, инициализирует строку данными этой строки")
{
	CMyString str("asdbcd"s);
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == "asdbcd");
}

TEST_CASE("Конструктор, принимающий указатель на массив символов, инициализирует строку данными строки с завершающим нулевым символом")
{
	CMyString str("asdbcd");
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == "asdbcd");
}

TEST_CASE("Конструктор, принимающий указатель на массив символов и длину, инициализирует строку данными из массива заданной длины")
{
	CMyString str("asd\0bcd", 6);
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == "asd\0bc");
}

TEST_CASE("SubString() должен возвращать подстроку с заданной позиции длиной не больше length символов")
{
	CMyString str("123\0qwerty", 10);
	CHECK(str.SubString(1) == "123\0qwerty");
	CHECK(str.SubString(4, 2) == "\0q");
	CHECK(str.SubString(4, 10) == "\0qwerty");
	CHECK_THROWS(str.SubString(10));
}

TEST_CASE("Clear() должен очищать строку (строка становится нулевой длины)")
{
	CMyString str("123\0qwerty", 10);
	str.Clear();
	CHECK(str.GetLength() == 0);
	CHECK(str.GetStringData() == "\0");
}

TEST_CASE("= должен выполнять конкатенацию двух строк")
{
	CMyString resString = "123\0" + CMyString("qwerty");
	CHECK(resString.GetLength() == 10);
	CHECK(resString.GetStringData() == "123\0qwerty");

	resString = "123\0"s + CMyString("qwerty");
	CHECK(resString.GetLength() == 11);
	CHECK(resString.GetStringData() == "123\\0qwerty");

	resString = CMyString("123\0") + CMyString("qwerty");
	CHECK(resString.GetLength() == 11);
	CHECK(resString.GetStringData() == "123\0qwerty");
}

TEST_CASE("+= должен выполнять конкатенацию двух строк с присваиванием")
{
	CMyString resString("123\0");
	resString += CMyString("qwerty");
	CHECK(resString.GetLength() == 10);
	CHECK(resString.GetStringData() == "123\0qwerty");
}

TEST_CASE("== должен проверить две строки на равенство")
{
	CMyString str1("123\0");
	CMyString str2("123");
	CHECK(!(str1 == str2));
	str2 += "\0";
	CHECK(str1 == str2);
}

TEST_CASE("!= должен проверить две строки на неравенство")
{
	CMyString str1("123\0");
	CMyString str2("123");
	CHECK(str1 != str2);
	str2 += "\0";
	CHECK(!(str1 != str2));
}

TEST_CASE("<, >, <=, >= должны сравнивать две строки")
{
	CMyString str1("1235");
	CMyString str2("1234");
	CHECK(!(str1 < str2));
	CHECK(str1 > str2);
	CHECK(!(str1 <= str2));
	CHECK(str1 >= str2);

	str2 += "\0";
	CHECK(str1 < str2);
	CHECK(!(str1 > str2));
	CHECK(str1 <= str2);
	CHECK(!(str1 >= str2));
}

TEST_CASE("[] должен осуществлять индексированный доступ к символам строки по целочисленному индексу для чтения или записи")
{
	CMyString str("123\0q");
	CHECK(str[3] == '\0');
	str[3] = '4';
	CHECK(str[3] == 4);
}

TEST_CASE(">> должен считывать из входного потока")
{
	CMyString str;
	std::stringstream ss;
	ss << "123\0q";
	ss >> str;
	CHECK(str.GetLength() == 5);
	CHECK(str.GetStringData() == "123\0q");
}

TEST_CASE("<< должен записывать в выходной поток")
{
	CMyString str("123\0q", 5);
	std::stringstream ss;
	ss << str;
	CHECK(ss.str() == "123\0q");
}