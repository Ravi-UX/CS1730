#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------
// main()
// ---------------------------------------------------------
int main( int argc, char * argv[] )
{
    //The sum of the squares
    int sumSqrs = 0;
    //The sum
    int sum = 0;
    //The square of the sums
    int sqrSum;
    int difference;
    //Loop through first 100 natural numbers
    for (int i = 1; i <= 100; i++) {
        //Square each number and to the sum of squares
        sumSqrs += i * i;
        //Sum each number
        sum += i;
    }
    //Square the final sum
    sqrSum = sum * sum;
    //Compute the difference
    difference = sqrSum - sumSqrs;

    //Print result to stdout
    cout << "The difference between the sum of the squares of the first 100 natural numbers ";
    cout << "and the square of the sum: " << difference << "\n";

    return 0;
}
