#include "stdafx.h"
#include "../Shapes/Rectangle.h"

struct Rectangle_
{
	const CPoint expectedTopLeftCorner = { 5, 2 };
	const double expectedWidth = 8;
	const double expectedHeight = 5;
	const uint32_t expectedOutlineColor = std::stoul("ff0000", 0, 16);
	const uint32_t expectedFillColor = std::stoul("00ff00", 0, 16);
	const CRectangle rectangle;
	Rectangle_()
		: rectangle(expectedTopLeftCorner, expectedWidth, expectedHeight, expectedOutlineColor, expectedFillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)

BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const IShape*>(&rectangle));
}

BOOST_AUTO_TEST_CASE(is_a_solid_shape)
{
	BOOST_CHECK(static_cast<const ISolidShape*>(&rectangle));
}

BOOST_AUTO_TEST_CASE(has_a_width)
{
	BOOST_CHECK_EQUAL(rectangle.GetWidth(), expectedWidth);
}

BOOST_AUTO_TEST_CASE(has_a_height)
{
	BOOST_CHECK_EQUAL(rectangle.GetHeight(), expectedHeight);
}

BOOST_AUTO_TEST_CASE(has_a_outline_color)
{
	BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), expectedOutlineColor);
}

BOOST_AUTO_TEST_CASE(has_a_fill_color)
{
	BOOST_CHECK_EQUAL(rectangle.GetFillColor(), expectedFillColor);
}

BOOST_AUTO_TEST_CASE(has_an_area)
{
	BOOST_CHECK_EQUAL(rectangle.GetArea(), expectedWidth * expectedHeight);
}

BOOST_AUTO_TEST_CASE(has_a_perimeter)
{
	BOOST_CHECK_EQUAL(rectangle.GetPerimeter(), 2 * (expectedWidth + expectedHeight));
}

BOOST_AUTO_TEST_CASE(has_a_coordinates_top_left_corner)
{
	BOOST_CHECK_EQUAL(rectangle.GetTopLeftCorner().m_x, expectedTopLeftCorner.m_x);
	BOOST_CHECK_EQUAL(rectangle.GetTopLeftCorner().m_y, expectedTopLeftCorner.m_y);
}

BOOST_AUTO_TEST_CASE(has_a_coordinates_bottom_right_corner)
{
	BOOST_CHECK_EQUAL(rectangle.GetBottomRightCorner().m_x, expectedTopLeftCorner.m_x + expectedWidth);
	BOOST_CHECK_EQUAL(rectangle.GetBottomRightCorner().m_y, expectedTopLeftCorner.m_y - expectedHeight);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(type - rectangle
top left corner - ( 5; 2 )
width - 8
height - 5
outline color - ff0000
fill color - 00ff00
)";
	BOOST_CHECK_EQUAL(rectangle.ToString(), expectedString);
}

BOOST_AUTO_TEST_SUITE_END()