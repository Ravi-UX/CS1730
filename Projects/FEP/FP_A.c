#include <stdlib.h>
#include <stdio.h>


// ---------------------------------------------------------
// main()
// ---------------------------------------------------------
int main( int argc, char * argv[] )
{

    //Check for input text file of integers
	FILE *input;
    if (argc == 2) {
        input = fopen(argv[1], "r");
    } else {
        printf("Use syntax: ./FP_A [nums.txt]\n");
        exit(1);
    }

    if (input == NULL) {
        printf("File cannot be opened for reading.\n");
        exit(1);
    }
    //Store the integers in the file in a temporary array
	register int n, size = 0;
    int temp[sizeof(size_t)];
	while (1)
	{
        fscanf(input, "%d", &n);
        if (feof(input))
            break;

        temp[size] = n;
        ++size;
	}
    //Move over contents from temporary array to a new array of size
    // also print the initial contents of the array
    int i;
    int nums[size];
    printf("Array before sort: [");
    for (i = 0; i < size; i++) {
        nums[i] = temp[i];
        if (i < size - 1) {
            printf("%d,", nums[i]);
        } else {
            printf("%d]\n", nums[i]);
        }
    }

    int first = size; //variable to keep track of index of first sorted 0
    if (nums[size - 1] == 0) {
        first = size - 1;
    }
    //Start sorting from the right side of the array
    for (i = size - 1; i > -1; i--) {
        //Once a 0 is encountered, shift all elements to the left
        // until the first sorted 0 and insert the 0 before the first
        // sorted 0
        if (nums[i] == 0 && i != size - 1) {
            int x;
            for (x = i; x < first - 1; x++) {
                    nums[x] = nums[x + 1];
            }
            first--;
            nums[first] = 0;
        }
    }

    //Print the final contents of the array after the sort
    printf("Array after sort: [");
    for (i = 0; i < size - 1; i++) {
        printf("%d,", nums[i]);
    }
    printf("%d]\n", nums[i]);

    //return the index of the first sorted 0
    return first;
}
