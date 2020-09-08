#include "stdafx.h"
#include "../Shapes/Triangle.h"

struct Triangle_
{
	const CPoint expectedVertex1 = { 5, 2 };
	const CPoint expectedVertex2 = { 3, 5 };
	const CPoint expectedVertex3 = { 9, 4 };
	const uint32_t expectedOutlineColor = std::stoul("ff0000", 0, 16);
	const uint32_t expectedFillColor = std::stoul("ff0000", 0, 16);
	const CTriangle triangle;
	Triangle_()
		: triangle(expectedVertex1, expectedVertex2, expectedVertex3, expectedOutlineColor, expectedFillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)

BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const IShape*>(&triangle));
}

BOOST_AUTO_TEST_CASE(is_a_solid_shape)
{
	BOOST_CHECK(static_cast<const ISolidShape*>(&triangle));
}

BOOST_AUTO_TEST_CASE(has_a_three_vertices)
{
	BOOST_CHECK_EQUAL(triangle.GetVertex1().m_x, expectedVertex1.m_x);
	BOOST_CHECK_EQUAL(triangle.GetVertex1().m_y, expectedVertex1.m_y);

	BOOST_CHECK_EQUAL(triangle.GetVertex2().m_x, expectedVertex2.m_x);
	BOOST_CHECK_EQUAL(triangle.GetVertex2().m_y, expectedVertex2.m_y);

	BOOST_CHECK_EQUAL(triangle.GetVertex3().m_x, expectedVertex3.m_x);
	BOOST_CHECK_EQUAL(triangle.GetVertex3().m_y, expectedVertex3.m_y);
}

BOOST_AUTO_TEST_CASE(has_a_outline_color)
{
	BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), expectedOutlineColor);
}

BOOST_AUTO_TEST_CASE(has_a_fill_color)
{
	BOOST_CHECK_EQUAL(triangle.GetFillColor(), expectedFillColor);
}

BOOST_AUTO_TEST_CASE(has_an_area)
{
	BOOST_CHECK_EQUAL(triangle.GetArea(), 8);
}

BOOST_AUTO_TEST_CASE(has_a_perimeter)
{
	BOOST_CHECK_CLOSE_FRACTION(triangle.GetPerimeter(), 14.2, 1e-2);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(type - triangle
vertex1 - ( 5; 2 )
vertex2 - ( 3; 5 )
vertex3 - ( 9; 4 )
outline color - ff0000
fill color - ff0000
)";
	BOOST_CHECK_EQUAL(triangle.ToString(), expectedString);
}

BOOST_AUTO_TEST_SUITE_END()