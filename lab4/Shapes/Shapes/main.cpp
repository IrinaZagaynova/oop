#include "stdafx.h"
#include "ShapeHandler.h"

int main()
{
	std::cout << "Use to create shapes: \n" <<
		"<LineSegment> <start point x> <start point y> <end point x> <end point y> <outline color>\n" <<
		"<Triangle> <vertex1 x> <vertex1 y> <vertex2 x> <vertex2 y> <vertex3 x> <vertex3 y> <outline color> <fill color>\n" <<
		"<Rectangle> <top left corner x> <top left corner y> <width> <height> <outline color> <fill color>\n" <<
		"<Circle> <center x> <center y> <radius> <outline color> <fill color>\n";

	CShapeHandler ShapeHandler(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!ShapeHandler.HandleCommand())
		{
			std::cout << "Unknown command!" << "\n";
		}
	}
	
	ShapeHandler.PrintShapeWithMaxArea();
	ShapeHandler.PrintShapeWithMinPerimeter();

    return 0;
}