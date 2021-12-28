#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------
// main()
// ---------------------------------------------------------
int main( int argc, char * argv[] )
{
    //Limit for the numbers in the fibonacci sequence
    int limit = 4000000;
    //First number to be summed
    int n1 = 1;
    //Second number to be summed
    int n2 = 2;
    //The sum of the two numbers
    int sum = 0;
    //The sum of all the even numbers
    // Initial value is 2 because it is the first even number in sequence
    int evenSum = 2;
    while (true) {
        //Sum the first two numbers
        sum = n1 + n2;
        //Check if the new sum is less than the limit
        if (sum <= limit) {
            //Check if the new sum is even and add
            if (sum % 2 == 0)
                evenSum += sum;
        } else {
            //Break if the new element is greater than the limit
            cout << "Sum of even valued terms in Fibonacci sequence less than 4000000: " << evenSum << "\n";
            break;
        }
        //Update the numbers to be summed
        n1 = n2;
        n2 = sum;
    }

    return 0;
}
