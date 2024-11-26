#pragma once

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