#include <iostream>
#include "Rectangle.h"

using namespace std;

int Rectangle::findArea()
{
	return length * breath;
}

Rectangle::Rectangle(int p_length, int p_breath)
{
	length = p_length;
	breath = p_breath;
}

void Rectangle::print()
{
	cout << "[length=" << length << " ft, breath=" << breath << " ft]";
}