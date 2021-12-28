#include <iostream>
using namespace std;

class Bird
{
 public:
 int oddbird;
 Bird( char it )   { oddbird = 1; cout << "constructor : " << it << endl; } 
 Bird( int  it=0 ) { oddbird = 5 ; cout << "constructor : " << it << endl; }
 void operator=(int num) { oddbird = num; cout << "overloaded operator= \n" ; }
};

class Eagle: public Bird 
 {
 public:
 int eagles;
 Eagle():Bird('a'),eagles(0)  {}
 Eagle(int):Bird(1),eagles(1) {}
 friend ostream &operator<<( ostream &output, const Eagle &eagle );
 };

ostream &operator<<( ostream &output, const Eagle &eagle ) 
{
 output << "overloaded outstream " << endl; 
 output << "eagles = " << eagle.eagles << endl; 
 output << "oddbird = " << eagle.oddbird << endl; 
 return output;
}

int main() 
{
Bird predator(1);
cout << "predator: " << predator.oddbird << endl; 
cout << endl;

Bird ostrich;
cout << "ostrich: " << ostrich.oddbird << endl; 
cout << endl;

ostrich = 2;
cout << "ostrich: " << ostrich.oddbird << endl; 
cout << endl;

Eagle broadwings;
cout << "eagle broadwings: " << broadwings << endl;

Eagle narrowwings(1);
cout << "eagle narrowwings: " << narrowwings << endl;
}
