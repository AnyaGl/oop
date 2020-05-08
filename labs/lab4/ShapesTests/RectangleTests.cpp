#include "../Shapes/Rectangle.h"
#include "MockCanvas.h"
#include "catch2/catch.hpp"

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


