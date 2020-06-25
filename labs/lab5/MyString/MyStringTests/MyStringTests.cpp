#define CATCH_CONFIG_MAIN
#include "../MyString/MyString.h"
#include "catch2/catch.hpp"
#include <sstream>

using namespace std::literals;

TEST_CASE("Default constructor must create a zero-length string")
{
	CMyString str;
	CHECK(str.GetLength() == 0);
	CHECK(str.GetStringData() == std::string(""));
}

TEST_CASE("Constructor that takes stl string must initialize string with data of stl string")
{
	CMyString str("asdbcd"s);
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == std::string("asdbcd"));
}

TEST_CASE("Constructor that takes pointer to array of characters must initialize string with string data that ends with \\0")
{
	CMyString str("asdbcd");
	CHECK(str.GetLength() == 6);
	CHECK(str.GetStringData() == std::string("asdbcd"));
}

TEST_CASE("Constructor that takes pointer to array of characters and length must initialize string with string data of given length")
{
	CMyString str("asd\0bcd", 7);
	CHECK(str.GetLength() == 7);
	CHECK(std::string(str.GetStringData(), 7) == std::string("asd\0bcd", 7));
}

TEST_CASE("SubString() must return substring from given position with length <= passed length value")
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

TEST_CASE("Clear() must clear string (string becomes zero length)")
{
	CMyString str("123\0qwerty", 10);
	str.Clear();
	CHECK(str.GetLength() == 0);
	CHECK(str.GetStringData() == std::string(""));
}

TEST_CASE("Assignment operator = must assign variable the value of another variable")
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

TEST_CASE("Move assignment operator = must assign variable value of another variable that will be cleared")
{
	CMyString str1;
	CMyString str2("123");
	str1 = std::move(str2);

	CHECK(str1.GetLength() == 3);
	CHECK(str1.GetStringData() == std::string("123"));

	CHECK(str2.GetLength() == 0);
	CHECK(str2.GetStringData() == std::string(""));

	str1 = std::move(str1);
	CHECK(str1.GetLength() == 3);
	CHECK(str1.GetStringData() == std::string("123"));
}

TEST_CASE("+ must concatenate two strings")
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

TEST_CASE("+= must concatenate two strings with assignment")
{
	CMyString resString("123\0", 4);
	resString += CMyString("qwerty");
	CHECK(resString.GetLength() == 10);
	CHECK(std::string(resString.GetStringData(), 10) == std::string("123\0qwerty", 10));

	resString += resString;
	CHECK(resString.GetLength() == 20);
	CHECK(std::string(resString.GetStringData(), 20) == std::string("123\0qwerty123\0qwerty", 20));
}

TEST_CASE("== must check string equality")
{
	CMyString str1("123\0", 4);
	CMyString str2("123", 3);
	CHECK(!(str1 == str2));
	str2 += CMyString("\0", 1);
	CHECK(str1 == str2);
}

TEST_CASE("!= must check string inequality")
{
	CMyString str1("123\0", 4);
	CMyString str2("123", 3);
	CHECK(str1 != str2);

	str2 += CMyString("\0", 1);
	CHECK(!(str1 != str2));
}

TEST_CASE("<, >, <=, >= must compare two strings")
{
	CMyString str1("1235");
	CMyString str2("1234");
	CHECK(str1 > str2);
	CHECK_FALSE(str1 < str2);

	CHECK(str1 >= str2);
	CHECK_FALSE(str1 <= str2);

	CHECK(str2 < str1);
	CHECK_FALSE(str2 > str1);

	CHECK(str2 <= str1);
	CHECK_FALSE(str2 >= str1);

	str1 = CMyString("123");
	
	CHECK(str1 < str2);
	CHECK_FALSE(str1 > str2);
	
	CHECK(str2 > str1);
	CHECK_FALSE(str2 < str1);
}

TEST_CASE("[] must perform indexed access to string characters by integer index for reading or writing")
{
	CMyString str("123\0q", 5);
	CHECK(str[3] == '\0');
	str[3] = '4';
	CHECK(str[3] == '4');
}

TEST_CASE(">> must read from the input stream")
{
	CMyString str;
	std::stringstream ss;
	ss << "123\0q";
	ss >> str;
	CHECK(str.GetLength() == 3);
	CHECK(str.GetStringData() == std::string("123"));
}

TEST_CASE("<< must write to the output stream")
{
	CMyString str("123\0q", 5);
	std::stringstream ss;
	ss << str;
	CHECK(ss.str() == std::string("123\0q", 5));
}