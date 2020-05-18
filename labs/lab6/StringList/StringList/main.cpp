#include "StringList.h"
#include <iostream>
int main()
{
	CStringList list;

	list.PushBack("123");

	std::cout << list.GetSize();
	return 0;
}