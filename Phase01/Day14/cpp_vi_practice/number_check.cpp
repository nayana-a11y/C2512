 #include<iostream>
      using namespace std;

      int main(){
         int number;
         cout << "Enter a number: ";
         cin >> number;

         if(number%2==0){

            if(number > 0)
               cout << "The number is positive and even " << endl;
            else if(number < 0)
               cout << "The number is negative and even " <<endl;
            else
               cout << "The number is zero." << endl;
            return 0;
         }
         else{
            if (number > 0)
               cout << "The number is positive and odd. " << endl;
            else if(number < 0)
               cout << "The number is negative and odd. " <<endl;
            else
               cout << "The number is zero." << endl;
            return 0;
         }
      }