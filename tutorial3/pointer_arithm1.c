/*   Casting and pointer arithmetic.  */

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 100
int main() 
{
    // Allocate a buffer
    char * A = malloc( BUFFER_SIZE );
    printf("A = %p\n", A); // %p void * ptr  in hexadeximal
 
    /* The following arithmetic examples are to show you how the ~type~ of 
     * the pointer affects arithmetic done on the pointer. 
     * When adding x to a pointer A (i.e. A + x), the result is really
     * (A + x * sizeof(TYPE_OF_PTR_A)).
     * explicitly cast a pointer when doing pointer arithmetic.
     */
 
    /* char is 1 byte wide
     * B = A + (5 * 1) 
     *   = A + 0x5
     */
    printf("sizeof(char) is %d\n", (int) sizeof(char));

    char *B = (A + 5); 
    printf("B = (A + 5) = A + 0x5 = %p (adds 5 to the address) \n", B);

    /* short is 2 bytes wide
     * C = A + (2 * 2) 
     *   = A + 0x4
     */
    char *C = (char *)(((short *) A) + 2);

    printf("sizeof(short) is %d\n", (int) sizeof(short));
    printf("C = (((short *) A) + 2) = A + 0x4 = %p\n", C);
    printf("C moves it 2 short values forward so adds '2'+'2' = 4\n");

    /* int is 4 bytes wide, char is 1 byte wide
     * D = (A + (3 * 4) + 7 * 1)
     *   = A + 19 
     *   = A + 0x13  (19 converted to HEX -->16 is 10 and 3 remains).
     * https://www.binaryhexconverter.com/decimal-to-hex-converter
     */
    printf("sizeof(int) is %d\n", (int) sizeof(int));
    char *D = ((char *)(((int *) A) + 3) + 7);
    printf("D = ((char *)(((int *) A) + 3) + 7) = A + 0x13 = %p\n", D);    

    /*  int* and char*  (or any other pointer) is 8 bytes wide 

	// what you think the answer should be?
     */
    char *E = ((char *)((int **)(((char **) A) + 2) + 3) + 4);
    //printf("E = ((char *)((int **)(((char **) A) + 2) + 3) + 4) = A + 0x2C = %p\n", E);    
    
    // Clean up memory
    free(A);
    
    return 0;
}



