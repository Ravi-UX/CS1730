#include <stdio.h>
#include <stdint.h>

#include <limits.h> // USHRT_MAX access 

// Secrets of printf formatting:
// https://www.cypress.com/file/54441/download

// https://en.wikibooks.org/wiki/C_Programming/stdint.h

// https://www.calculator.net/binary-calculator.html
// 1111 1111 1111 1111

// https://en.wikibooks.org/wiki/C_Programming/limits.h
// https://rcweb.dartmouth.edu/doc/ibmcxx/en_US/doc/complink/ref/rucl64mg.htm

// rules.
//https://www.nayuki.io/page/summary-of-c-cpp-integer-rules
int main(void)

{
	// short int.
	uint16_t value = 0xFFFF; // 2^{16} − 1 which equals 65,535
	
	printf("uint16_t unsigned 16 bit integer is of size %ld bytes) \n", sizeof(value));

	printf("uint16_t unsigned 16 bit integer max value is %u) \n", USHRT_MAX );

	printf("          Original Value:  %10u\n",                 value);
	printf("  Unsigned 16->Signed 16:  %10hd\n", (int16_t)      value); // ** conversion [-1]
	printf("Unsigned 16->Unsigned 32:  %10u\n",  (unsigned int) value); // widening

	printf(" Unsigned 16->Unsigned 8:  %10hu\n", (uint8_t)      value); // narrowing    [255]
									// top bits discarded

	printf(" Unsigned 16->Signed 8:    %10d\n", (int8_t)      value); // narrowing       [-1]
	printf("  Unsigned 16->Signed 32:  %10d\n",  (int)          value); //  sign convert

	printf("  \n");

	int16_t svalue = -1; // signed value
	printf("          Original Value:  %10d\n",                 svalue); //
	printf("  Signed 16->Unsigned 16:  %10u\n", (uint16_t)      svalue); //**65535 sign convert
										// overflow

	printf("    Signed 16->Signed 32:  %10d\n",  (int)          svalue); //  widening
	printf("     Signed 16->Unsigned 8:%10hu\n", (uint8_t)       svalue); // narrowing  [255]
									// to bits discarded
									// overflow - implemention

	printf("     Signed 16->Signed 8:  %10d\n", (int8_t)       svalue); // narrowing  [-1]
	printf("  Signed 16->Unsigned 32:  %10u\n", (unsigned int)  svalue); // ** sign convert
										// [4294967295]
	return 0;
}
