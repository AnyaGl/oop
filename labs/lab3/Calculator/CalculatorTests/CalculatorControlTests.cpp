#include "../Calculator/CalculatorControl.h"
#include "catch2/catch.hpp"
#include <sstream>

void VerifyCommandHandling(Calculator& calc, const std::string& command, const std::string& expectedResult = "")
{
	std::stringstream input, output;
	CalculatorControl control(calc, input, output);
	input << command;
	CHECK(control.StartHandler());
	CHECK(expectedResult == output.str());
}

TEST_CASE("If command is invalid, handler must return false")
{
	Calculator calc;
	std::stringstream input, output;
	CalculatorControl control(calc, input, output);
	input << "unknown";
	CHECK(!control.StartHandler());
} 

TEST_CASE("If variable was successfully declared then nothing must be output")
{
	Calculator calc;
	VerifyCommandHandling(calc, "var x");
}

TEST_CASE("If the assignment was successful, then nothing must be output")
{
	Calculator calc;
	VerifyCommandHandling(calc, "let x=1.1");
	VerifyCommandHandling(calc, "let y=x");
}

TEST_CASE("If action is invalid, then message is returned")
{
	Calculator calc;
	VerifyCommandHandling(calc, "let x 1", "Invalid command\n");
	VerifyCommandHandling(calc, "fn f-x+y", "Invalid command\n");
}

TEST_CASE("If identifier name is invalid, then message is returned")
{
	Calculator calc;
	VerifyCommandHandling(calc, "let 1x=x", "Invalid identifier name\n");
	VerifyCommandHandling(calc, "fn _x12*=x", "Invalid identifier name\n");
}

TEST_CASE("When function is correctly created, nothing must be output")
{
	Calculator calc;
	calc.SetValueToVariable("x", 1.1);
	VerifyCommandHandling(calc, "fn f=x");
	VerifyCommandHandling(calc, "fn f1=x+x");
	VerifyCommandHandling(calc, "fn f2=x-x");
	VerifyCommandHandling(calc, "fn f3=x*x");
	VerifyCommandHandling(calc, "fn f4=x/x");
}

TEST_CASE("Print() must output identifier value")
{
	Calculator calc;
	calc.SetValueToVariable("x", 1.1);
	VerifyCommandHandling(calc, "print x", "1.10\n");

	calc.CreateFunction("f1", "x", Function::Operation::Addition, "x");
	VerifyCommandHandling(calc, "print f1", "2.20\n");
}

TEST_CASE("PrintVars() must output values of all variables in alphabetical order")
{
	Calculator calc;
	calc.SetValueToVariable("b", 111);
	calc.SetValueToVariable("c", 1.1);
	calc.SetValueToVariable("a", 10.127);
	calc.DeclareVariable("d");
	VerifyCommandHandling(calc, "printvars", "a:10.13\nb:111.00\nc:1.10\nd:nan\n");
}

TEST_CASE("PrintFns() must output values of all functions in alphabetical order")
{
	Calculator calc;
	calc.SetValueToVariable("a", 1);
	calc.SetValueToVariable("c", 0);
	calc.DeclareVariable("b");
	calc.CreateFunction("f", "a", Function::Operation::Subtraction, "b");
	calc.CreateFunction("f1", "a", Function::Operation::Division, "c");
	calc.CreateFunction("f2", "a", Function::Operation::Addition, "c");

	VerifyCommandHandling(calc, "printfns", "f:nan\nf1:nan\nf2:1.00\n");
}
