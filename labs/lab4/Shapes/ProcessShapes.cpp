#include "ProcessShapes.h"
#include <algorithm>
#include <sstream>

CProcessShapes::CProcessShapes(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { "LineSegment", std::bind(&CProcessShapes::AddLineSegment, this, std::placeholders::_1) },
		  { "Rectangle", std::bind(&CProcessShapes::AddRectangle, this, std::placeholders::_1) },
		  { "Triangle", std::bind(&CProcessShapes::AddTriangle, this, std::placeholders::_1) },
		  { "Circle", std::bind(&CProcessShapes::AddCircle, this, std::placeholders::_1) } })
{
}

bool CProcessShapes::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string shape;
	strm >> shape;

	auto it = m_actionMap.find(shape);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

void CProcessShapes::PrintShapeWithMaxArea() const
{
	if (m_shapesList.empty())
	{
		m_output << "Impossible to find shape with max area. List of shapes is empty.\n";
		return;
	}
	auto shapeWithMaxArea = std::max_element(m_shapesList.begin(), m_shapesList.end(), [](const auto& shape1, const auto& shape2) {
		return shape1->GetArea() < shape2->GetArea();
	});
	m_output << "\nShape with max area:\n"
			 << (*shapeWithMaxArea)->ToString() << std::endl;
}

void CProcessShapes::PrintShapeWithMinPerimeter() const
{
	if (m_shapesList.empty())
	{
		m_output << "Impossible to find shape with min perimeter. List of shapes is empty.\n";
		return;
	}
	auto shapeWithMinPerimeter = std::min_element(m_shapesList.begin(), m_shapesList.end(), [](const auto& shape1, const auto& shape2) {
		return shape1->GetPerimeter() < shape2->GetPerimeter();
	});
	m_output << "\nShape with min perimeter:\n"
			 << (*shapeWithMinPerimeter)->ToString() << std::endl;
}

void CProcessShapes::DrawShapes() const
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(600, 600), "Shapes", sf::Style::Default, settings);
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color(255, 255, 255));
		for (auto shape : m_shapesList)
		{
			shape->Draw(canvas);
		}
		window.display();
	}
}

void CProcessShapes::GetShapesInfo() const
{
	for (auto shape : m_shapesList)
	{
		m_output << (*shape).ToString() << std::endl;
	}
}

std::vector<std::string> ParseCommand(std::istream& commandLine)
{
	std::vector<std::string> params;
	std::string param;

	while (!commandLine.eof() && !commandLine.fail())
	{
		commandLine >> param;
		params.push_back(param);
	}
	return params;
}

bool IsNumbers(const std::vector<std::string>& params, size_t from, size_t to)
{
	for (size_t i = from; i < to; i++)
	{
		for (auto ch : params[i])
		{
			if (!std::isdigit(ch) && ch != '.')
			{
				return false;
			}
		}
	}
	return true;
}

bool IsColors(const std::vector<std::string>& params, size_t from, size_t to)
{
	for (size_t i = from; i < to; i++)
	{
		for (auto ch : params[i])
		{
			if (!std::isdigit(ch) && (ch < 'a' || ch > 'f') && (ch < 'A' || ch > 'F'))
			{
				return false;
			}
		}
	}
	return true;
}

bool CProcessShapes::AddLineSegment(std::istream& commandLine)
{
	std::vector<std::string> params = ParseCommand(commandLine);
	if (params.size() == 5 && IsNumbers(params, 0, 4) && IsColors(params, 4, 5))
	{
		CPoint startPoint = { std::stod(params[0]), std::stod(params[1]) };
		CPoint endPoint = { std::stod(params[2]), std::stod(params[3]) };
		uint32_t outlineColor = std::stoul(params[4], 0, 16);

		auto ptr = std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
		m_shapesList.push_back(ptr);
	}
	else
	{
		m_output << "Invalid input\nUsage: LineSegment <start point> <end point> <outline color>\n"
				 << "Example: LineSegment 10.3 20.15 30.7 40.4 ff0000\n";
	}
	return true;
}

bool CProcessShapes::AddTriangle(std::istream& commandLine)
{
	std::vector<std::string> params = ParseCommand(commandLine);
	if (params.size() == 8 && IsNumbers(params, 0, 6) && IsColors(params, 6, 8))
	{
		CPoint vertex1 = { std::stod(params[0]), std::stod(params[1]) };
		CPoint vertex2 = { std::stod(params[2]), std::stod(params[3]) };
		CPoint vertex3 = { std::stod(params[4]), std::stod(params[5]) };
		uint32_t outlineColor = std::stoul(params[6], 0, 16);
		uint32_t fillColor = std::stoul(params[7], 0, 16);

		auto ptr = std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
		m_shapesList.push_back(ptr);
	}
	else
	{
		m_output << "Invalid input\nUsage: Triangle <vertex1> <vertex2> <vertex3> <outline color> <fill color>\n"
				 << "Example: Triangle 0 3.1 3.5 5.1 0 0 ff0000 00ff00\n";
	}
	return true;
}

bool CProcessShapes::AddRectangle(std::istream& commandLine)
{
	std::vector<std::string> params = ParseCommand(commandLine);
	if (params.size() == 6 && IsNumbers(params, 0, 4) && IsColors(params, 4, 6))
	{
		CPoint leftTop = { std::stod(params[0]), std::stod(params[1]) };
		double width = std::stod(params[2]);
		double height = std::stod(params[3]);
		uint32_t outlineColor = std::stoul(params[4], 0, 16);
		uint32_t fillColor = std::stoul(params[5], 0, 16);

		auto ptr = std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
		m_shapesList.push_back(ptr);
	}
	else
	{
		m_output << "Invalid input\nUsage: Rectangle <left top vertex> <width> <height> <outline color> <fill color>\n"
				 << "Example: Rectangle 5 3.2 4 5.2 ff0000 00ff00\n";
	}
	return true;
}

bool CProcessShapes::AddCircle(std::istream& commandLine)
{
	std::vector<std::string> params = ParseCommand(commandLine);
	if (params.size() == 5 && IsNumbers(params, 0, 3) && IsColors(params, 3, 5))
	{
		CPoint center = { std::stod(params[0]), std::stod(params[1]) };
		double radius = std::stod(params[2]);
		uint32_t outlineColor = std::stoul(params[3], 0, 16);
		uint32_t fillColor = std::stoul(params[4], 0, 16);

		auto ptr = std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
		m_shapesList.push_back(ptr);
	}
	else
	{
		m_output << "Invalid input\nUsage: Circle <center> <radius> <outline color> <fill color>\n"
				 << "Example: Circle 0 3.1 5.1 ff0000 00ff00\n";
	}
	return true;
}
