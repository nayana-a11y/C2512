// Example 7: `Person and Teacher`
// - `Base Class:` `Person`  
//   - Fields: `name`, `age`  
//   - Pure Virtual Behaviors: `introduce()`, `work()`  
// - `Derived Class:` `Teacher`  
//   - Fields: `subject`, `experienceYears`  

#include <iostream>
#include <cstring> 

using namespace std;

// Base class Person
class Person {
protected:
    char* name;  
    int age;

public:
    // Constructor 
    Person(const char* name, int age) {
        // this->name = new char[strlen(name) + 1];  // Allocate memory for name
        // strcpy(this->name, name);  // Copy the string to the dynamically allocated memory
        // this->age = age;
        cout << "Person constructor called for " << this->name << endl;
    }

    // Virtual destructor to ensure derived class destructors are called
    virtual ~Person() {
        cout << "Person destructor called for " << name << endl;
        delete[] name;  // Free dynamically allocated memory for name
    }

    // Pure virtual functions for dynamic binding
    virtual void introduce() = 0;
    virtual void work() = 0;
};

// Derived class: Teacher
class Teacher : public Person {
private:
    char* subject;  // Dynamic C-string 
    int experienceYears;

public:
    // Constructor with dynamic allocation for subject
    Teacher(const char* name, int age, const char* subject, int experienceYears)
        : Person(name, age), experienceYears(experienceYears) {
        this->subject = new char[strlen(subject) + 1];  // Allocate memory for subject
        strcpy(this->subject, subject);  // Copy the subject string
        cout << "Teacher constructor called for " << this->name << endl;
    }

    // Destructor 
    ~Teacher() {
        cout << "Teacher destructor called for " << name << endl;
        delete[] subject;  // Free dynamically allocated memory for subject
    }

    // Overriding the pure virtual functions
    void introduce() override {
        cout << "Hello, my name is " << name << ", I am " << age << " years old. I teach " << subject << "." << endl;
    }

    void work() override {
        cout << "I am teaching " << subject << " and have " << experienceYears << " years of experience." << endl;
    }
};

int main() {
    // Create dynamic objects
    Person* person = new Teacher("John Doe", 35, "Mathematics", 10);
    
    // Calling behaviors using base class pointer 
    person->introduce();  
    person->work();       

    // Delete the dynamic object
    delete person;

    return 0;
}
