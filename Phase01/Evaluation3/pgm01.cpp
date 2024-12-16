 // // Coding Question: 1.1
    // Employee {id, age, name} //id, age, name are value objects 
    // Employee e1(101,22,"Athira"),e2(102,23,"Bhagya");
    // cout << e1 << endl; //101 22 Athira
    // cout << e2 << endl; //102 23 Bhagya
    // e1.swap(e2);
    // cout << e1 << endl; //102 23 Bhagya
    // cout << e2 << endl; //101 22 Athira


  
        #include <iostream>
        #include <string>
        using namespace std;

        class Employee {
        private:
            int id;
            int age;
            string name;

        public:
          Employee(int id, int age, const string& name) : id(id), age(age), name(name) {}

          friend ostream& operator<<(ostream& os, const Employee& emp) {
              cout << emp.id << " " << emp.age << " " << emp.name;
          }

          void swap(Employee& other) {
            int tempId = id;
            id = other.id;
            other.id = tempId;

            int tempAge = age;
            age = other.age;
            other.age = tempAge;

            std::string tempName = name;
            name = other.name;
            other.name = tempName;
            }
        };

        int main() {
            Employee e1(101, 22, "Athira");
            Employee e2(102, 23, "Bhagya");

            cout << "e1 " <<  e1 << endl; // 101 22 Athira
            cout << "e2 " <<  e2 << endl; // 102 23 Bhagya

            e1.swap(e2);

            cout << "e1 " << e1 << endl; // 102 23 Bhagya
            cout << "e2 " <<  e2 << endl; // 101 22 Athira

            return 0;
        }
  
