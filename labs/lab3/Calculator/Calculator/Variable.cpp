#include "Variable.h"

Variable::Variable()
	: m_value(std::nullopt)
{
}

void Variable::SetValue(std::optional<double> value)
{
	m_value = value;
}

std::optional<double> Variable::GetValue() const
{
	return m_value;
}
