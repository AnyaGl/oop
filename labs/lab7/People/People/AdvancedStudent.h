#pragma once
#include "IAdvancedStudent.h"
#include "StudentImpl.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	std::string GetDissertationTopic() const override;
	void SetDissertationTopic(const std::string& dissertationTopic) override;

private:
	std::string m_dissertationTopic;
};
