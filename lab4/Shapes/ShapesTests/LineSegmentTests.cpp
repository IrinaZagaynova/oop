#include "stdafx.h"
#include "../Shapes/LineSegment.h"

struct LineSegment_
{
	const CPoint expectedStartPoint = { 5, 0 };
	const CPoint expectedEndPoint = { 10, 20 };
	const uint32_t expectedOutlineColor = std::stoul("ff0000", 0, 16);
	CLineSegment lineSegment;
	LineSegment_()
		: lineSegment(expectedStartPoint, expectedEndPoint, expectedOutlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegment_)

BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const IShape*>(&lineSegment));
}

BOOST_AUTO_TEST_CASE(has_a_start_point)
{
	BOOST_CHECK_EQUAL(lineSegment.GetStartPoint().m_x, expectedStartPoint.m_x);
	BOOST_CHECK_EQUAL(lineSegment.GetStartPoint().m_y, expectedStartPoint.m_y);
}

BOOST_AUTO_TEST_CASE(has_a_end_point)
{
	BOOST_CHECK_EQUAL(lineSegment.GetEndPoint().m_x, expectedEndPoint.m_x);
	BOOST_CHECK_EQUAL(lineSegment.GetEndPoint().m_y, expectedEndPoint.m_y);
}

BOOST_AUTO_TEST_CASE(has_a_outline_color)
{
	BOOST_CHECK_EQUAL(lineSegment.GetOutlineColor(), expectedOutlineColor);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(type - line segment
start point - ( 5; 0 )
end point - ( 10; 20 )
outline color - ff0000
)";
	BOOST_CHECK_EQUAL(lineSegment.ToString(), expectedString);
}

BOOST_AUTO_TEST_SUITE_END()
