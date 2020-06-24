#pragma once
#include "IStudent.h"
#include <string>

class IAdvancedStudent : public IStudent
{
public:
	virtual std::string GetDissertationTopic() const = 0;
	virtual void SetDissertationTopic(const std::string& dissertationTopic) = 0;
};
