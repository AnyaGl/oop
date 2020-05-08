#include "MyString.h"
#include <algorithm>
#include <iostream>

CMyString::CMyString()
	: m_length(0)
{
	m_pString = new char[m_length + 1];
	m_pString[m_length] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	m_pString = new char[m_length + 1];
	memcpy(m_pString, pString, m_length + 1);
	m_pString[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_pString, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_pString(other.m_pString)
	, m_length(other.m_length)
{
	other.m_pString = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	delete[] m_pString;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::runtime_error("Start position out of range");
	}
	return CMyString(m_pString + start, std::min(m_length - start, length));
}

void CMyString::Clear()
{
	CMyString tmp;
	std::swap(m_pString, tmp.m_pString);
	std::swap(m_length, tmp.m_length);
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (&other != this)
	{
		CMyString tmp(other);
		std::swap(m_pString, tmp.m_pString);
		std::swap(m_length, tmp.m_length);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_pString;
		m_pString = other.m_pString;
		m_length = other.m_length;
		other.m_pString = nullptr;
		other.m_length = 0;
	}
	return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	*this = *this + other;
	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	return m_pString[index];
}

char& CMyString::operator[](size_t index)
{
	return m_pString[index];
}

CMyString const operator+(const CMyString& str1, const CMyString& str2)
{
	size_t sumLength = str1.m_length + str2.m_length;
	char* sumOfStrings = new char[sumLength];
	memcpy(sumOfStrings, str1.m_pString, str1.m_length);
	memcpy(sumOfStrings + str1.m_length, str2.m_pString, str2.m_length);

	CMyString result(sumOfStrings, sumLength);

	return result;
}

enum class CompareResult
{
	Equal,
	Greater,
	Less
};

CompareResult CompareStrings(const CMyString& str1, const CMyString& str2)
{
	if (str1.GetLength() < str2.GetLength())
	{
		return CompareResult::Less;
	}
	if (str1.GetLength() > str2.GetLength())
	{
		return CompareResult::Greater;
	}
	for (size_t i = 0; i < str1.GetLength(); i++)
	{
		if (str1[i] < str2[i])
		{
			return CompareResult::Less;
		}
		if (str1[i] > str2[i])
		{
			return CompareResult::Greater;
		}
	}
	return CompareResult::Equal;
}

bool operator==(const CMyString& str1, const CMyString& str2)
{
	return CompareStrings(str1, str2) == CompareResult::Equal;
}

bool operator!=(const CMyString& str1, const CMyString& str2)
{
	return !(str1 == str2);
}

bool operator<(const CMyString& str1, const CMyString& str2)
{
	return CompareStrings(str1, str2) == CompareResult::Less;
}

bool operator>(const CMyString& str1, const CMyString& str2)
{
	return CompareStrings(str1, str2) == CompareResult::Greater;
}

bool operator<=(const CMyString& str1, const CMyString& str2)
{
	return !(str1 > str2);
}

bool operator>=(const CMyString& str1, const CMyString& str2)
{
	return !(str1 < str2);
}

std::ostream& operator<<(std::ostream& stream, const CMyString& str)
{
	std::string resultStr;
	for (size_t i = 0; i < str.m_length; i++)
	{
		stream << str[i];
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
	std::string inputStr;
	stream >> inputStr;
	str = CMyString(inputStr);
	return stream;
}
