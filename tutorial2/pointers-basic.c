#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 100
int main() 
{
    // Allocate a buffer
    int a = 5;
    int *aPtr;

    aPtr = &a; // address operator

   printf("a is %d\n", a);
   printf("aPtr is %d\n", *aPtr);
   printf("variable a is at address: %p\n", (void*)&a);
   printf("aPtr is %p\n", (void*)aPtr);
	
   *aPtr = 666; // dereference
   printf("a is %d\n", a);
   printf("aPtr is %d\n", *aPtr);
   printf("variable a is at address: %p\n", (void*)&a);
   printf("aPtr is %p\n", (void*)aPtr);

   *&a = a;
   printf("a is %d\n", a);
   printf("aPtr is %d\n", *aPtr);
   printf("variable a is at address: %p\n", (void*)&a);
   printf("aPtr is %p\n", (void*)aPtr);

   *&aPtr = aPtr;
   printf("a is %d\n", a);
   printf("aPtr is %d\n", *aPtr);
   printf("variable a is at address: %p\n", (void*)&a);
   printf("aPtr is %p\n", (void*)aPtr);
    
    return 0;
}


