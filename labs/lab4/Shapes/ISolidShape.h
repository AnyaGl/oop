#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape(){};
	virtual uint32_t GetFillColor() const = 0;
};
