#pragma once
#include "PersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	std::string GetUniversityName() const override
	{
		return m_universityName;
	}
	void SetUniversityName(const std::string& universityName) override
	{
		m_universityName = universityName;
	}

	std::string GetStudentCardNumber() const override
	{
		return m_studentCardNumber;
	}
	void SetStudentCardNumber(const std::string& studentCardNumber) override
	{
		m_studentCardNumber = studentCardNumber;
	}

private:
	std::string m_universityName;
	std::string m_studentCardNumber;
};
