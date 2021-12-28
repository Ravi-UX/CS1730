#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------
// main()
// ---------------------------------------------------------
int main( int argc, char * argv[] )
{

    //The number to be tested
    int num = 1;
    while (true) {
        int i;
        //Check if the number is evenly divisible
        // by all numbers from 1-20
        for (i = 1; i <= 20; i++) {
            if (num % i != 0)
                break;
        }
        //check if the for loop fully finished and did not break
        if (i == 21) {
            //If the for loop completed, the integer was found
            cout << "Smallest positive number that is evenly divisible by all the numbers from ";
            cout << "1 to " << i - 1 << ": " << num << "\n";
            return 0;
        }
        //Increment number and test again if for loop did not finish
        num++;
    }

    return 0;
}
