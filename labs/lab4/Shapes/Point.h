#pragma once
#include <string>

class CPoint
{
public:
	double x;
	double y;
	std::string ToString() const;

	bool operator==(const CPoint& point) const;
};
