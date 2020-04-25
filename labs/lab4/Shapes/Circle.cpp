#define _USE_MATH_DEFINES
#include "Circle.h"
#include <iomanip>
#include <sstream>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	ss << "Type: circle\nPerimeter: " << GetPerimeter()
	   << "\nArea: " << GetArea()
	   << "\nCenter: " << m_center.ToString()
	   << "\nRadius: " << m_radius
	   << "\nOutline color: " << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor
	   << "\nFill color: " << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;
	return ss.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor, m_fillColor);
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
