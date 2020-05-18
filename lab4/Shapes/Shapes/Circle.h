#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint const& center, double const& radius, uint32_t outlineColor, uint32_t fillColor);
	double GetArea()const override;
	double GetPerimeter()const override;
	std::string ToString()const override;
	uint32_t GetOutlineColor()const override;
	uint32_t GetFillColor()const override;
	CPoint GetCenter()const;
	double GetRadius()const;
private:
	CPoint m_center; 
	double m_radius;
	uint32_t m_outlineColor, m_fillColor;
}; 