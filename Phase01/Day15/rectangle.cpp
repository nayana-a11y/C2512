#include <iostream>

using namespace std;

class Rectangle
{
public:
	// attributes [member data]
	int length;
	int breath;
	// behaviours [member functions]
	int findArea();
	// constrctors
	Rectangle(int p_length, int p_breath);
	//
	void print();
};

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