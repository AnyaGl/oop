#include "CarControl.h"
#include "Car.h"
#include <algorithm>
#include <sstream>
#include <string>

CCarControl::CCarControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
{
}

bool CCarControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;
	std::transform(action.begin(), action.end(), action.begin(), tolower);

	if (action == "info")
	{
		Info();
	}
	else if (action == "engineon")
	{
		EngineOn();
	}
	else if (action == "engineoff")
	{
		EngineOff();
	}
	else if (action == "setgear")
	{
		int gear;
		strm >> gear;
		SetGear(gear);
	}
	else if (action == "setspeed")
	{
		int speed;
		strm >> speed;
		SetSpeed(speed);
	}
	else
	{
		return false;
	}

	return true;
}

bool CCarControl::EngineOn()
{
	bool result = m_car.TurnOnEngine();
	if (result)
	{
		m_output << "Engine is on\n";
	}
	else
	{
		m_output << "Failed to turn on engine\n";
	}

	return result;
}

bool CCarControl::EngineOff()
{
	bool result = m_car.TurnOffEngine();
	if (result)
	{
		m_output << "Engine is off\n";
	}
	else
	{
		m_output << "Failed to turn off engine\n"
				 << "Speed must be 0 and gear must be neutral\n";
	}

	return result;
}

std::string DirectionToString(const Direction& direction)
{
	switch (direction)
	{
	case Direction::Back:
		return "back";
	case Direction::Stand:
		return "stand";
	case Direction::Forward:
		return "forward";
	default:
		return "Invalid direction";
	}
}

std::string GearToString(int gear)
{
	switch (gear)
	{
	case -1:
		return "reverse";
	case 0:
		return "neutral";
	case 1:
		return "first";
	case 2:
		return "second";
	case 3:
		return "third";
	case 4:
		return "fourth";
	case 5:
		return "fifth";
	default:
		return "Invalid gear";
	}
}

bool CCarControl::Info()
{
	m_output << "Engine status: " << ((m_car.IsEngineOn()) ? ("on") : ("off")) << std::endl;
	m_output << "Speed: " << m_car.GetSpeed() << std::endl;
	m_output << "Direction: " << DirectionToString(m_car.GetDirection()) << std::endl;
	m_output << "Gear: " << GearToString(m_car.GetGear()) << std::endl;

	return false;
}

bool CCarControl::SetGear(int gear)
{
	bool result = m_car.SetGear(gear);
	if (result)
	{
		m_output << "Gear is changed to " << GearToString(gear) << "\n";
	}
	else
	{
		m_output << "Gear didn't change\n";
	}

	return result;
}

bool CCarControl::SetSpeed(int speed)
{
	bool result = m_car.SetSpeed(speed);
	if (result)
	{
		m_output << "Now speed is " << speed << "\n";
	}
	else
	{
		m_output << "Speed didn't change\n";
	}

	return result;
}