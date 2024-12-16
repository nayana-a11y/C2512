//1.2 "id, age, name" as dynamic memory using new and delete 

        #include <iostream>
        #include <string>
        using namespace std;

        class Employee {
        private:
            int* id;           
            int* age;         
            string* name;      

        public:
            Employee(int e_id, int e_age, const string& e_name) {
                id = new int(e_id);
                age = new int(e_age);
                name = new string(e_name);
            }

            ~Employee() {
            delete id;
            delete age;
            delete name;
        }


        Employee(const Employee& other) {
            id = new int(*other.id);
            age = new int(*other.age);
            name = new string(*other.name);
        }

        friend ostream& operator<<(ostream& os, const Employee& emp) {
            cout << *emp.id << " " << *emp.age << " " << *emp.name;
        }

        void swap(Employee& other) {
            int* tempId = id;
            id = other.id;
            other.id = tempId;

            int* tempAge = age;
            age = other.age;
            other.age = tempAge;

            string* tempName = name;
            name = other.name;
            other.name = tempName;
        }
      };

      int main() {
          Employee e1(101, 22, "Athira");
          Employee e2(102, 23, "Bhagya");

          cout << "e1: " << e1 << endl; // 101 22 Athira
          cout << "e2: " << e2 << endl; // 102 23 Bhagya

          e1.swap(e2);

          cout << "e1: " << e1 << endl; // 102 23 Bhagya
          cout << "e2: " << e2 << endl; // 101 22 Athira

          return 0;
      }