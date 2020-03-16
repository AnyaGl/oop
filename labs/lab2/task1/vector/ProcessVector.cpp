#include "ProcessVector.h"

void ProcessVector(std::vector<double>& numbers)
{
	double sumPosNum = 0;
	for (double& number : numbers)
	{
		if (number >= 0)
		{
			sumPosNum += number;
		}
	}

	for (int i = 0; i < numbers.size(); i++)
	{
		if (i % 2 == 0)
		{
			numbers[i] *= 2;
		}
		else
		{
			numbers[i] -= sumPosNum;
		}
	}
}