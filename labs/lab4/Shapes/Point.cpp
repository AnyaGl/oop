#include "Point.h"
#include <iomanip>
#include <sstream>

std::string CPoint::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	ss << "(" << x << ", " << y << ")";
	return ss.str();
}

bool CPoint::operator==(const CPoint& point) const
{
	return (this->x == point.x) && (this->y == point.y);
}
