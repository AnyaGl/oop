#include "CalculatorControl.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <iomanip> 

CalculatorControl::CalculatorControl(Calculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
{
}

bool CalculatorControl::StartHandler()
{
	try
	{
		if (!HandleCommand())
		{
			return false;
		}
	}
	catch (const std::runtime_error& error)
	{
		m_output << error.what() << std::endl;
	}
	return true;
}

bool CalculatorControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string command;
	strm >> command;
	std::transform(command.begin(), command.end(), command.begin(), tolower);

	if (command == "var")
	{
		std::string identifier;
		strm >> identifier;
		Var(identifier);
	}
	else if (command == "let")
	{
		std::string action;
		strm >> action;
		Let(action);
	}
	else if (command == "fn")
	{
		std::string action;
		strm >> action;
		Fn(action);
	}
	else if (command == "print")
	{
		std::string identifier;
		strm >> identifier;
		Print(identifier);
	}
	else if (command == "printvars")
	{
		PrintVars();
	}
	else if (command == "printfns")
	{
		PrintFns();
	}
	else
	{
		return false;
	}

	return true;
}

struct Arguments
{
	std::string identifier;
	std::string firstArgName;
	std::string secondArgName;
	Function::Operation operation = Function::Operation::Nothing;
};

Function::Operation ToOperation(const std::string& operation)
{
	if (operation == "+")
	{
		return Function::Operation::Addition;
	}
	if (operation == "-")
	{
		return Function::Operation::Subtraction;
	}
	if (operation == "*")
	{
		return Function::Operation::Multiplication;
	}
	if (operation == "/")
	{
		return Function::Operation::Division;
	}
}

std::optional<Arguments> ParseArgs(const std::string& action)
{
	std::smatch matches0;
	std::regex rx("^(.*)=(.*)$");
	std::regex_search(action, matches0, rx);

	Arguments args;
	if (matches0.size() == 3)
	{
		args.identifier = matches0.str(1);
		args.firstArgName = matches0.str(2);

		std::smatch matches;
		std::regex rx("^(.*)([/*+-])(.*)$");
		std::regex_search(args.firstArgName, matches, rx);

		if (matches.size() == 4)
		{
			args.secondArgName = matches[3];
			args.operation = ToOperation(matches[2]);
			args.firstArgName = matches[1];
		}
		return args;
	}

	return std::nullopt;
}

bool IsCorrectIdentifier(const std::string& identifier)
{
	std::smatch matches;
	std::regex rx("^([_[:alpha:]])([_[:alnum:]]*)$");
	std::regex_search(identifier, matches, rx);

	if (matches.empty())
	{
		return false;
	}
	return true;
}

void CheckIdentifier(const std::string& name)
{
	if (!IsCorrectIdentifier(name))
	{
		throw std::runtime_error("Invalid identifier name");
	}
}

void CalculatorControl::Var(const std::string& identifier)
{
	CheckIdentifier(identifier);
	m_calc.DeclareVariable(identifier);
}

void CalculatorControl::Let(const std::string& action)
{
	std::optional<Arguments> args = ParseArgs(action);
	if (!args)
	{
		throw std::runtime_error("Invalid command");
	}
	std::string identifier = args.value().identifier;
	std::string firstArgName = args.value().firstArgName;

	CheckIdentifier(identifier);
	std::istringstream ss(firstArgName);
	double value;
	if (ss >> value && ss.eof())
	{
		m_calc.SetValueToVariable(identifier, value);
	}
	else
	{
		m_calc.SetValueToVariable(identifier, firstArgName);
	}
}

void CalculatorControl::Fn(const std::string& action)
{
	std::optional<Arguments> args = ParseArgs(action);
	if (!args)
	{
		throw std::runtime_error("Invalid command");
	}
	std::string identifier = args.value().identifier;
	std::string firstArgName = args.value().firstArgName;
	std::string secondArgName = args.value().secondArgName;
	Function::Operation operation = args.value().operation;


	CheckIdentifier(identifier);
	if (operation != Function::Operation::Nothing)
	{
		m_calc.CreateFunction(identifier, firstArgName, operation, secondArgName);
	}
	else
	{
		m_calc.CreateFunction(identifier, firstArgName);
	}
}

void CalculatorControl::PrintOptionalValue(std::optional<double> value)
{
	if (value)
	{
		m_output << std::fixed << std::setprecision(2);
		m_output << value.value() << std::endl;
	}
	else
	{
		m_output << "nan" << std::endl;
	}
}
void CalculatorControl::Print(const std::string& identifier)
{
	std::optional<double> value = m_calc.GetValue(identifier);
	PrintOptionalValue(value);
}

void CalculatorControl::PrintVars()
{
	Calculator::Values values = m_calc.GetVariableValues();
	for (const auto& [name, value] : values)
	{
		m_output << name << ":";
		PrintOptionalValue(value);
	}
}

void CalculatorControl::PrintFns()
{
	Calculator::Values values = m_calc.GetFunctionValues();
	for (const auto& [name, value] : values)
	{
		m_output << name << ":";
		PrintOptionalValue(value);
	}
}
