#pragma once
#include "Canvas.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <functional>
#include <map>
#include <memory>
#include <vector>

class CProcessShapes
{
public:
	CProcessShapes(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintShapeWithMaxArea() const;
	void PrintShapeWithMinPerimeter() const;
	void DrawShapes() const;
	void GetShapesInfo() const;

private:
	bool AddLineSegment(std::istream& commandLine);
	bool AddTriangle(std::istream& commandLine);
	bool AddRectangle(std::istream& commandLine);
	bool AddCircle(std::istream& commandLine);

	using Handler = std::function<bool(std::istream& commandLine)>;
	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::shared_ptr<IShape>> m_shapesList;
};
