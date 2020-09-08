#include "Triangle.h"
#include "stdafx.h"

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetPerimeter()const
{
	double lengthA = sqrt(pow((m_vertex1.m_x - m_vertex2.m_x), 2) + pow((m_vertex1.m_y - m_vertex2.m_y), 2));
	double lengthB = sqrt(pow((m_vertex1.m_x - m_vertex3.m_x), 2) + pow((m_vertex1.m_y - m_vertex3.m_y), 2));
	double lengthC = sqrt(pow((m_vertex2.m_x - m_vertex3.m_x), 2) + pow((m_vertex2.m_y - m_vertex3.m_y), 2));

	return (lengthA + lengthB + lengthC);
}

double CTriangle::GetArea()const
{
	double s = 0.5 * fabs((m_vertex1.m_x - m_vertex3.m_x) * (m_vertex2.m_y - m_vertex3.m_y) - (m_vertex2.m_x - m_vertex3.m_x) * (m_vertex1.m_y - m_vertex3.m_y));

	return s;
}

std::string CTriangle::ToString()const
{
	std::ostringstream strm;
	strm << "type - triangle\n" <<
		"vertex1 - " << "( " << m_vertex1.m_x << "; " << m_vertex1.m_y << " )\n" <<
		"vertex2 - " << "( " << m_vertex2.m_x << "; " << m_vertex2.m_y << " )\n" <<
		"vertex3 - " << "( " << m_vertex3.m_x << "; " << m_vertex3.m_y << " )\n" <<
		"outline color - " << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor << "\n" <<
		"fill color - " << std::setfill('0') << std::setw(6) << std::hex << m_fillColor << "\n";

	return strm.str();
}

uint32_t CTriangle::GetOutlineColor()const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor()const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1()const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2()const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3()const
{
	return  m_vertex3;
}

