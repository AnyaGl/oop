#include "StringList.h"
#include <iostream>
int main()
{
	CStringList list;

	list.PushBack("123");
	for (auto str : list)
	{
		std::cout << str << std::endl;
	}
	list.PushBack("345");
	for (auto str : list)
	{
		std::cout << str << std::endl;
	}
	std::cout << list.GetSize();
	return 0;
}