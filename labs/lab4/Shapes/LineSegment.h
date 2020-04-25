#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	void Draw(ICanvas& canvas) override;

	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_outlineColor;
};