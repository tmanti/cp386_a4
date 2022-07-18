//Thomas Ingram - github: tmanti
//Lan You       - github: LY0530

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int* ptr;
    char command[20];
    
    int size = atoi(argv[1]);
    ptr = (int*)malloc(size*sizeof(int));
    printf("Allocated %d bytes of memory\n",size);

    while(scanf("%s",command)) {
        if (strcmp(command,"Exit")==0) exit(0);
        //loop
    }
    
    free(ptr);
    return 0;
}
