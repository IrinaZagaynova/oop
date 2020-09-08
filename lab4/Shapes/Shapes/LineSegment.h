#pragma once
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint const& startPoint, CPoint const& endPoint, uint32_t outlineColor);
	double GetArea()const override;
	double GetPerimeter()const override;
	std::string ToString()const override;
	uint32_t GetOutlineColor()const override;
	CPoint GetStartPoint()const;
	CPoint GetEndPoint()const;
private:
	uint32_t m_outlineColor;
	CPoint m_startPoint, m_endPoint;
};