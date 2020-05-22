#include "FindMaxEx.h"
#include "Sportsman.h"
#include <iostream>
#include <sstream>

Sportsman GetSportsman(const std::string& str)
{
	std::istringstream ss(str);
	Sportsman sportsman;
	ss >> sportsman.name >> sportsman.height >> sportsman.weight;
	if (!ss)
	{
		throw std::runtime_error("Invalid string");
	}
	return sportsman;
}

std::vector<Sportsman> ReadSportsmen(std::istream& input)
{
	std::vector<Sportsman> sportsmen;
	std::string inputStr;
	while (getline(input, inputStr))
	{
		try
		{
			sportsmen.push_back(GetSportsman(inputStr));
		}
		catch (const std::runtime_error& exc)
		{
			std::cout << exc.what() << std::endl;
		}
	}
	return sportsmen;
}

void PrintSportsmanWithMaxHeight(std::ostream& output, const std::vector<Sportsman>& sportsmen)
{
	Sportsman sportsmanWithMaxHeight;
	if (FindMax(sportsmen, sportsmanWithMaxHeight, IsLessHeight))
	{
		output << "Sportsman with max height: " << sportsmanWithMaxHeight.name
			   << "\n\theight: " << sportsmanWithMaxHeight.height
			   << "\n\tweight: " << sportsmanWithMaxHeight.weight << std::endl;
	}
	else
	{
		output << "Cannot find sportsman with max height" << std::endl;
	}
}

void PrintSportsmanWithMaxWeight(std::ostream& output, const std::vector<Sportsman>& sportsmen)
{
	Sportsman sportsmanWithMaxWeight;
	if (FindMax(sportsmen, sportsmanWithMaxWeight, IsLessWeight))
	{
		output << "Sportsman with max weight: " << sportsmanWithMaxWeight.name
			   << "\n\theight: " << sportsmanWithMaxWeight.height
			   << "\n\tweight: " << sportsmanWithMaxWeight.weight << std::endl;
	}
	else
	{
		output << "Cannot find sportsman with max weight" << std::endl;
	}
}

int main()
{
	std::vector<Sportsman> sportsmen = ReadSportsmen(std::cin);
	PrintSportsmanWithMaxHeight(std::cout, sportsmen);
	PrintSportsmanWithMaxWeight(std::cout, sportsmen);
	return 0;
}
