#include <stdio.h>


// Copy last three addresses of 'intarray' into 'ptr_array' which is an array of
// pointers to an int. intarray and ptr_array are variable names.
// you will do this by steps: Q1-Q3.

    int main()
    {

    	int intarray[5] = {1,2,3,4,5};


	// pointer "pointer" below, points to an integer points, which points to
	// the first element in intarrary.
        int *pointer = (int *) &intarray; // points to the first element here.

       // Q1. make "pointer" point to the 3rd element of intarray with value '3' (currently
       //	it points to the first element with value '1')

	// Q1: Insert code for Q1 below:
        pointer++;
        pointer++;


        // below is an array of 3 pointers, pointing to integers.
        int *ptr_array[3];

        // copy last three addresses of intarray into ptr_array
        int i;
        for( i = 0; i < 3; i++ )
	{
            	// Q2.insert code below, so that the elements in ptr_array points to
	   	//	the last three elements in intarray
           	// 		pointer should initially point to '3'
           	// 			then you should increment the pointer
	   	//			to the next element of intarray.

	   	// Q2: Insert code for Q2 below:

        ptr_array[i] = &*pointer++;

        }

        for (i = 0; i < 3; i++)
	{
        	if (ptr_array[i] == &pointer[i])
	 	{
		// Q3 - add printing out the content intarray ('3', '4', and '5'
		//	in addition to pointer addresses

	   	// Q3: replace the '666' token with a proper variable name (using ptr_array)
                	printf("ptr_array[%d] ==  &pointer[%d] : %p : %d \n",
				// i, i, ptr_array[i], 666  );
				   i, i, ptr_array[i], *ptr_array[i]  );
            	}
		else
		{
                	printf("ptr_array[%d] !=  &pointer[%d] : %p : %d\n",
				i, i, ptr_array[i], *ptr_array[i]  );
            	}
        }

        return 0;
    }
