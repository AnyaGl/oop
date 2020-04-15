#pragma once
#include <iostream>

class CCar;

class CCarControl
{
public:
	CCarControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn();
	bool EngineOff();
	bool Info();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};
