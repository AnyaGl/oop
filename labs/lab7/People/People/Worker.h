#pragma once
#include "IWorker.h"
#include "PersonImpl.h"

class CWorker : public CPersonImpl<IWorker>
{
public:
	std::string GetSpeciality() const override;
	void SetSpeciality(const std::string& speciality) override;

private:
	std::string m_speciality;
};
