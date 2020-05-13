#include "Rational.h"

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	else
	{
		m_numerator = numerator;
		m_denominator = denominator;
		NormalizeFraction();
	}
}

int FindGreatestCommonDivisor(int a, int b)
{
	a = abs(a);
	b = abs(b);
	while (b != 0)
	{
		a %= b;
		std::swap(a, b);
	}
	return a;
}

void CRational::NormalizeFraction()
{
	int gcd = FindGreatestCommonDivisor(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;

	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = abs(m_denominator);
	}
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
	return ((double)m_numerator / (double)m_denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	int numerator = m_numerator - integerPart * m_denominator;
	int denominator = m_denominator;

	std::pair<int, CRational> сompoundFraction = std::make_pair(integerPart, CRational(numerator, denominator));

	return сompoundFraction;
}

CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(const CRational& rational)
{
	m_numerator = rational.GetDenominator() * m_numerator + rational.GetNumerator() * m_denominator;
	m_denominator *= rational.GetDenominator();
	NormalizeFraction();

	return *this;
}

CRational& CRational::operator-=(const CRational& rational)
{
	m_numerator = rational.GetDenominator() * m_numerator - rational.GetNumerator() * m_denominator;
	m_denominator *= rational.GetDenominator();
	NormalizeFraction();

	return *this;
}

CRational& CRational::operator*=(const CRational& rational)
{
	m_numerator *= rational.GetNumerator();
	m_denominator *= rational.GetDenominator();
	NormalizeFraction();

	return *this;
}

CRational& CRational::operator/=(const CRational& rational)
{
	if (rational == 0)
	{
		throw std::runtime_error("Division by zero");
	}
	m_numerator *= rational.GetDenominator();
	m_denominator *= rational.GetNumerator();
	NormalizeFraction();

	return *this;
}

CRational const operator+(const CRational& rational1, const CRational& rational2)
{
	int newNumerator = rational1.GetNumerator() * rational2.GetDenominator() + rational2.GetNumerator() * rational1.GetDenominator();
	int newDenominator = rational1.GetDenominator() * rational2.GetDenominator();
	return CRational(newNumerator, newDenominator);
}

CRational const operator-(const CRational& rational1, const CRational& rational2)
{
	int newNumerator = rational1.GetNumerator() * rational2.GetDenominator() - rational2.GetNumerator() * rational1.GetDenominator();
	int newDenominator = rational1.GetDenominator() * rational2.GetDenominator();
	return CRational(newNumerator, newDenominator);
}

CRational const operator*(const CRational& rational1, const CRational& rational2)
{
	int newNumerator = rational1.GetNumerator() * rational2.GetNumerator();
	int newDenominator = rational1.GetDenominator() * rational2.GetDenominator();
	return CRational(newNumerator, newDenominator);
}

CRational const operator/(const CRational& rational1, const CRational& rational2)
{
	if (rational2 == 0)
	{
		throw std::runtime_error("Division by zero");
	}
	int newNumerator = rational1.GetNumerator() * rational2.GetDenominator();
	int newDenominator = rational1.GetDenominator() * rational2.GetNumerator();
	return CRational(newNumerator, newDenominator);
}

bool operator==(const CRational& rational1, const CRational& rational2)
{
	return (rational1.GetNumerator() == rational2.GetNumerator() && rational1.GetDenominator() == rational2.GetDenominator());
}

bool operator!=(const CRational& rational1, const CRational& rational2)
{
	return !(rational1 == rational2);
}

bool operator<(const CRational& rational1, const CRational& rational2)
{
	CRational result = rational1 - rational2;
	return (result.GetNumerator() < 0);
}

bool operator<=(const CRational& rational1, const CRational& rational2)
{
	CRational result = rational1 - rational2;
	return (result.GetNumerator() <= 0);
}

bool operator>(const CRational& rational1, const CRational& rational2)
{
	CRational result = rational1 - rational2;
	return (result.GetNumerator() > 0);
}

bool operator>=(const CRational& rational1, const CRational& rational2)
{
	CRational result = rational1 - rational2;
	return (result.GetNumerator() >= 0);
}

std::ostream& operator<<(std::ostream& stream, const CRational& rational)
{
	stream << rational.GetNumerator() << '/' << rational.GetDenominator();
	return stream;
}

std::istream& operator>>(std::istream& stream, CRational& rational)
{
	int numerator, denominator;
	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
	}
	return stream;
}
