#include <iostream>
#include <vector>
#include <string>

using id_t = int; // Define id_t
using namespace std;

class Vendor {
private:
    id_t id;
    string name;
    short int ratings;
public:
    void SetId(id_t id) { this->id = id; }
    id_t GetId() { return this->id; }
    void SetName(string name) { this->name = name; }
    string GetName() { return this->name; }
    void SetRatings(short int ratings) { this->ratings = ratings; }
    short int GetRatings() { return this->ratings; }
};

template<class T>
class ICreatable {
public:
    virtual void Create(T& entity) = 0;
    virtual ~ICreatable() { }
};

template<class T>
class IReadableOne {
public:
    virtual T ReadById(id_t id) = 0;
    virtual ~IReadableOne() { }
};

template<class T>
class IHCrud : public ICreatable<T>, public IReadableOne<T> {
public:
    virtual vector<T> ReadAll() = 0;
    virtual ~IHCrud() { }
};

using IVendorRepo = IHCrud<Vendor>;

class VendorFileRepo : public IVendorRepo {
public:
    void Create(Vendor& entity) override {
        cout << "Vendor Created into file..." << endl;
    }
    Vendor ReadById(id_t id) override {
        Vendor vendor;
        cout << "Vendor Read from file..." << endl;
        return vendor;
    }
    vector<Vendor> ReadAll() override {
        vector<Vendor> vendors;
        cout << "Vendor Read All from file..." << endl;
        return vendors;
    }
};

int main() {
    IVendorRepo* repo = new VendorFileRepo();
    Vendor vendor;
    vendor.SetId(1);
    vendor.SetName("Vendor 1");
    vendor.SetRatings(5);

    repo->Create(vendor);
    Vendor retrieved = repo->ReadById(1);
    vector<Vendor> vendors = repo->ReadAll();

    delete repo;
    return 0;
}
