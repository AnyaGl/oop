#include "../Shapes/Circle.h"
#include "MockCanvas.h"
#include "catch2/catch.hpp"

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
