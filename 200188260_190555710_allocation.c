//Thomas Ingram - github: tmanti
//Lan You       - github: LY0530

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int size;
    int start;
    int end;
    free_node *next;
} free_node;

typedef struct {
    int size;
    char *proc_name;
    int start;
    int end;
    allocated_node *next;
} allocated_node;

void allocate(free_node *free_mem, allocated_node *alloc_mem, char alg, char *proc_name, int size);
void free(free_node *free_mem, allocated_node *alloc_mem, char *proc_name);

void insert(free_node *free_mem, free_node *node){
    if(free_mem){
        free_node *ptr = free_mem;
        while(ptr->next){
            if(ptr->start < node->start){
                node->next = ptr->next;
                ptr->next = node;
            } else {
                ptr = ptr->next;
            }
        }
        if(ptr->next == NULL){
            ptr->next = node;
        }
    } else {
        free_mem = node;
    }
}

void insert(allocated_node *alloc_mem, allocated_node *node){
    if(alloc_mem){
        free_node *ptr = alloc_mem;
        while(ptr->next){
            if(ptr->start < node->start){
                node->next = ptr->next;
                ptr->next = node;
            } else {
                ptr = ptr->next;
            }
        }
        if(ptr->next == NULL){
            ptr->next = node;
        }
    } else {
        alloc_mem = node;
    }
}

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
                char processNum[4];

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

void clean(free_node **free_mem){
    free_node *curr = *free_mem;
    free_node *prev = NULL;

    while(curr){
        if(curr->size == 0){
            if(prev){
                prev->next = curr->next;
            } else {
                *free_mem = curr->next;
            }
        }

        if(prev){
            if(prev->end == curr->start-1){
                prev->end = curr->end;
                prev->size += curr->size;
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
        }

        prev = curr;
        curr = curr->next;
    }
}

int first_fit(free_node **free_mem, int size){
    free_node *ptr = *free_mem;
    int start;
    if(ptr){
        while(ptr){
            if(ptr->size >= size){
                start = ptr->start;
                ptr->start += size;
                ptr->size -= size;
                return start;
            }
            ptr = ptr->next;
        }
    }
    return -1;
}

int best_fit(free_node **free_mem, int size){

}

int worst_fit(free_node **free_mem, int size){

}

void allocate(free_node **free_mem, allocated_node **alloc_mem, char alg, char *proc_name, int size){
    int block;
    if(alg == 'F'){
        block = first_fit(free_mem, size);
    } else if(alg == 'B'){
        block = best_fit(free_mem, size);
    } else if(alg == 'W'){
        block = worst_fit(free_mem, size);
    } else {
        printf("Invalid fit algorithm\n");
        return;
    }

    if(block == -1){
        printf("No valid memory block for the process\n");
        return;
    } else {
        allocated_node *new_node = (allocated_node*)malloc(sizeof(allocated_node));
        new_node->start = block;
        new_node->end = block+size-1;
        new_node->size = size;
        strcpy(new_node->proc_name, proc_name);

        new_node->next = NULL;

        insert(alloc_mem, new_node);
        clean(free_mem);
    }
}

void free(free_node *free_mem, allocated_node *alloc_mem, char *proc_name){
    allocated_node *curr = alloc_mem;
    allocated_node *prev = NULL;

    while(curr){
        if(strcmp(curr->proc_name, proc_name)){
            break;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if(curr == NULL){
        printf("There is no process of name: %s", proc_name);
        return;
    } else {
        int free_size = curr->size;
        int start = curr->start;

        prev->next = curr->next;
        free(curr);

        free_node *new_node = (free_node*)malloc(sizeof(free_node));
        new_node->size = free_size;
        new_node->start = start;
        new_node->end = start + free_size-1;
        insert(free_mem, new_node);
        clean(free_mem);
    }
}
