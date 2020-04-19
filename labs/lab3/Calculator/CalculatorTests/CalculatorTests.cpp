#include "../Calculator/Calculator.h"
#include "catch2/catch.hpp"

TEST_CASE("Calculator must not have variables and functions by default")
{
	Calculator calc;
	CHECK(calc.GetVariableValues().empty());
	CHECK(calc.GetFunctionValues().empty());
}

TEST_CASE("Value of the new variable must be nullopt")
{
	Calculator calc;
	Calculator::Values reqValues;
	reqValues = { { "x", std::nullopt } };

	calc.DeclareVariable("x");
	CHECK(reqValues == calc.GetVariableValues());
}

TEST_CASE("If there is already variable with the same identifier, exception must be thrown")
{
	Calculator calc;

	calc.DeclareVariable("x1");
	CHECK_THROWS(calc.DeclareVariable("x1"));

	calc.CreateFunction("f", "x1");
	CHECK_THROWS(calc.DeclareVariable("f"));
}

TEST_CASE("When value is assigned to nonexistent variable, variable must be added")
{
	Calculator calc;
	calc.SetValueToVariable("x1", 1.1);

	Calculator::Values reqValues = { { "x1", 1.1 } };
	CHECK(reqValues == calc.GetVariableValues());
}

TEST_CASE("If one variable is assigned value of nonexistent variable, exception must be thrown")
{
	Calculator calc;
	CHECK_THROWS(calc.SetValueToVariable("x1", "x"));
}

TEST_CASE("SetValueToVariable() must assign to variable a value of another variable or a number")
{
	Calculator calc;
	calc.SetValueToVariable("x1", 1.1);
	calc.SetValueToVariable("x2", "x1");

	Calculator::Values reqValues = { { "x1", 1.1 }, {"x2", 1.1} };
	CHECK(reqValues == calc.GetVariableValues());
}

TEST_CASE("After changing value of variable, values of all related functions must be update")
{
	Calculator calc;
	calc.SetValueToVariable("x", 10.5);
	calc.CreateFunction("func", "x");
	calc.CreateFunction("func1", "x", Function::Operation::Addition, "func");
	calc.CreateFunction("func2", "func1", Function::Operation::Addition, "func");

	Calculator::Values reqValues = { { "func", 10.5 }, { "func1", 21 }, {"func2", 31.5} };
	CHECK(reqValues == calc.GetFunctionValues());

	SECTION("Value of variable changes to a number")
	{
		calc.SetValueToVariable("x", 1);
		reqValues = { { "func", 1 }, { "func1", 2 }, { "func2", 3 } };
		CHECK(reqValues == calc.GetFunctionValues());	
	}
	SECTION("Value of variable changes to value of another variable")
	{
		calc.SetValueToVariable("x1", 1);
		calc.SetValueToVariable("x", "x1");
		reqValues = { { "func", 1 }, { "func1", 2 }, { "func2", 3 } };
		CHECK(reqValues == calc.GetFunctionValues());
	}
}

TEST_CASE("If function name matches one of the identifiers, exception must be thrown")
{
	Calculator calc;
	calc.DeclareVariable("x");
	calc.SetValueToVariable("x1", 1.1);
	CHECK_THROWS(calc.CreateFunction("x", "x1"));
}

TEST_CASE("If function is assigned a nonexistent identifier, there exception must be thrown")
{
	Calculator calc;
	CHECK_THROWS(calc.CreateFunction("f", "x"));
	calc.DeclareVariable("y");
	CHECK_THROWS(calc.CreateFunction("f", "x", Function::Operation::Addition, "y"));
	CHECK_THROWS(calc.CreateFunction("f", "y", Function::Operation::Addition, "x"));
}

TEST_CASE("When creating function, it must be assigned the appropriate value")
{
	Calculator calc;
	calc.SetValueToVariable("x", -1.1);
	calc.CreateFunction("f", "x");
	CHECK(calc.GetValue("f") == -1.1);

	calc.SetValueToVariable("x", 3);
	calc.CreateFunction("f0", "x", Function::Operation::Addition, "x");
	CHECK(calc.GetValue("f0") == 6);
	calc.CreateFunction("f1", "x", Function::Operation::Subtraction, "x");
	CHECK(calc.GetValue("f1") == 0);
	calc.CreateFunction("f2", "x", Function::Operation::Multiplication, "x");
	CHECK(calc.GetValue("f2") == 9);
	calc.CreateFunction("f3", "x", Function::Operation::Division, "x");
	CHECK(calc.GetValue("f3") == 1);
	calc.DeclareVariable("y");
	calc.CreateFunction("f4", "x", Function::Operation::Division, "y");
	CHECK(calc.GetValue("f4") == std::nullopt);

	SECTION("If division by zero then must be nullopt")
	{
		calc.SetValueToVariable("x", 0);
		CHECK(calc.GetValue("f3") == std::nullopt);
	}
}