// https://www.rapidtables.com/convert/number/binary-to-decimal.html
// 1 byte : 8 bits.
// 8 bits - highest 255

#include <stdio.h> 
int main() 
{ 
	unsigned char c1 = 100;  
	unsigned char c2 = 3;
	unsigned char c3 = 4;
	unsigned char cresult ;

	cresult = c1 * c2 / c3;  // 300 / 4 = 75 (no overflow)
	
	printf ("%d\n", cresult); 
	return 0; 
}
