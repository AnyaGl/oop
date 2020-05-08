#pragma once
#include <string>

class CPoint
{
public:
	double x = 0;
	double y = 0;
	std::string ToString() const;

	bool operator==(const CPoint& point) const;
};
