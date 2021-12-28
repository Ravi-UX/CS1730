#include <iostream>
#include <string>
#include <vector> 	// For std::vector
#include <fstream> 	// For std::ifstream and std::ofstream
#include <vector>       // std::vector
#include <algorithm>    // std::for_each

using namespace std;


// Helper function 1
void printx2()
{
    cout << " ";
}

int main() 
{
    	// Store the contents into a vector of strings
   	vector<std::string> outputs;
 
	// ---- will read from standar input
    	// cout << "Reading from data.txt....\n";
    	// Create the file object (input)
     	// ifstream infile("data.txt"); 
 
    	// Read into 
    	string temp;
 
    	// Get the input from the cin until EOF
    	// and add string to vector
        while( getline(cin, temp) )
	{
        	// Add to the list of output strings
        	outputs.push_back(temp);
    	}

	// Use an orditnary loop to iterate through the outputs vector
	cout << "Orginary Loop:" << endl;
	for( size_t i = 0, e = outputs.size(); i != e; ++i )
	{
		cout << i << " : " << outputs[i]  << endl;
	}

	cout << "\nLambda Based Loop:" << endl;
    	for_each( outputs.begin(), outputs.end(), 
		[](const auto &e) { std::cout << "-" << e << "\n"; });
 
    	// Use a range-based for loop to iterate through the outputs vector
    	// https://docs.microsoft.com/en-us/
	   // cpp/cpp/range-based-for-statement-cpp?view=msvc-160
	cout << "\nRange Base Loop:" << endl;
       	for( const auto & i : outputs ) // auto preferred
		cout << i << endl;
    return 0;
}
