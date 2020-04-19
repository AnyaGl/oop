#include "Calculator.h"
#include <set>
#include <stdexcept>

bool Calculator::IsVariableExist(const std::string& name) const
{
	return m_variables.find(name) != m_variables.end();
}

bool Calculator::IsFunctionExist(const std::string& name) const
{
	return m_functions.find(name) != m_functions.end();
}

void Calculator::CheckForMissingIdentifier(const std::string& name) const
{
	if (IsVariableExist(name))
	{
		throw std::runtime_error("There is a variable with name '" + name + "'");
	}
	if (IsFunctionExist(name))
	{
		throw std::runtime_error("There is a function with name '" + name + "'");
	}
}

void Calculator::CheckIdentifierExistance(const std::string& name) const
{
	if (!IsVariableExist(name) && !IsFunctionExist(name))
	{
		throw std::runtime_error("Identifier '" + name + "' doesn't exist");
	}
}

void Calculator::DeclareVariable(const std::string& name)
{
	CheckForMissingIdentifier(name);
	m_variables.emplace(name, Variable());
}

void Calculator::SetValueToVariable(const std::string& name, double value)
{
	if (!IsVariableExist(name))
	{
		DeclareVariable(name);
	}
	m_variables[name].SetValue(value);
	UpdateFunctionValues(name);
}

void Calculator::SetValueToVariable(const std::string& name, const std::string& argName)
{
	CheckIdentifierExistance(argName);
	if (!IsVariableExist(name))
	{
		DeclareVariable(name);
	}
	std::optional<double> value = GetValue(argName);
	m_variables[name].SetValue(value);
	UpdateFunctionValues(name);
}

void Calculator::CreateFunction(const std::string& name, const std::string& argName)
{
	CheckForMissingIdentifier(name);
	CheckIdentifierExistance(argName);
	
	m_functions[name] = Function(argName);
	std::optional<double> argValue = GetValue(argName);
	m_functions[name].SetValue(argValue);
	m_functionsInOrder.push_back(name);
}

void Calculator::CreateFunction(const std::string& name, const std::string& firstArgName, const Function::Operation& operation, const std::string& secondArgName)
{
	CheckForMissingIdentifier(name);
	CheckIdentifierExistance(firstArgName);
	CheckIdentifierExistance(secondArgName);

	m_functions.emplace(name, Function(firstArgName, operation, secondArgName));
	CalculateValue(m_functions[name]);
	m_functionsInOrder.push_back(name);
}

void Calculator::CalculateValue(Function& function)
{
	std::optional<double> arg1 = GetValue(function.GetFirstArgName());

	if (function.GetOperation() == Function::Operation::Nothing)
	{
		function.SetValue(arg1);
		return;
	}

	std::optional<double> arg2 = GetValue(function.GetSecondArgName());
	
	if (arg1 && arg2)
	{
		switch (function.GetOperation())
		{
		case Function::Operation::Addition:
			function.SetValue(arg1.value() + arg2.value());
			return;
		case Function::Operation::Subtraction:
			function.SetValue(arg1.value() - arg2.value());
			return;
		case Function::Operation::Multiplication:
			function.SetValue(arg1.value() * arg2.value());
			return;
		case Function::Operation::Division:
			if (arg2.value() == 0)
			{
				function.SetValue(std::nullopt);
				return;
			}
			function.SetValue(arg1.value() / arg2.value());
			return;
		}
	}
	function.SetValue(std::nullopt);
}

void Calculator::UpdateFunctionValues(const std::string& changedVar)
{
	std::set<std::string> changedValues;
	changedValues.emplace(changedVar);

	for (auto& name : m_functionsInOrder)
	{
		Function& func = m_functions[name];
		if (changedValues.count(name) == 0 && (changedValues.count(func.GetFirstArgName()) != 0 || changedValues.count(func.GetSecondArgName()) != 0))
		{
			changedValues.emplace_hint(changedValues.end(), name);
			CalculateValue(func);
		}
	}	
}

Calculator::Values Calculator::GetVariableValues() const
{
	Values values;
	for (auto& [name, var] : m_variables)
	{
		values.emplace(name, var.GetValue());
	}
	return values;
}

Calculator::Values Calculator::GetFunctionValues() const
{
	Values values;
	for (auto& [name, func] : m_functions)
	{
		values.emplace(name, func.GetValue());
	}
	return values;
}

std::optional<double> Calculator::GetValue(const std::string& name) const
{
	CheckIdentifierExistance(name);
	if (IsVariableExist(name))
	{
		Variable var = m_variables.find(name)->second;
		return var.GetValue();
	}
	if (IsFunctionExist(name))
	{
		Function func = m_functions.find(name)->second;
		return func.GetValue();
	}
}
