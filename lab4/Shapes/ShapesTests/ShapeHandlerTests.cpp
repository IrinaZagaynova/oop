#include "stdafx.h"
#include "../Shapes/ShapeHandler.h"

struct ShapeHandlerlDependencies
{
	std::stringstream input;
	std::stringstream output;
};

struct ShapeHandlerFixture : ShapeHandlerlDependencies
{
	CShapeHandler menu;

	ShapeHandlerFixture()
		: menu(input, output)
	{
	}

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(menu.HandleCommand());
		BOOST_CHECK(input.eof());
		output << menu.GetShapeInfo();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapeHandler, ShapeHandlerFixture)

BOOST_AUTO_TEST_CASE(can_create_line_segment)
{
	std::ostringstream strm;
	strm << R"(type - line segment
start point - ( 5; 0 )
end point - ( 10; 20 )
outline color - ff0000
)";
	std::string expected = strm.str();
	VerifyCommandHandling("LineSegment 5 0 10 20 ff0000", expected);
}

BOOST_AUTO_TEST_CASE(cant_create_line_segment_if_command_entered_incorrectly)
{
	std::string expected = "Command entered incorrectly\n";
	VerifyCommandHandling("LineSegment 5 6 8 7 00ff00 0", expected);
	VerifyCommandHandling("LineSegment 5 6 7 00ff00", expected);
	VerifyCommandHandling("LineSegment 5 6 8 A 00ff00", expected);
	VerifyCommandHandling("LineSegment 5 0 10 20 ff000É", expected);
}

BOOST_AUTO_TEST_CASE(can_create_triangle)
{
	std::ostringstream strm;
	strm << R"(type - triangle
vertex1 - ( 5; 2 )
vertex2 - ( 3; 5 )
vertex3 - ( 9; 4 )
outline color - ff0000
fill color - ff0000
)";
	std::string expected = strm.str();
	VerifyCommandHandling("Triangle 5 2 3 5 9 4 ff0000 ff0000", expected);
}

BOOST_AUTO_TEST_CASE(cant_create_triangle_if_command_entered_incorrectly)
{
	std::string expected = "Command entered incorrectly\n";
	VerifyCommandHandling("Triangle 5 2 3 5 9 4 5 0 0", expected);
	VerifyCommandHandling("Triangle 5 2 3 5 9 4 0", expected);	
	VerifyCommandHandling("Triangle 5 A 3 5 9 4 0 0", expected);
	VerifyCommandHandling("Triangle 5 2 3 5 9 4 Éf0000 0", expected);
}

BOOST_AUTO_TEST_CASE(can_create_rectangle)
{
	std::ostringstream strm;
	strm << R"(type - rectangle
top left corner - ( 5; 6 )
width - 8
height - 7
outline color - ff0000
fill color - 00ff00
)";
	std::string expected = strm.str();
	VerifyCommandHandling("Rectangle 5 6 8 7 ff0000 ff00", expected);
}

BOOST_AUTO_TEST_CASE(cant_create_rectangle_if_command_entered_incorrectly)
{
	std::string expected = "Command entered incorrectly\n";
	VerifyCommandHandling("Rectangle 5 6 8 7 0 0 0 ", expected);
	VerifyCommandHandling("Rectangle 5 6 8 7 0", expected);
	VerifyCommandHandling("Rectangle 5 6 A 7 0 0", expected);
	VerifyCommandHandling("Rectangle 5 6 8 7 ff0000 ff0É", expected);
}

BOOST_AUTO_TEST_CASE(can_create_circle)
{
	std::ostringstream strm;
	strm << R"(type - circle
center - ( 11.5; 8 )
radius - 12.345
outline color - 00ff00
fill color - 000000
)";
	std::string expected = strm.str();
	VerifyCommandHandling("Circle 11.5 8 12.345 00ff00 0", expected);
}

BOOST_AUTO_TEST_CASE(cant_create_circle_if_command_entered_incorrectly)
{
	std::string expected = "Command entered incorrectly\n";
	VerifyCommandHandling("Circle 11.5 8 12.345 5 0 0", expected);
	VerifyCommandHandling("Circle 11.5 8 12.345 0", expected);
	VerifyCommandHandling("Circle 11.5 8 A 0 0", expected);
	VerifyCommandHandling("Circle 11.5 8 12.345 00ff0É 0", expected);
}

BOOST_AUTO_TEST_SUITE_END()

struct when_shapes_are_created_ : ShapeHandlerFixture
{
	when_shapes_are_created_()
	{
		input << "LineSegment 5 0 10 20 ff0000";
		menu.HandleCommand();
		input = std::stringstream();
		input << "Rectangle 5 6 8 7 ff0000 ff00";
		menu.HandleCommand();
		input = std::stringstream();
		input << "Circle 11.5 8 12.345 ff00 0";
		menu.HandleCommand();
		input = std::stringstream();
		input << "Triangle 5 2 3 5 9 4 ff0000 ff0000";
		menu.HandleCommand();
	}
};

BOOST_FIXTURE_TEST_SUITE(when_shapes_are_created, when_shapes_are_created_)

BOOST_AUTO_TEST_CASE(can_print_info_about_shape_with_max_area)
{
	std::ostringstream strm;
	strm << R"(
type - circle
center - ( 11.5; 8 )
radius - 12.345
outline color - 00ff00
fill color - 000000
area - 4.8e+02
perimeter - 78
)";
	menu.PrintShapeWithMaxArea();
	BOOST_CHECK_EQUAL(output.str(), strm.str());
}

BOOST_AUTO_TEST_CASE(can_print_info_about_shape_with_min_perimeter)
{
	std::ostringstream strm;
	strm << R"(
type - triangle
vertex1 - ( 5; 2 )
vertex2 - ( 3; 5 )
vertex3 - ( 9; 4 )
outline color - ff0000
fill color - ff0000
area - 8
perimeter - 14
)";
	menu.PrintShapeWithMinPerimeter();
	BOOST_CHECK_EQUAL(output.str(), strm.str());
}

BOOST_AUTO_TEST_SUITE_END()