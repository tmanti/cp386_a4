//Thomas Ingram - github: tmanti
//Lan You       - github: LY0530

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct free_node {
    int size;
    int start;
    int end;
    struct free_node *next;
} FREE;

typedef struct allocated_node {
    int size;
    char *proc_name;
    int start;
    int end;
    struct allocated_node *next;
} ALLOCATED;

void allocate_memory(FREE **free_mem, ALLOCATED **alloc_mem, char alg, char *proc_name, int size);
void free_memory(FREE **free_mem, ALLOCATED **alloc_mem, char *proc_name);

void free_insert(FREE *free_mem, FREE *node){
    if(free_mem){
        FREE *ptr = free_mem;
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

void alloc_insert(ALLOCATED *alloc_mem, ALLOCATED *node){
    if(alloc_mem){
        ALLOCATED *ptr = alloc_mem;
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
    FREE *free_mem = NULL;
    ALLOCATED *alloc_mem = NULL;

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
                char *processNum = (char*)malloc(4*sizeof(char));
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
                
                allocate_memory(&free_mem, &alloc_mem, type, processNum, processSize);

                //printf("Successfully allocated %d to process %s\n", processSize, processNum);

            }
            else if (strcmp(token,"RL")==0) {
                //printf("in RL\n");
                //RL <process number/name>, release memory
                char *processNum = (char*)malloc(4*sizeof(char));

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

void clean(FREE **free_mem){
    FREE *curr = *free_mem;
    FREE *prev = NULL;

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

int first_fit(FREE **free_mem, int size){
    FREE *ptr = *free_mem;
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

int best_fit(FREE **free_mem, int size){

}

int worst_fit(FREE **free_mem, int size){

}

void allocate_memory(FREE **free_mem, ALLOCATED **alloc_mem, char alg, char *proc_name, int size){
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
        ALLOCATED *new_node = (ALLOCATED*)malloc(sizeof(ALLOCATED));
        new_node->start = block;
        new_node->end = block+size-1;
        new_node->size = size;
        strcpy(new_node->proc_name, proc_name);

        new_node->next = NULL;

        alloc_insert(*alloc_mem, new_node);
        clean(free_mem);
    }
}

void free_memory(FREE **free_mem, ALLOCATED **alloc_mem, char *proc_name){
    ALLOCATED *curr = *alloc_mem;
    ALLOCATED *prev = NULL;

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

        FREE *new_node = (FREE*)malloc(sizeof(FREE));
        new_node->size = free_size;
        new_node->start = start;
        new_node->end = start + free_size-1;
        free_insert(*free_mem, new_node);
        clean(free_mem);
    }
}
