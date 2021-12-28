//https://motostatz.com/fastest-accelerating-motorcycles/
#include <iostream>

#include <map>

using namespace std;

int main()
{

   	map<string, int> speed
  	{ 
		{ "Ninja", 102 },
   		{ "Duke",   94 }, 
   		{ "CBF500r", 98 }, 
		{ "BMW", 156 },
		{ "Ducati", 156 } 
   	};

   // retrieve a specific Key
   speed[ "someotherbike"] = 990;
   speed.insert({ "Andsomeotherbike", 4 });

   // create  an iterator
   map<string, int>::iterator i;

   cout << "The speed of bikes are" << endl;

   // iterator
   for (i = speed.begin(); i != speed.end(); i++)
   	cout << i->first << " => " << i->second <<endl;
   cout << endl;
   cout << "The top speed of BMW is "<< speed["BMW"] << endl;
   cout << endl;
}
