#include "MyString.h"

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

CMyString::CMyString(CMyString&& other)
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
	return size_t();
}

const char* CMyString::GetStringData() const
{
	return nullptr;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	return CMyString();
}

void CMyString::Clear()
{
}

CMyString& CMyString::operator=(const CMyString& other)
{
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	return *this;
}



CMyString& CMyString::operator+=(const CMyString& other)
{
	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	return m_pString[0];
}

char& CMyString::operator[](size_t index)
{
	return m_pString[0];
}

CMyString const operator+(const CMyString& str1, const CMyString& str2)
{
	return nullptr;
}

bool operator==(const CMyString& str1, const CMyString& str2)
{
	return false;
}

bool operator!=(const CMyString& str1, const CMyString& str2)
{
	return false;
}

bool operator<(const CMyString& str1, const CMyString& str2)
{
	return false;
}

bool operator>(const CMyString& str1, const CMyString& str2)
{
	return false;
}

bool operator<=(const CMyString& str1, const CMyString& str2)
{
	return false;
}

bool operator>=(const CMyString& str1, const CMyString& str2)
{
	return false;
}

std::ostream& operator<<(std::ostream& stream, const CMyString& rational)
{
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& rational)
{
	return stream;
}
