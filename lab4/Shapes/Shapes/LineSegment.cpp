#include "stdafx.h"
#include "LineSegment.h"

CLineSegment::CLineSegment(CPoint const& startPoint, CPoint const& endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea()const
{
	return 0;
}

double CLineSegment::GetPerimeter()const
{
	return sqrt(pow((m_startPoint.m_x - m_endPoint.m_x), 2) + pow((m_startPoint.m_y - m_endPoint.m_y), 2));
}

std::string CLineSegment::ToString()const
{
	std::ostringstream strm;
	strm << "type - line segment\n" <<
		"start point - " << "( " << m_startPoint.m_x << "; " << m_startPoint.m_y << " )\n" <<
		"end point - " << "( " << m_endPoint.m_x << "; " << m_endPoint.m_y << " )\n" <<
		"outline color - " << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor << "\n";

	return strm.str();
}

uint32_t CLineSegment::GetOutlineColor()const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint()const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint()const
{
	return m_endPoint;
}
