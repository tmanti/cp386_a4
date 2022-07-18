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
        printf("allocator>");

    while(scanf("%[^\n]%*c", command)) {
        //printf("%s",command);
        if (strcmp(command,"Exit")==0) exit(0);

        if (strcmp(command,"Status")==0) {
            //reporting the status of memory

        }
        else {
            char *token = strtok(command," ");
            //check command type RQ/RL/C
            //printf("%s",commandType);
            if (strcmp(token,"RQ")==0) {
                //printf("in RQ\n");
                //RQ <process number> <size> <B>, new process
                char processNum[2];
                int processSize;

                token = strtok(NULL, " ");
                strcpy(processNum,token); //<process number>
                token = strtok(NULL, " ");
                processSize = atoi(token); //<size>
                token = strtok(NULL, " ");
                char type = *token; //<B>

                //printf( "processNum:%s\n", processNum);
                //printf( "processSize:%d\n", processSize);
                //printf( "type:%c\n", type);
                
                if (type == 70) {
                    //printf("in F\n");
                    // first fit

                }
                else if (type == 66) {
                    //printf("in B\n");
                    // best fit

                }
                else if (type == 87) {
                    //printf("in W\n");
                    // worst fit

                }

                //printf("Successfully allocated %d to process %s\n", processSize, processNum);

            }
            else if (strcmp(token,"RL")==0) {
                //printf("in RL\n");
                //RL <process number/name>, release memory
                char processNum[2];

                token = strtok(NULL, " ");
                strcpy(processNum,token); //<process number/name>

                //printf( "processNum:%s\n", processNum);

                //RL function here

                printf("releasing memory for process %s\n",processNum);

            }
            else if (strcmp(token,"C")==0) {
                //printf("in C");
                // compact set of holes into one larger hole

                //C function here

                printf("Compaction process is successful\n");
            }
        }
        printf("allocator>");
    }
    
    free(ptr);
    return 0;
}
