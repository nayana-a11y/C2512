//vector
#include<iostream>
#include<deque>
using namespace std;

template <class T>
void print(T container, const char* caption) {
    cout << caption << ":";
    for(auto e : container) {
        cout << e << " ";
    }
    cout << endl;
}

int main() 
{
    deque<double> salaries;
    salaries.push_back(10000.0);
    salaries.push_back(20000.0);
    salaries.push_back(30000.0);
    salaries.push_back(10000.0);      
    salaries.push_back(20000.0);

    print<deque<double>>(salaries, "Salaries");

    cout << "size:" << salaries.size() << endl;
    cout << "max_size:" << salaries.max_size() << endl;

    cout << endl;
    cout << "front:" << salaries.front() << endl;
    cout << "back:" << salaries.back() << endl;
    cout << "[2]:" << salaries[2] << endl;
    cout << "at:" << salaries.at(2) << endl;

    
    cout << endl;
    
    salaries.push_front(20.0);
    print<deque<double>>(salaries, "After push front at 20.0,\n\tSalaries");

    salaries.insert(salaries.begin() + 1, 500.0);
    print<deque<double>>(salaries, "After insert 500.0 at index 1,\n\tSalaries");

    salaries.pop_back();
    print<deque<double>>(salaries, "After (pop_back)removed last element,\n\tSalaries");

    salaries.pop_front();
    print<deque<double>>(salaries, "After (pop_front)removed front element,\n\tSalaries");

    salaries.erase(salaries.begin()+2);
    print<deque<double>>(salaries, "After remove at index 2,\n\tSalaries");

    cout << endl;
    cout << "salaries(using iterator):";
    for( auto ITER = salaries.begin() ; ITER != salaries.end() ; ITER++ ) { 
        cout << *ITER << " ";
    }
    cout << endl;

    cout << endl ;
    cout << "salaries(using reverse iterator):";
    for( auto ITER = salaries.rbegin() ; ITER != salaries.rend() ; ITER++ ) { 
        cout << *ITER << " ";
    }
    cout << endl;

    salaries.clear();
    print<deque<double>>(salaries, "After clear,\n\tSalaries");
    return 0;
}