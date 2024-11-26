#include <iostream>
#include "Rectangle.h"

using namespace std;

int main()
{
	Rectangle plot1(40, 30);
	Rectangle plot2(70, 20);

	plot1.print();
	cout << endl;
	int area1 = plot1.findArea();
	cout << "Area of plot 1 is " << area1 << " sq. ft" << endl;

	plot2.print();
	cout << endl;
	int area2 = plot2.findArea();
	cout << "Area of plot 2 is " << area2 << " sq. ft" << endl;

	return 0;
}