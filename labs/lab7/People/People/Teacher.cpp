#include "Teacher.h"

std::string CTeacher::GetSubject() const
{
	return m_subject;
}

void CTeacher::SetSubject(const std::string& subject)
{
	m_subject = subject;
}
