#include "Worker.h"

std::string CWorker::GetSpeciality() const
{
	return m_speciality;
}

void CWorker::SetSpeciality(const std::string& speciality)
{
	m_speciality = speciality;
}
