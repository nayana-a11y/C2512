//  `Electronic Gadgets`
// - `Base Class:` Gadget `{field: brand, behavior: powerOn()}`
// - `Derived Class 1:` Phone `{field: carrier, behavior: makeCall()}`
// - `Derived Class 2:` Camera `{field: resolution, behavior: takePhoto()}`
// - `Final Derived Class:` Smartphone `{field: osVersion, behavior: browseWeb()}`

#include <iostream>
#include <string>

class Gadget {
protected:
    std::string brand;

public:
    // Constructor of Gadget
    Gadget(const std::string& brand)
        : brand(brand) {  
        std::cout << "Gadget constructor called for " << brand << std::endl;
    }

    //  Destructor of Gadget
    virtual ~Gadget() {
        std::cout << "Gadget destructor called for " << brand << std::endl;
    }

    void powerOn() {
        std::cout << brand << " Gadget is powered on..." << std::endl;
    }
};

// Derived class 
class Phone : virtual public Gadget {
private:
    // Private fields of Dog class
    std::string carrier;

public:
    // Constructor of Phone
    Phone(const std::string& brand, const std::string& carrier)
        : Gadget(brand), carrier(carrier) { 
        std::cout << "Phone constructor called for " << brand << ", carrier: " << carrier << std::endl;
    }

    // Destructor of Phone
    virtual ~Phone() {
        std::cout << "Phone destructor called for " << brand << std::endl;
    }

    void makeCall()  {
        
        std::cout << brand << " Phone makes Call..." << std::endl;
    }
};

class Camera : virtual public Gadget {
private:
    std::string resolution;

public:
    // Constructor of Camera
    Camera(const std::string& brand, const std::string& resolution)
        : Gadget(brand), resolution(resolution) { 
        std::cout << "Camera constructor called for " << brand << ", resolution: " << resolution << std::endl;
    }

    // Destructor of Camera
    virtual ~Camera() {
        std::cout << "Camera destructor called for " << brand << "." << std::endl;
    }

    void takePhoto()  {
        
        std::cout << brand << " Camera takes Photo..." << std::endl;
    }
};

class Smartphone : public Phone, public Camera {
private:
    std::string osVersion;

public:
    // Constructor of Smartphone
    Smartphone(const std::string& brand, const std::string& carrier, const std::string& resolution, const std::string& osVersion)
        : Gadget(brand), Phone(brand, carrier), Camera(brand, resolution), osVersion(osVersion) { 
        std::cout << "Smartphone constructor called for " << brand << ", osVersion: " << osVersion << std::endl;
    }

    // Destructor of Smartphone
    ~Smartphone() {
        std::cout << "Smartphone destructor called for " << brand << "." << std::endl;
    }

    void browseWeb()  {
        std::cout << brand << " Smartphone browsing the Web..." << std::endl;
    }
};

int main() {
    // Create an static object
    Smartphone smartphone("Samsung", "5G Carrier", "108MP", "Android 13");
    
    smartphone.powerOn();  
    smartphone.makeCall();    
    smartphone.takePhoto();    
    smartphone.browseWeb();    

    // Create an dynamic object
    // Smartphone* smartphone = new Smartphone("Samsung", "5G Carrier", "108MP", "Android 13");

    // smartphone->powerOn();   
    // smartphone->makeCall();  
    // smartphone->takePhoto(); 
    // smartphone->browseWeb(); 

    // delete smartphone;

    return 0;

}