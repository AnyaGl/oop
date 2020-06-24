#include "Pupil.h"

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

void CPupil::SetSchoolName(const std::string& schoolName)
{
	m_schoolName = schoolName;
}

std::string CPupil::GetGrade() const
{
	return m_grade;
}

void CPupil::SetGrade(const std::string& grade)
{
	m_grade = grade;
}
