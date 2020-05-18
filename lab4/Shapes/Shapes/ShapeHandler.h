#pragma once
#include "stdafx.h"
#include "IShape.h"

class CShapeHandler
{
public:
	CShapeHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintShapeWithMaxArea()const;
	void PrintShapeWithMinPerimeter()const;
	std::string GetShapeInfo()const;
private:
	bool CreateLineSegment(std::istream& args);
	bool CreateTriangle(std::istream& args);
	bool CreateRectangle(std::istream& args);
	bool CreateCircle(std::istream& args);
	std::vector<std::shared_ptr<IShape>> m_shapesList;
private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};