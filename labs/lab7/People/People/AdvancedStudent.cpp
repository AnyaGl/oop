#include "AdvancedStudent.h"

std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}

void CAdvancedStudent::SetDissertationTopic(const std::string& dissertationTopic)
{
	m_dissertationTopic = dissertationTopic;
}
