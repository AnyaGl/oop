#include "Function.h"

Function::Function(const std::string& argName)
	: m_firstArgName(argName)
	, m_operation(Operation::Nothing)
	, m_value(std::nullopt)
{
}

Function::Function(const std::string& firstArgName, const Operation& operation, const std::string& secondArgName)
	: m_firstArgName(firstArgName)
	, m_operation(operation)
	, m_secondArgName(secondArgName)
	, m_value(std::nullopt)
{
}

void Function::SetValue(std::optional<double> value)
{
	m_value = value;
}

std::optional<double> Function::GetValue() const
{
	return m_value;
}

std::string Function::GetFirstArgName() const
{
	return m_firstArgName;
}

std::string Function::GetSecondArgName() const
{
	return m_secondArgName;
}

Function::Operation Function::GetOperation() const
{
	return m_operation;
}
