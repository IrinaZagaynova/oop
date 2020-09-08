#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	uint32_t virtual GetFillColor()const = 0;
};