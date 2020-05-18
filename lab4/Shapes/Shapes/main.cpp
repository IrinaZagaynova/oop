#include "stdafx.h"
#include "ShapeHandler.h"

int main()
{
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