// https://en.cppreference.com/w/cpp/container/multimap
   //https://www.boost.org/sgi/stl/Multimap.html
// no limit of members with the same key

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{

  multimap<string, string> m;

  m.insert(pair<string, string>("1,3", "elle"));
  m.insert(pair<string, string>("1,2", "eelo"));
  m.insert(pair<string, string>("0,3", "lets"));
  m.insert(pair<string, string>("1,3", "eche"));
  m.insert(pair<string, string>("0,3", "roel"));

  cout << "Number of elements with key 1,3: " << m.count("1,3") << endl;
  cout << "Number of elements with key 1,2: " << m.count("1,2") << endl;
  cout << "Number of elements with key 0,2: " << m.count("0,2") << endl;
  cout << "Number of elements with key 0,3 " << m.count("0,3") << endl;

  cout << "Elements in m: " << endl;
  for( multimap<string, string>::iterator it = m.begin();  it != m.end();  ++it )
  	cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;
}
