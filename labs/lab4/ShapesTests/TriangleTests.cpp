#include "../Shapes/Triangle.h"
#include "MockCanvas.h"
#include "catch2/catch.hpp"

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