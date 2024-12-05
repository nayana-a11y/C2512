#include <iostream>
#include <cstring>
using namespace std;

int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Fraction { //a/b , here a = numerator , b = denominator
    private:
        //attr 
        int numerator;
        int denominator;
    public:
        // constructor 
        Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) { }
        Fraction Add(const Fraction& other) {
            Fraction third(0, 1);
            third.numerator = (this->numerator * other.denominator) + (other.numerator * this->denominator);
            third.denominator = this->denominator * other.denominator;
            //
            int gcd = findGCD(third.numerator, third.denominator);
            third.numerator = third.numerator / gcd;
            third.denominator = third.denominator / gcd;
            //
            return third;
        }
        /*void display() {
            cout << this->numerator << "/" << this->denominator << endl;
        }*/

        //operator
        friend ostream& operator<<(ostream& output, const Fraction& fraction);
};

ostream& operator<<(ostream& output, const Fraction& fraction) { //non member op <<
    output << fraction.numerator << "/" << fraction.denominator;
    return output;
}

int main() {
    // Create two fraction objects
    Fraction f1(1, 2); // Represents 1/2
    Fraction f2(2, 3); // Represents 2/3

    // Add two fractions
    Fraction result = f1.Add(f2);
    //cout << "Sum of two fractions: ";
    //result.display(); // Expected output: 7/6 (in reduced form)
    cout << "sum of " << f1 << " and " << f2 << " is " << result << "." << endl; // Expected output: 7/6 (in reduced form)

    // Create a third fraction
    Fraction f3(3, 4); // Represents 3/4

    // Add three fractions
    Fraction result2 = f1.Add(f2.Add(f3));
    //cout << "Sum of three fractions: ";
    //result2.display(); // Expected output: 23/12 (in reduced form)

    cout << "sum of " << f1 << ", " << f2 << " and " << f3 << " is " << result2 << "." << endl; // Expected output: 23/12 (in reduced form)

    return 0;
}