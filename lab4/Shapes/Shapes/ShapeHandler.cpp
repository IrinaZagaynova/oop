#include "stdafx.h"
#include "ShapeHandler.h"
#include "boost/algorithm/string.hpp"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

using namespace std;
using namespace std::placeholders;

CShapeHandler::CShapeHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
				{ "LineSegment", bind(&CShapeHandler::CreateLineSegment, this, _1) },
				{ "Rectangle", bind(&CShapeHandler::CreateRectangle, this, _1) },
				{ "Triangle", bind(&CShapeHandler::CreateTriangle, this, _1) },
				{ "Circle", bind(&CShapeHandler::CreateCircle, this, _1) },
		})
{
}

bool CShapeHandler::HandleCommand()
{	
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	if (cin.eof())
	{
		return true;
	}

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;				
}

void CShapeHandler::PrintShapeWithMaxArea()const
{
	if (m_shapesList.empty())
	{
		return;
	}

	auto shape = std::max_element(m_shapesList.begin(), m_shapesList.end(), [](const std::shared_ptr<IShape>& sh1, const std::shared_ptr<IShape>& sh2) {
		return sh1->GetArea() < sh2->GetArea();
		});

	m_output << "\n" << (*shape)->ToString();
	m_output << std::setprecision(2) << "area - " << (*shape)->GetArea() << "\n"
		<< "perimeter - " << (*shape)->GetPerimeter() << "\n";
}

void CShapeHandler::PrintShapeWithMinPerimeter()const
{
	if (m_shapesList.empty())
	{
		return;
	}

	auto shape = std::min_element(m_shapesList.begin(), m_shapesList.end(), [](const std::shared_ptr<IShape>& sh1, const std::shared_ptr<IShape>& sh2) {
		return sh1->GetPerimeter() < sh2->GetPerimeter();
		});

	m_output << "\n" <<(*shape)->ToString();
	m_output << std::setprecision(2) << "area - " << (*shape)->GetArea() << "\n"
		<< "perimeter - " << (*shape)->GetPerimeter() << "\n";
}

std::string CShapeHandler::GetShapeInfo()const
{
	if (m_shapesList.empty())
	{
		return "";
	}
	
	return m_shapesList[0]->ToString();
}

bool IsNumber(const string& line)
{
	for (char ch : line)
	{
		if (!isascii(ch) || (!isdigit(ch) && ch != '.'))
		{
			return false;
		}
	}
	return true;
}

bool IsColor(const string& line)
{
	for (char ch : line)
	{
		if (!isascii(ch) || (!isalpha(ch) && !isdigit(ch)))
		{
			return false;
		}
	}
	return true;
}

bool CheckCorrectnessOfShapeParameters(const vector<string>& params, size_t colorsStartPosition)
{
	for (size_t i = 0; i < params.size(); i++)
	{
		if (i < colorsStartPosition)
		{
			if (!IsNumber(params[i]))
			{
				return false;
			}
		}
		else
		{
			if (!IsColor(params[i]))
			{
				return false;
			}
		}
	}

	return true;
}

bool CShapeHandler::CreateLineSegment(std::istream& args)
{
	string line;
	vector<string> params;

	getline(args, line);
	boost::algorithm::trim(line);
	boost::split(params, line, boost::algorithm::is_any_of(" "));
	
	if (params.size() != 5 || !CheckCorrectnessOfShapeParameters(params, 4))
	{
		m_output << "Command entered incorrectly\n";
		return true;
	}

	CPoint startPoint = { stod(params[0]), stod(params[1]) };
	CPoint endPoint = { stod(params[2]), stod(params[3]) };
	uint32_t outlineColor = std::stoul(params[4], 0, 16);
	
	m_shapesList.push_back(std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor));

	return true;
}

bool CShapeHandler::CreateTriangle(istream& args)
{
	string line;
	vector<string> params;

	getline(args, line);
	boost::algorithm::trim(line);
	boost::split(params, line, boost::algorithm::is_any_of(" "));

	if (params.size() != 8 || !CheckCorrectnessOfShapeParameters(params, 6))
	{
		m_output << "Command entered incorrectly\n";
		return true;
	}

	CPoint vertex1 = { stod(params[0]), stod(params[1]) };
	CPoint vertex2 = { stod(params[2]), stod(params[3]) };
	CPoint vertex3 = { stod(params[4]), stod(params[5]) };
	uint32_t outlineColor = std::stoul(params[6], 0, 16);
	uint32_t fillColor = std::stoul(params[7], 0, 16);

	m_shapesList.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));

	return true;
}

bool CShapeHandler::CreateRectangle(istream& args)
{
	string line;
	vector<string> params;

	getline(args, line);
	boost::algorithm::trim(line);
	boost::split(params, line, boost::algorithm::is_any_of(" "));

	if (params.size() != 6 || !CheckCorrectnessOfShapeParameters(params, 4))
	{
		m_output << "Command entered incorrectly\n";
		return true;
	}

	CPoint topLeftCorner = { stod(params[0]), stod(params[1]) };
	double width = stod(params[2]);
	double height = stod(params[3]);
	uint32_t outlineColor = std::stoul(params[4], 0, 16);
	uint32_t fillColor = std::stoul(params[5], 0, 16);

	m_shapesList.push_back(std::make_shared<CRectangle>(topLeftCorner, width, height, outlineColor, fillColor));

	return true;
}

bool CShapeHandler::CreateCircle(istream& args)
{
	string line;
	vector<string> params;

	getline(args, line);
	boost::algorithm::trim(line);
	boost::split(params, line, boost::algorithm::is_any_of(" "));

	if (params.size() != 5 || !CheckCorrectnessOfShapeParameters(params, 3))
	{
		m_output << "Command entered incorrectly\n";
		return true;
	}

	CPoint center = { stod(params[0]), stod(params[1]) };
	double radius = stod(params[2]);
	uint32_t outlineColor = std::stoul(params[3], 0, 16);
	uint32_t fillColor = std::stoul(params[4], 0, 16);

	m_shapesList.push_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));

	return true;
}