#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() 
{
  map<int, map<int, string> > nested_map;
  nested_map[1][4] = "else";
  nested_map[0][3] = "ibex";
  cout << nested_map[1][4] << endl;
  cout << nested_map[0][3] << endl;
}
