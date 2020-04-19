#pragma once
#include "Calculator.h"

class CalculatorControl
{
public:
	CalculatorControl(Calculator& calc, std::istream& input, std::ostream& output);
	bool StartHandler();

private:
	bool HandleCommand();
	void Var(const std::string& identifier);
	void Let(const std::string& action);
	void Fn(const std::string& action);
	void Print(const std::string& identifier);
	void PrintVars();
	void PrintFns();
	void PrintOptionalValue(std::optional<double> value);

	Calculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;
};
