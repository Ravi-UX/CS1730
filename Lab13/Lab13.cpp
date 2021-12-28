#include <iostream>
#include <string>
#include <map>
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
        sort(outputs.begin(), outputs.end());

	// Use an orditnary loop to iterate through the outputs vector
        map<string, int> frequency;
	for( size_t i = 0, e = outputs.size(); i != e; ++i )
	{
        size_t x = i;
        int count = 0;
        while (x != e) {
            if (outputs[i] == outputs [x])
                count++;
            x++;
        }
        frequency.insert({outputs[i], count});
		//cout << i << " : " << outputs[i]  << endl;
	}

    map<string, int>::iterator i;
    for (i = frequency.begin(); i != frequency.end(); i++)
        cout << i-> second << " " << i -> first << endl;



    return 0;
}
