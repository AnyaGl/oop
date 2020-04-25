#include "../Shapes/Circle.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/Point.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/Triangle.h"
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

TEST_CASE("Triangle must be initialized with the passed values")
{
	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 5, 12 };
	CPoint vertex3 = { 5, 0 };
	uint32_t outlineColor = 0;
	uint32_t fillColor = 0xffffff;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	CHECK(triangle.GetVertex1() == vertex1);
	CHECK(triangle.GetVertex2() == vertex2);
	CHECK(triangle.GetVertex3() == vertex3);
	CHECK(triangle.GetOutlineColor() == outlineColor);
	CHECK(triangle.GetFillColor() == fillColor);
}

TEST_CASE("Area and perimeter of triangle must be equal to the corresponding values")
{
	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 5, 12 };
	CPoint vertex3 = { 5, 0 };

	CTriangle triangle(vertex1, vertex2, vertex3, 0, 0xffffff);

	CHECK(triangle.GetArea() == 30);
	CHECK(triangle.GetPerimeter() == 30);
}

TEST_CASE("ToString() must return triangle information")
{
	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 5, 12 };
	CPoint vertex3 = { 5, 0 };

	CTriangle triangle(vertex1, vertex2, vertex3, 0, 0xffffff);
	std::string info = "Type: triangle\nPerimeter: 30.00\nArea: 30.00\nVertex1: (0.00, 0.00)\nVertex2: (5.00, 12.00)\nVertex3: (5.00, 0.00)\nOutline color: 000000\nFill color: ffffff";
	CHECK(triangle.ToString() == info);
}

TEST_CASE("Draw in Triangle must DrawPolygon on Canvas")
{
	CMockCanvas canvas;

	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 5, 12 };
	CPoint vertex3 = { 5, 0 };
	CTriangle triangle(vertex1, vertex2, vertex3, 0, 0xffffff);

	triangle.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawPolygon };
	CHECK(canvas.GetData() == reqData);
}

TEST_CASE("Rectangle must be initialized with the passed values")
{
	CPoint leftTop = { 5, 5.5 };
	double width = 10;
	double height = 5;
	uint32_t outlineColor = 0;
	uint32_t fillColor = 0xffffff;

	CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

	CHECK(rectangle.GetLeftTop() == leftTop);
	CHECK(rectangle.GetWidth() == width);
	CHECK(rectangle.GetHeight() == height);
	CHECK(rectangle.GetOutlineColor() == outlineColor);
	CHECK(rectangle.GetFillColor() == fillColor);
}

TEST_CASE("Right bottom point, area and perimeter of rectangle must be equal to the corresponding values")
{
	CPoint leftTop = { 5, 5.5 };
	double width = 10;
	double height = 5;

	CRectangle rectangle(leftTop, width, height, 0, 0xffffff);

	CHECK(rectangle.GetRightBottom() == CPoint{ 15, 0.5 });
	CHECK(rectangle.GetArea() == 50);
	CHECK(rectangle.GetPerimeter() == 30);
}

TEST_CASE("ToString() must return rectangle information")
{
	CPoint leftTop = { 5, 5.5 };
	double width = 10;
	double height = 5;

	CRectangle rectangle(leftTop, width, height, 0, 0xffffff);
	std::string info = "Type: rectangle\nPerimeter: 30.00\nArea: 50.00\nLeft top point: (5.00, 5.50)\nRight bottom point: (15.00, 0.50)\nWidth: 10.00\nHeight: 5.00\nOutline color: 000000\nFill color: ffffff";
	CHECK(rectangle.ToString() == info);
}

TEST_CASE("Draw in Rectangle must DrawPolygon on Canvas")
{
	CMockCanvas canvas;

	CPoint leftTop = { 5, 5.5 };
	double width = 10;
	double height = 5;
	CRectangle rectangle(leftTop, width, height, 0, 0xffffff);

	rectangle.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawPolygon };
	CHECK(canvas.GetData() == reqData);
}

TEST_CASE("Circle must be initialized with the passed values")
{
	CPoint center = { 5, 0 };
	double radius = 10;
	uint32_t outlineColor = 0;
	uint32_t fillColor = 0xffffff;

	CCircle circle(center, radius, outlineColor, fillColor);

	CHECK(circle.GetCenter() == center);
	CHECK(circle.GetRadius() == radius);
	CHECK(circle.GetOutlineColor() == outlineColor);
	CHECK(circle.GetFillColor() == fillColor);
}

TEST_CASE("Area and perimeter of circle must be equal to the corresponding values")
{
	CPoint center = { 5, 0 };
	double radius = 10;

	CCircle circle(center, radius, 0, 0xffffff);

	CHECK(circle.GetArea() == Approx(314.159).epsilon(0.001));
	CHECK(circle.GetPerimeter() == Approx(62.832).epsilon(0.001));
}

TEST_CASE("ToString() must return circle information")
{
	CPoint center = { 5, 0 };
	double radius = 10;

	CCircle circle(center, radius, 0, 0xffffff);
	std::string info = "Type: circle\nPerimeter: 62.83\nArea: 314.16\nCenter: (5.00, 0.00)\nRadius: 10.00\nOutline color: 000000\nFill color: ffffff";
	CHECK(circle.ToString() == info);
}

TEST_CASE("Draw in Circle must DrawCircle on Canvas")
{
	CMockCanvas canvas;

	CPoint center = { 5, 0 };
	double radius = 10;
	CCircle circle(center, radius, 0, 0xffffff);

	circle.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawCircle };
	CHECK(canvas.GetData() == reqData);
}
