#include "Rational.h"

CRational::CRational()
{
	m_numerator = 0;
	m_denominator = 1;
}

CRational::CRational(int value)
	: m_numerator(value)
{
	m_denominator = 1;
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return m_numerator / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	return std::pair<int, CRational>();
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return *this;
}

CRational& CRational::operator+=(const CRational& rational)
{
	return *this;
}

CRational& CRational::operator-=(const CRational& rational)
{
	return *this;
}

CRational& CRational::operator*=(const CRational& rational)
{
	return *this;
}

CRational& CRational::operator/=(const CRational& rational)
{
	return *this;
}


CRational const operator+(const CRational& rational1, const CRational& rational2)
{
	return rational1;
}

CRational const operator-(const CRational& rational1, const CRational& rational2)
{
	return rational1;
}

CRational const operator*(const CRational& rational1, const CRational& rational2)
{
	return rational1;
}

CRational const operator/(const CRational& rational1, const CRational& rational2)
{
	return rational1;
}

bool operator==(const CRational& rational1, const CRational& rational2)
{
	return false;
}

bool operator!=(const CRational& rational1, const CRational& rational2)
{
	return false;
}

bool operator<(const CRational& rational1, const CRational& rational2)
{
	return false;
}

bool operator<=(const CRational& rational1, const CRational& rational2)
{
	return false;
}

bool operator>(const CRational& rational1, const CRational& rational2)
{
	return false;
}

bool operator>=(const CRational& rational1, const CRational& rational2)
{
	return false;
}

std::ostream& operator<<(std::ostream& stream, const CRational& rational)
{
	return stream;
}

std::istream& operator>>(std::istream& stream, const CRational& rational)
{
	return stream;
}
