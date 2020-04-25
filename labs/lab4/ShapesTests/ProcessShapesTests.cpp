#include "../Shapes/ProcessShapes.h"
#include "catch2/catch.hpp"
#include <sstream>

void VerifyCommandHandling(const std::string& command, const std::string& expectedResult)
{
	std::stringstream input, output;
	CProcessShapes process(input, output);
	input << command;
	CHECK(process.HandleCommand());
	process.GetShapesInfo();
	CHECK(expectedResult == output.str());
}

TEST_CASE("If command is invalid then handle command must return false")
{
	std::stringstream input, output;
	CProcessShapes process(input, output);
	input << "invalid";
	CHECK(!process.HandleCommand());
}

TEST_CASE("Valid command with LineSegment must add line segment to shapes list")
{
	std::string shapesInfo = "Type: line segment\nPerimeter: 13.00\nArea: 0.00\nStart point: (0.00, 0.00)\nEnd point: (5.00, 12.00)\nOutline color: ff00ff\n";
	VerifyCommandHandling("LineSegment 0 0 5 12 ff00ff", shapesInfo);
}

TEST_CASE("Invalid command with LineSegment must print message")
{
	std::string message = "Invalid input\nUsage: LineSegment <start point> <end point> <outline color>\nExample: LineSegment 10.3 20.15 30.7 40.4 ff0000\n";
	VerifyCommandHandling("LineSegment 10*3 20.15 10 10 ff0000", message);
}

TEST_CASE("Valid command with Triangle must add triangle to shapes list")
{
	std::string shapesInfo = "Type: triangle\nPerimeter: 30.00\nArea: 30.00\nVertex1: (0.00, 0.00)\nVertex2: (5.00, 12.00)\nVertex3: (5.00, 0.00)\nOutline color: 000000\nFill color: ffffff\n";
	VerifyCommandHandling("Triangle 0 0 5 12 5 0 000000 ffffff", shapesInfo);
}

TEST_CASE("Invalid command with Triangle must print message")
{
	std::string message = "Invalid input\nUsage: Triangle <vertex1> <vertex2> <vertex3> <outline color> <fill color>\nExample: Triangle 0 3.1 3.5 5.1 0 0 ff0000 00ff00\n";
	VerifyCommandHandling("Triangle 10.3 20.15 ff0000", message);
}

TEST_CASE("Valid command with Rectangle must add rectangle to shapes list")
{
	std::string shapesInfo = "Type: rectangle\nPerimeter: 30.00\nArea: 50.00\nLeft top point: (5.00, 5.50)\nRight bottom point: (15.00, 0.50)\nWidth: 10.00\nHeight: 5.00\nOutline color: 000000\nFill color: ffffff\n";
	VerifyCommandHandling("Rectangle 5 5.5 10 5 000000 FFFFFF", shapesInfo);
}

TEST_CASE("Invalid command with Rectangle must print message")
{
	std::string message = "Invalid input\nUsage: Rectangle <left top vertex> <width> <height> <outline color> <fill color>\nExample: Rectangle 5 3.2 4 5.2 ff0000 00ff00\n";
	VerifyCommandHandling("Rectangle 0 10.3 20.15 11 ffffff zxc", message);
}

TEST_CASE("Valid command with Circle must add circle to shapes list")
{
	std::string shapesInfo = "Type: circle\nPerimeter: 62.83\nArea: 314.16\nCenter: (5.00, 0.00)\nRadius: 10.00\nOutline color: 000000\nFill color: ffffff\n";
	VerifyCommandHandling("Circle 5 0 10 000000 ffffff", shapesInfo);
}

TEST_CASE("Invalid command with Circle must print message")
{
	std::string message = "Invalid input\nUsage: Circle <center> <radius> <outline color> <fill color>\nExample: Circle 0 3.1 5.1 ff0000 00ff00\n";
	VerifyCommandHandling("Circle 0 10.3 20.15 11 ffffff zxc", message);
}

TEST_CASE("If shapes list is empty then PrintShapeWithMaxArea() must print message")
{
	std::stringstream input, output;
	CProcessShapes process(input, output);
	process.PrintShapeWithMaxArea();
	CHECK(output.str() == "Impossible to find shape with max area. List of shapes is empty.\n");
}

TEST_CASE("If shapes list isn't empty then PrintShapeWithMaxArea() must print shape with max area")
{
	std::stringstream input, output;
	CProcessShapes process(input, output);

	input << "Rectangle 5 10 20 10 000000 ffffff" << std::endl
		  << "Circle 5 0 10 000000 ffffff";
	while (!input.eof())
	{
		process.HandleCommand();
	}

	process.PrintShapeWithMaxArea();
	std::string shapeInfo = "\nShape with max area:\nType: circle\nPerimeter: 62.83\nArea: 314.16\nCenter: (5.00, 0.00)\nRadius: 10.00\nOutline color: 000000\nFill color: ffffff\n";
	CHECK(output.str() == shapeInfo);
}

TEST_CASE("If shapes list is empty then PrintShapeWithMinPerimeter() must print message")
{
	std::stringstream input, output;
	CProcessShapes process(input, output);
	process.PrintShapeWithMinPerimeter();
	CHECK(output.str() == "Impossible to find shape with min perimeter. List of shapes is empty.\n");
}

TEST_CASE("If shapes list isn't empty then PrintShapeWithMinPerimeter() must print shape with min perimeter")
{
	std::stringstream input, output;
	CProcessShapes process(input, output);

	input << "Rectangle 5 10 20 10 000000 ffffff" << std::endl
		  << "Circle 5 0 10 000000 ffffff";
	while (!input.eof())
	{
		process.HandleCommand();
	}

	process.PrintShapeWithMinPerimeter();
	std::string shapeInfo = "\nShape with min perimeter:\nType: rectangle\nPerimeter: 60.00\nArea: 200.00\nLeft top point: (5.00, 10.00)\nRight bottom point: (25.00, 0.00)\nWidth: 20.00\nHeight: 10.00\nOutline color: 000000\nFill color: ffffff\n";
	CHECK(output.str() == shapeInfo);
}
