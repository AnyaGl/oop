﻿#include "Car.h"

bool CCar::TurnOnEngine()
{
	m_isEngineOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}
	return false;
}

bool IsSpeedInRange(const std::pair<int, int>& speedRange, int speed)
{
	return speed >= speedRange.first && speed <= speedRange.second;
}

bool IsSpeedInGearSpeedRange(int speed, int gear)
{
	return (gear == -1 && IsSpeedInRange(REVERSE_SPEED_RANGE, speed)) || 
		(gear == 0 && IsSpeedInRange(NEUTRAL_SPEED_RANGE, speed)) || 
		(gear == 1 && IsSpeedInRange(FIRST_SPEED_RANGE, speed)) || 
		(gear == 2 && IsSpeedInRange(SECOND_SPEED_RANGE, speed)) || 
		(gear == 3 && IsSpeedInRange(THIRD_SPEED_RANGE, speed)) || 
		(gear == 4 && IsSpeedInRange(FOURTH_SPEED_RANGE, speed)) || 
		(gear == 5 && IsSpeedInRange(FIFTH_SPEED_RANGE, speed));
}

bool CCar::SetSpeed(int speed)
{
	if (m_gear == 0 && m_speed < speed)
	{
		return false;
	}
	if (!IsSpeedInGearSpeedRange(speed, m_gear))
	{
		return false;
	}
	m_speed = speed;
	m_direction = (speed == 0) ? Direction::Stand : 
				  (speed > 0 && m_gear == -1) ? Direction::Back : 
				  (speed > 0 && m_gear > 0) ? Direction::Forward :
				   m_direction;

	return true;
}

bool IsDirectionAllowChangeSpeed(int gear, const Direction& direction)
{
	return (gear == -1 && direction != Direction::Forward) || 
		(gear == 0) || 
		(gear == 1 && direction != Direction::Back) || 
		(gear > 1 && direction == Direction::Forward);
}

bool CCar::SetGear(int gear)
{
	if (!m_isEngineOn && gear != 0)
	{
		return false;
	}
	if (!IsSpeedInGearSpeedRange(m_speed, gear))
	{
		return false;
	}
	if (!IsDirectionAllowChangeSpeed(gear, m_direction))
	{
		return false;
	}
	m_gear = gear;
	return true;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

int CCar::GetGear() const
{
	return m_gear;
}