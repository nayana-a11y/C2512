// Example 7: `Animal Kingdom`
// - `Base Class:` Animal `{field: species, behavior: eat()}`
// - `Derived Class:` Bird `{field: wingSpan, behavior: fly()}`

#include <iostream>
using namespace std;
#include <string>

class Animal {

protected: 
    std::string species;

public:
    Animal(const std::string& species): species(species) {  
        std::cout << "Animal constructor called for " << species << std::endl;
    }

    ~Animal() {
        std::cout << "Animal destructor called for " << species << "." << std::endl;
    }

    void Eat() {
        std::cout << species << " eats..." << std::endl;
    }
};

class Bird : public Animal {
private: 
    std::string wingSpan;

public:
    Bird(const std::string& species, const std::string& wingSpan)
        : Animal(species), wingSpan(wingSpan) { 
        std::cout << "Bird constructor called for " << wingSpan<< std::endl;
    }

    ~Bird() {
        std::cout << "Bird destructor called. " << std::endl;
    }
    
    void Fly() {
        std::cout << species << " flies with wingspan " << wingSpan << std::endl;
    }
};

int main() {

    // // create static objects 
    // Animal animal("Mammal");
    // animal.Eat();

    // Bird bird("Eagle", "8 feet"); 
    // bird.Fly(); 
    // bird.Eat();  

    // create dynamic objects
    Animal* animal = new Animal("Mammal");   
    Bird* bird = new Bird("Eagle", "8 feet");   
    
    animal->Eat();
    bird->Fly();
    bird->Eat(); 

    delete animal; 
    delete bird; 

    return 0;
}