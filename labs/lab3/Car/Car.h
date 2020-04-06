#pragma once
#include <utility>

enum class Direction 
{
	Forward,
	Back,
	Stand
};

const std::pair<int, int> REVERSE_SPEED_RANGE = { 0, 20 };
const std::pair<int, int> NEUTRAL_SPEED_RANGE = { 0, 150 };
const std::pair<int, int> FIRST_SPEED_RANGE = { 0, 30 };
const std::pair<int, int> SECOND_SPEED_RANGE = { 20, 50 };
const std::pair<int, int> THIRD_SPEED_RANGE = { 30, 60 };
const std::pair<int, int> FOURTH_SPEED_RANGE = { 40, 90 };
const std::pair<int, int> FIFTH_SPEED_RANGE = { 50, 150 };

class CCar
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool IsEngineOn() const;

	bool SetGear(int gear);
	int GetGear() const;

	bool SetSpeed(int speed);
	int GetSpeed() const;

	Direction GetDirection() const;
private:
	bool m_isEngineOn = false;
	Direction m_direction = Direction::Stand;
	int m_speed = 0;
	int m_gear = 0;
};
