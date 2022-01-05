#include <iostream>

void WriteLine(const char* Content) //not const char because that denies changing value
{
	std::cout << Content << std::endl;
}