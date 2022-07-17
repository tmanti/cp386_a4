//Thomas Ingram - github: tmanti
//Lan You       - github: LY0530

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int* ptr;
    
    int size = atoi(argv[1]);
    ptr = (int*)malloc(size*sizeof(int));
    printf("Allocated %d bytes of memory\n",size);
    
    free(ptr);
    return 0;
}
