#pragma once
#include <optional>

class Variable
{
public:
	Variable();
	void SetValue(std::optional<double> value);
	std::optional<double> GetValue() const;

private:
	std::optional<double> m_value;
};
