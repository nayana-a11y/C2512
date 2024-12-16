#include <iostream>
#include <vector>    // For vector 
#include <algorithm> // For min_element, max_element, find, sort, for_each, 
#include <numeric>   // For accumulate
#include <functional> // For greater
using namespace std;



int main()
{
    vector<float> temperatures;
    temperatures.push_back(88.0f);
    temperatures.push_back(79.0f);
    temperatures.push_back(90.0f);
    temperatures.push_back(93.0f);
    temperatures.push_back(83.0f);
    
    cout << "Temperatures:";
    for(int I = 0; I < temperatures.size(); I++)
    {
        cout << temperatures[I] << " ";
    }
    cout << endl;
    
    cout << "Temperatures:";
    for(auto temperature : temperatures)//for(float temperature : temperatures)
    {
        cout << temperature << " ";
    }
    cout << endl;
    
    cout << "Temperatures:";
    //for(vector<float>::iterator iter = temperatures.begin(); iter != temperatures.end(); iter++)
    for(auto iter = temperatures.begin(); iter != temperatures.end(); iter++)
    {
        cout << *iter << " ";
    }
    cout << endl;
    
    int count =  temperatures.size();
    float min = *min_element(temperatures.begin(), temperatures.end());
    float max = *max_element(temperatures.begin(), temperatures.end());
    float sum = accumulate(temperatures.begin(), temperatures.end(), 0.0f);
    float avg = sum / count;
    
    cout << "count:" << count << endl;
    cout << "min:" << min << endl;
    cout << "max:" << max << endl;
    cout << "sum:" << sum << endl;
    cout << "avg:" << avg << endl;

    temperatures.pop_back();
    auto found_it = find(temperatures.begin(), temperatures.end(), 90.0f);
    if(found_it != temperatures.end()){
        temperatures.erase(found_it);
    }
    cout << "Temperatures:";
    for(auto temperature : temperatures)//for(float temperature : temperatures)
    {
        cout << temperature << " ";
    }
    cout << endl;

    sort(temperatures.begin(), temperatures.end());
    cout << "sorted temperatures:"; 
    for_each(temperatures.begin(), temperatures.end(), [](float e) { cout << e << " "; });
    cout << endl;
    
    sort(temperatures.begin(), temperatures.end(), greater<int>());
    cout << "desc sorted temperatures:"; 
    for_each(temperatures.begin(), temperatures.end(), [](float e) { cout << e << " "; });
    cout << endl;
    
    return 0;
}