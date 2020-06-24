#pragma once
#include "IStudent.h"
#include "StudentImpl.h"

class CStudent : public CStudentImpl<IStudent>
{
public:
	std::string GetUniversityName() const override;
	void SetUniversityName(const std::string& universityName) override;

	std::string GetStudentCardNumber() const override;
	void SetStudentCardNumber(const std::string& studentCardNumber) override;

private:
	std::string m_universityName;
	std::string m_studentCardNumber;
};
