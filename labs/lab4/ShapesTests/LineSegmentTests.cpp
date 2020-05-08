#include "../Shapes/LineSegment.h"
#include "MockCanvas.h"
#include "catch2/catch.hpp"

TEST_CASE("Line segment must be initialized with the passed values")
{
	CPoint pointFrom = { 0, 0 };
	CPoint pointTo = { 5, 12 };
	CLineSegment line(pointFrom, pointTo, 0xff00ff);

	CHECK(line.GetStartPoint() == pointFrom);
	CHECK(line.GetEndPoint() == pointTo);
	CHECK(line.GetOutlineColor() == 0xff00ff);
}

TEST_CASE("Area of the segment = 0, perimeter of the segment = length of the segment")
{
	CPoint pointFrom = { 0, 0 };
	CPoint pointTo = { 5, 12 };
	CLineSegment line(pointFrom, pointTo, 0xff00ff);

	CHECK(line.GetArea() == 0);
	CHECK(line.GetPerimeter() == 13);
}

TEST_CASE("ToString() must return line segment information")
{
	CPoint pointFrom = { 0, 0 };
	CPoint pointTo = { 5, 12 };
	CLineSegment line(pointFrom, pointTo, 0xff00ff);

	std::string info = "Type: line segment\nPerimeter: 13.00\nArea: 0.00\nStart point: (0.00, 0.00)\nEnd point: (5.00, 12.00)\nOutline color: ff00ff";
	CHECK(line.ToString() == info);
}

TEST_CASE("Draw in LineSegment must DrawLine on Canvas")
{
	CMockCanvas canvas;

	CPoint pointFrom = { 0, 0 };
	CPoint pointTo = { 5, 12 };
	CLineSegment line(pointFrom, pointTo, 0xff00ff);

	line.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawLine };
	CHECK(canvas.GetData() == reqData);
}
