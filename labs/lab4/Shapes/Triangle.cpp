#include "Triangle.h"
#include <iomanip>
#include <iostream>
#include <sstream>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	return abs(0.5 * ((m_vertex1.x - m_vertex3.x) * (m_vertex2.y - m_vertex3.y) - (m_vertex2.x - m_vertex3.x) * (m_vertex1.y - m_vertex3.y)));
}

double GetLength(CPoint point1, CPoint point2)
{
	return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
}

double CTriangle::GetPerimeter() const
{
	return GetLength(m_vertex1, m_vertex2) + GetLength(m_vertex1, m_vertex3) + GetLength(m_vertex3, m_vertex2);
}

std::string CTriangle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	ss << "Type: triangle\nPerimeter: " << GetPerimeter()
	   << "\nArea: " << GetArea()
	   << "\nVertex1: " << m_vertex1.ToString()
	   << "\nVertex2: " << m_vertex2.ToString()
	   << "\nVertex3: " << m_vertex3.ToString()
	   << "\nOutline color: " << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor
	   << "\nFill color: " << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;
	return ss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

void CTriangle::Draw(ICanvas& canvas)
{
	std::vector<CPoint> vertices = { m_vertex1, m_vertex2, m_vertex3 };
	canvas.DrawPolygon(vertices, m_outlineColor, m_fillColor);
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
