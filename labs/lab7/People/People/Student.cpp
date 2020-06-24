#include "Student.h"

std::string CStudent::GetUniversityName() const
{
	return m_universityName;
}

void CStudent::SetUniversityName(const std::string& universityName)
{
	m_universityName = universityName;
}

std::string CStudent::GetStudentCardNumber() const
{
	return m_studentCardNumber;
}

void CStudent::SetStudentCardNumber(const std::string& studentCardNumber)
{
	m_studentCardNumber = studentCardNumber;
}
