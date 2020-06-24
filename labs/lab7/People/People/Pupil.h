#pragma once
#include "IPupil.h"
#include "PersonImpl.h"

class CPupil : public CPersonImpl<IPupil>
{
public:
	std::string GetSchoolName() const override;
	void SetSchoolName(const std::string& schoolName) override;

	std::string GetGrade() const override;
	void SetGrade(const std::string& grade) override;

private:
	std::string m_schoolName;
	std::string m_grade;
};
