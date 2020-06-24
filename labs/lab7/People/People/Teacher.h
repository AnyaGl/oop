#pragma once
#include "ITeacher.h"
#include "PersonImpl.h"

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	std::string GetSubject() const override;
	void SetSubject(const std::string& subject) override;

private:
	std::string m_subject;
};
