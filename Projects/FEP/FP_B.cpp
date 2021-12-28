#include <fstream>
#include <iostream>
using namespace std;

// ---------------------------------------------------------
// main()
// ---------------------------------------------------------
int main( int argc, char * argv[] )
{
    //Create a file stream for input text file of integers
    ifstream inFile;
    if (argc == 2) {
        inFile.open(argv[1]);
    } else {
        cout << "Use syntax: ./FP_A [nums.txt]\n";
        exit(1);
    }

    if (inFile.fail()) {
        cout << "File cannot be opened for reading.\n";
        exit(1);
    }
    //Read in the integers in the file into a temporary array
	register int n, size = 0;
    int temp[sizeof(size_t)];

	while (inFile >> n)
	{
        temp[size] = n;
        ++size;
	}
    inFile.close();

    //Move the contents of the temporary array to a new array
    // of the proper size and print the contents
    int i;
    int nums[size];
    cout << "Array X: [";
    for (i = 0; i < size; i++) {
        nums[i] = temp[i];
        if (i < size - 1) {
            cout << nums[i] << ",";
        } else {
            cout << nums[i] << "]\n";
        }
    }

    //Search the array for an integers such that it is the same as its index
    // and print to stdout and return if found
    for (i = 0; i < size; i++) {
        if (i == nums[i]) {
            cout << "X[i] = i = " << i << "\n";
            return 0;
        }
    }

    //Print if no integer is found satisfying the condition
    cout << "There exists no integer such that X[i] = i.\n";


    return 0;
}
