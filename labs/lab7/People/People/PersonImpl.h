#pragma once
#include <string>

template <typename Base>
class CPersonImpl : public Base
{
public:
	std::string GetName() const override
	{
		return m_name;
	}
	void SetName(const std::string& name) override
	{
		m_name = name;
	}

	std::string GetSurname() const override
	{
		return m_surname;
	}
	void SetSurname(const std::string& surname) override
	{
		m_surname = surname;
	}

	std::string GetPatronymic() const override
	{
		return m_patronymic;
	}
	void SetPatronymic(const std::string& patronymic) override
	{
		m_patronymic = patronymic;
	}

	std::string GetAddress() const override
	{
		return m_address;
	}
	void SetAddress(const std::string& address) override
	{
		m_address = address;
	}

private:
	std::string m_name;
	std::string m_surname;
	std::string m_patronymic;
	std::string m_address;
};
