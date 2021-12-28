#include <stdio.h>


int main( int argc, char* argv[] )
{
  struct name { char * name; int  age; } jansson; 
  struct name 				 svensson;

  struct name 				*person;

  svensson.name 	= "Gunnar Svensson";
  svensson.age 		= 25;

  jansson.name 	= "Jack Jansson";
  jansson.age 		= 18;

  printf("%s is %d years old\n", svensson.name, svensson.age);
  printf("%s is %d years old\n", jansson.name,  jansson.age);

  person = &svensson;
  printf("%s is %d years old\n",person->name,person->age);

  person = &jansson;
  printf("%s is %d years old\n",person->name,person->age);


  return 0;
}

