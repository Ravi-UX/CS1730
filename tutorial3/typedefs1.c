#include <stdio.h>

// typedef <thing you want to rename> <the name of the new thing>
typedef int number;


int main()
{
    // typedefs allow for code that is cleaner to read, as well
    // as increased modularity / polymorphism.
    number foo = 5;

    printf( " %d\n", foo  );
    return 0;
}
