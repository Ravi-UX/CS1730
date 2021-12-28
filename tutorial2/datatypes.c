#include <stdio.h>
#include <stdlib.h> 

int main( int argc, char *argv[] )
 {
 int 		a;
 long int       b;
 long long int  c;
 double         d;
 long double    e;
 char           f ={'\0'};
 char           g[80] = {'\0'};


 a = 5;
 b = 6;
 c = 7;
 d = 8;
 e = 9;

 printf("a: %d\n", a);
 printf("b: %ld\n", b);
 printf("c: %lld\n", c);
 printf("d: %f\n", d);
 printf("e: %Lf\n", e);
 printf("f: %c\n", f);
 printf("g: %s\n", g);
}

