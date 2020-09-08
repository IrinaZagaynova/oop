#include "Circle.h"
#define _USE_MATH_DEFINES 
#include "stdafx.h"
#include <math.h>

CCircle::CCircle(CPoint const& center, double const& radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea()const
{
	return pow(m_radius, 2) * M_PI;
}

double CCircle::GetPerimeter()const
{
	return 2 * m_radius * M_PI;
}

std::string CCircle::ToString()const
{
	std::ostringstream strm;
	strm << "type - circle\n" <<
		"center - " << "( " << m_center.m_x << "; " << m_center.m_y << " )\n" <<
		"radius - " << m_radius << "\n" <<
		"outline color - " << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor << "\n" <<
		"fill color - " << std::setfill('0') << std::setw(6) << std::hex << m_fillColor << "\n";

	return strm.str();
}

uint32_t CCircle::GetOutlineColor()const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor()const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter()const
{
	return m_center;
}

double CCircle::GetRadius()const
{
	return m_radius;
}
