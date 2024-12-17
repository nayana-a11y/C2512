/*
// Coding Question: 1.1
    Employee {id, age, name} //id, age, name are value objects
    Employee e1(101,22,"Athira"),e2(102,23,"Bhagya");
    cout << e1 << endl; //101 22 Athira
    cout << e2 << endl; //102 23 Bhagya
    e1.swap(e2);
    cout << e1 << endl; //102 23 Bhagya
    cout << e2 << endl; //101 22 Athira
    //1.2 "id, age, name" as dynamic memory using new and delete
    //1.3 Programmer { string* tasks; int taskCount; } : Employee | tasks is the multiple tasks - array of task
        swap function overloadable
        here, create the dynamic programmer object assigned to employee pointer.
        field 'tasks' is dynamic memoery.
        operator << overloadable, swap is overridden.
    //1.4 replace dynamic fields as smart pointers
        prove that Employee virtual destructor is not needed.
        create the dynamic programmer object assigned to employee smart pointer
    //1.5 construct array of N programmers. read programmers from keyboard.
        cin >> var; // overload operator>> in employee and programmer
*/

#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
private:
    int *id;
    int *age;
    char *name;

public:
    Employee(int id, int age, const char *name);
    Employee(Employee &&other);
    Employee &operator=(Employee &&other);
    ~Employee();
    void swp(Employee &other);
    friend ostream &operator<<(ostream &out, const Employee &employee);
};

int main()
{
    Employee e1(101, 22, "Athira"), e2(102, 23, "Bhagya");
    cout << e1 << endl
         << e2 << endl;
    e1.swp(e2);
    cout << e1 << endl
         << e2 << endl;

    return 0;
}

Employee::Employee(int id, int age, const char *name)
{
    this->id = new int{id};
    this->age = new int{age};
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Employee::Employee(Employee &&other)
{
    this->id = other.id;
    this->age = other.age;
    this->name = other.name;
    other.id = nullptr;
    other.age = nullptr;
    other.name = nullptr;
}

Employee &Employee::operator=(Employee &&other)
{
    delete this->id;
    delete this->age;
    delete[] this->name;
    this->id = other.id;
    this->age = other.age;
    this->name = other.name;
    other.id = nullptr;
    other.age = nullptr;
    other.name = nullptr;
    return *this;
}

Employee::~Employee()
{
    delete this->id;
    delete this->age;
    delete[] this->name;
}

ostream &operator<<(ostream &out, const Employee &employee)
{
    out << "ID: " << *(employee.id) << ", name: " << employee.name << ", age: " << *(employee.age);
    return out;
}

void Employee::swp(Employee &other)
{
    Employee temp(move(*this));
    *this = move(other);
    other = move(temp);
}