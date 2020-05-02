#pragma once 
#include < iostream>
#include <utility>

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	void NormalizeFraction();

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational& operator+=(const CRational& rational);
	CRational& operator-=(const CRational& rational);
	CRational& operator*=(const CRational& rational);
	CRational& operator/=(const CRational& rational);

private:
	int m_numerator;
	int m_denominator;
};
CRational const operator+(const CRational& rational1, const CRational& rational2);
CRational const operator-(const CRational& rational1, const CRational& rational2);
CRational const operator*(const CRational& rational1, const CRational& rational2);
CRational const operator/(const CRational& rational1, const CRational& rational2);

bool operator==(const CRational& rational1, const CRational& rational2);
bool operator!=(const CRational& rational1, const CRational& rational2);
bool operator<(const CRational& rational1, const CRational& rational2);
bool operator<=(const CRational& rational1, const CRational& rational2);
bool operator>(const CRational& rational1, const CRational& rational2);
bool operator>=(const CRational& rational1, const CRational& rational2);

std::ostream& operator<<(std::ostream& stream, const CRational& rational);
std::istream& operator>>(std::istream& stream, CRational& rational);