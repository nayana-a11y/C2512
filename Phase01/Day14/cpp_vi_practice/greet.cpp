 #include <iostream>
    #include <cstdlib>

    using std::cout;
    using std::cin;
    using std::endl;

    int main(){
        char name[255];

        cout << "Enter the name:" << endl;
        cin >> name;
        cout << "Hello " << name << "!!!" << endl;
        cout << "Good Bye!" ;
        return EXIT_SUCCESS;

    }