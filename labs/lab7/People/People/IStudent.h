#pragma once
#include "IPerson.h"
#include <string>

class IStudent : public IPerson
{
public:
	virtual std::string GetUniversityName() const = 0;
	virtual void SetUniversityName(const std::string& universityName) = 0;

	virtual std::string GetStudentCardNumber() const = 0;
	virtual void SetStudentCardNumber(const std::string& studentCardNumber) = 0;
};
