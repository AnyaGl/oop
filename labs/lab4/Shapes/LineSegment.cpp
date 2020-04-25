#include "LineSegment.h"
#include <iomanip>
#include <sstream>
#include <string>

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow((m_endPoint.x - m_startPoint.x), 2) + pow((m_endPoint.y - m_startPoint.y), 2));
}

std::string CLineSegment::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	ss << "Type: line segment\nPerimeter: " << GetPerimeter()
	   << "\nArea: " << GetArea()
	   << "\nStart point: " << m_startPoint.ToString()
	   << "\nEnd point: " << m_endPoint.ToString()
	   << "\nOutline color: " << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor;
	return ss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}

CPoint CLineSegment::GetStartPoint()
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint()
{
	return m_endPoint;
}
