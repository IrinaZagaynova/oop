#include "stdafx.h"
#include "../Shapes/Circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

struct Circle_
{
	const CPoint expectedCenter = { 11.5, 8 };
	const double expectedRadius = 12.345;
	const uint32_t expectedOutlineColor = std::stoul("ff00", 0, 16);
	const uint32_t expectedFillColor = 0;
	const CCircle circle;
	Circle_()
		: circle(expectedCenter, expectedRadius, expectedOutlineColor, expectedFillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)

BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const IShape*>(&circle));
}

BOOST_AUTO_TEST_CASE(is_a_solid_shape)
{
	BOOST_CHECK(static_cast<const ISolidShape*>(&circle));
}

BOOST_AUTO_TEST_CASE(has_a_center)
{
	BOOST_CHECK_EQUAL(circle.GetCenter().m_x, expectedCenter.m_x);
	BOOST_CHECK_EQUAL(circle.GetCenter().m_y, expectedCenter.m_y);
}

BOOST_AUTO_TEST_CASE(has_a_radius)
{
	BOOST_CHECK_EQUAL(circle.GetRadius(), expectedRadius);
}

BOOST_AUTO_TEST_CASE(has_a_outline_color)
{
	BOOST_CHECK_EQUAL(circle.GetOutlineColor(), expectedOutlineColor);
}

BOOST_AUTO_TEST_CASE(has_a_fill_color)
{
	BOOST_CHECK_EQUAL(circle.GetFillColor(), expectedFillColor);
}

BOOST_AUTO_TEST_CASE(has_an_area)
{
	BOOST_CHECK_EQUAL(circle.GetArea(), pow(expectedRadius, 2) * M_PI);
}

BOOST_AUTO_TEST_CASE(has_a_perimeter)
{
	BOOST_CHECK_EQUAL(circle.GetPerimeter(), 2 * expectedRadius * M_PI);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(type - circle
center - ( 11.5; 8 )
radius - 12.345
outline color - 00ff00
fill color - 000000
)";
	BOOST_CHECK_EQUAL(circle.ToString(), expectedString);
}

BOOST_AUTO_TEST_SUITE_END()
