#pragma once
#include "Point.h"
#include <cstdint>
#include <string>

class IShape
{
public:
	double virtual GetArea()const = 0;
	double virtual GetPerimeter()const = 0;
	std::string virtual ToString()const = 0;
	uint32_t virtual GetOutlineColor()const = 0;
	virtual ~IShape() {};
};