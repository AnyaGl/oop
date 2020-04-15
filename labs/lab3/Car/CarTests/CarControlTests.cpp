#include "../Car/Car.h"
#include "../Car/CarControl.h"
#include "catch2/catch.hpp"
#include <sstream>

void VerifyCommandHandling(const std::string& command, const std::string& expectedResult, CCar& car)
{
	std::stringstream input, output;
	CCarControl carControl(car, input, output);
	input << command;
	CHECK(carControl.HandleCommand());
	CHECK(expectedResult == output.str());
}

TEST_CASE("Handle command EngineOn must return behavior")
{
	CCar car;
	VerifyCommandHandling("EngineOn", "Engine is on\n", car);
}

TEST_CASE("Handle command EngineOff must return behavior")
{
	CCar car;
	car.TurnOnEngine();
	VerifyCommandHandling("EngineOff", "Engine is off\n", car);

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	VerifyCommandHandling("EngineOff", "Failed to turn off engine\nSpeed must be 0 and gear must be neutral\n", car);
}

TEST_CASE("Handle command Info must return car status")
{
	CCar car;
	VerifyCommandHandling("Info", "Engine status: off\nSpeed: 0\nDirection: stand\nGear: neutral\n", car);

	car.TurnOnEngine();
	VerifyCommandHandling("Info", "Engine status: on\nSpeed: 0\nDirection: stand\nGear: neutral\n", car);

	car.SetGear(1);
	car.SetSpeed(20);
	VerifyCommandHandling("Info", "Engine status: on\nSpeed: 20\nDirection: forward\nGear: first\n", car);

	car.SetSpeed(0);
	car.SetGear(-1);
	car.SetSpeed(10);
	VerifyCommandHandling("Info", "Engine status: on\nSpeed: 10\nDirection: back\nGear: reverse\n", car);
}

TEST_CASE("Handle command SetSpeed must return behavior")
{
	CCar car;
	car.TurnOnEngine();
	VerifyCommandHandling("SetSpeed 10", "Speed didn't change\n", car);

	car.SetGear(1);
	car.SetSpeed(20);
	VerifyCommandHandling("SetSpeed 20", "Now speed is 20\n", car);
}

TEST_CASE("Handle command SetGear must return behavior")
{
	CCar car;
	car.TurnOnEngine();
	
	VerifyCommandHandling("SetGear 4", "Gear didn't change\n", car);

	VerifyCommandHandling("SetGear -1", "Gear is changed to reverse\n", car);
}

TEST_CASE("Handle command must not be case sensitive")
{
	CCar car;
	VerifyCommandHandling("engineon", "Engine is on\n", car);

	VerifyCommandHandling("SETGEAR 1", "Gear is changed to first\n", car);
}

TEST_CASE("If command is invalid then handle command must return false")
{
	CCar car;
	std::stringstream input, output;
	CCarControl carControl(car, input, output);
	input << "invalid command";
	CHECK(!carControl.HandleCommand());
}