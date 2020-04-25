#pragma once
#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable(){};
	virtual void Draw(ICanvas& canvas) = 0;
};
