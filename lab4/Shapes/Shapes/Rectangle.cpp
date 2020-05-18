#include "Rectangle.h"
#include "stdafx.h"

CRectangle::CRectangle(CPoint const& topLeftCorner, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_topLeftCorner(topLeftCorner)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea()const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter()const
{
	return 2 * (m_width + m_height);
}

std::string CRectangle::ToString()const
{
	std::ostringstream strm;
	strm << "type - rectangle\n" <<
		"top left corner - " << "( " << m_topLeftCorner.m_x << "; " << m_topLeftCorner.m_y << " )\n" <<
		"width - " << m_width << "\n" <<
		"height - " << m_height << "\n" <<
		"outline color - " << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor << "\n" <<
		"fill color - " << std::setfill('0') << std::setw(6) << std::hex << m_fillColor << "\n";

	return strm.str();
}

uint32_t CRectangle::GetOutlineColor()const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor()const
{
	return m_fillColor;
}

double CRectangle::GetWidth()const
{
	return m_width;
}

double CRectangle::GetHeight()const
{
	return m_height;
}

CPoint CRectangle::GetTopLeftCorner() const
{
	return m_topLeftCorner;
}

CPoint CRectangle::GetBottomRightCorner()const
{
	CPoint bottomRightCorner;
	bottomRightCorner.m_x = m_topLeftCorner.m_x + m_width;
	bottomRightCorner.m_y = m_topLeftCorner.m_y - m_height;

	return bottomRightCorner;
}
