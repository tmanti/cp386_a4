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
    unsigned char *memory;
    int start;
    int end;
    struct allocated_node *next;
} ALLOCATED;

void allocate_memory(FREE **free_mem, ALLOCATED **alloc_mem, char alg, char *proc_name, int size);
void free_memory(FREE **free_mem, ALLOCATED **alloc_mem, char *proc_name);

void free_insert(FREE **free_mem, FREE *node){
    if(*free_mem){
        FREE *ptr = *free_mem;
        if(node->start < ptr->start){
            node->next = ptr;
            *free_mem = node;
        } else {
            while(ptr->next){
                if(node->start < ptr->next->start){
                    node->next = ptr->next;
                    ptr->next = node;
                    return;
                } else {
                    //printf("loop2\n");
                    ptr = ptr->next;
                }
            }
            if(ptr->next == NULL){
                ptr->next = node;
            }
        }
    } else {
        *free_mem = node;
    }
}

void alloc_insert(ALLOCATED **alloc_mem, ALLOCATED *node){
    if(*alloc_mem){
        //printf("NOP\n, %d", alloc_mem == NULL);
        ALLOCATED *ptr = *alloc_mem;
        if(node->start < ptr->start){
            node->next = ptr;
            *alloc_mem = node;
        } else {
            while(ptr->next){
                if(node->start < ptr->next->start){
                    node->next = ptr->next;
                    ptr->next = node;
                    //printf("%d:%d\n", ptr->next->start, node->start);
                    return;
                } else {
                    ptr = ptr->next;
                }
            }
            if(ptr->next == NULL){
                ptr->next = node;
            }
        }
    } else {
        *alloc_mem = node;
    }
}

unsigned char* memory;
int total_memory;
int used_memory = 0;;

int main(int argc, char *argv[]) {
    FREE *free_mem = NULL;
    ALLOCATED *alloc_mem = NULL;
    
    //FREE *free_mem;
    char command[20];
    
    //total_memory = atoi(argv[1]);
    total_memory = 1048576;
    memory = (char*)malloc(total_memory*sizeof(char));

    free_mem = (FREE*)malloc(sizeof(FREE));
    free_mem->size = total_memory;
    free_mem->start = 0;
    free_mem->end = total_memory-1;
    free_mem->next = NULL;

    printf("Allocated %d bytes of memory\n", total_memory);
        printf("allocator>");

    while(scanf("%[^\n]%*c", command)) {
        //printf("%s",command);
        if (strcmp(command,"Exit")==0){
            free(memory);
            exit(0);
        } 

        if (strcmp(command,"Status")==0) {
            //reporting the status of memory
            printf("Paritions [Allocated memory = %d]:\n", used_memory);
            ALLOCATED *ptr = alloc_mem;
            while(ptr){
                printf("Address [%d:%d] Process %s\n", ptr->start, ptr->end, ptr->proc_name);
                ptr = ptr->next;
            }

            printf("\nHoles [Free memory = %d]:\n", total_memory-used_memory);
            FREE *fptr = free_mem;
            while(fptr){
                printf("Address [%d:%d] len = %d\n", fptr->start, fptr->end, fptr->size);
                fptr = fptr->next;
            }
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

                

            }
            else if (strcmp(token,"RL")==0) {
                //printf("in RL\n");
                //RL <process number/name>, release memory
                char *processNum = (char*)malloc(4*sizeof(char));

                token = strtok(NULL, " ");
                strcpy(processNum,token); //<process number/name>

                //printf( "processNum:%s\n", processNum);

                //RL function here
                free_memory(&free_mem, &alloc_mem, processNum);

                

            }
            else if (strcmp(token,"C")==0) {
                //printf("in C");
                // compact set of holes into one larger hole

                //C function here
                ALLOCATED *curr = alloc_mem;
                ALLOCATED *prev = NULL;
                while(curr){
                    if(prev && prev->end != curr->start-1){
                        curr->start = prev->end+1;
                        curr->end = curr->start+curr->size-1;
                        curr->memory = memory+curr->start;
                    } else if(prev == NULL && curr->start != 0){
                        curr->start = 0;
                        curr->end = curr->size-1;
                        curr->memory = memory;
                    }
                    prev = curr;
                    curr = curr->next;
                }

                FREE *curr_free = free_mem;
                FREE *prev_free = NULL;

                free_mem = (FREE*)malloc(sizeof(FREE));
                free_mem->size = total_memory-used_memory;
                free_mem->start = used_memory;
                free_mem->end = used_memory+free_mem->size-1;
                free_mem->next = NULL;

                while(curr_free){
                    prev_free = curr_free;
                    curr_free = curr_free->next;
                    free(prev_free);
                }

                printf("Compaction process is successful\n");
            }
        }
        printf("allocator>");
    }
    
    //free(ptr);
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
    int start;
    int i =0;
    FREE *ptr = *free_mem;
    FREE *temp = NULL; 
    if(ptr){
        int min = 1e9;
        while(ptr){
            if(ptr->size >= size && ptr->size < min){
                min = ptr->size;
                start = ptr->start;
                temp = ptr;
            }
            ptr = ptr->next;
            i++;
        }
        if(temp){
            temp->start += size;
            temp->size -= size;
        } else {
            start = -1;
        }
        return start;
    }
    return -1;
}

int worst_fit(FREE **free_mem, int size){
    int start;
    FREE *ptr = *free_mem;
    FREE *temp = NULL;
    if(ptr){
        int max = -1e9;
        while(ptr){
            if(ptr->size >= size && ptr->size > max){
                max = ptr->size;
                start = ptr->start;
                temp = ptr;
                ptr = ptr->next;
            }
            ptr = ptr->next;
        }
        if(temp){
            temp->start += size;
            temp->size -= size;
        } else {
            start = -1;
        }
        return start;
    }
    return -1;   
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

    //printf("%d\n", block);
    if(block == -1){
        printf("No hole of sufficient size\n");
        return;
    } else {
        ALLOCATED *new_node = (ALLOCATED*)malloc(sizeof(ALLOCATED));
        new_node->start = block;
        new_node->end = block+size-1;
        new_node->size = size;
        new_node->memory = memory+block;
        new_node->proc_name = proc_name;

        new_node->next = NULL;

        alloc_insert(alloc_mem, new_node);
        clean(free_mem);

        used_memory+=size;
        printf("Successfully allocated %d to process %s\n", size, proc_name);
    }
}

void free_memory(FREE **free_mem, ALLOCATED **alloc_mem, char *proc_name){
    ALLOCATED *curr = *alloc_mem;
    ALLOCATED *prev = NULL;

    while(curr){
        //printf("%s!\n", curr->proc_name);
        if(strcmp(curr->proc_name, proc_name)==0){
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

        if(prev){
            prev->next = curr->next;
        } else {
            *alloc_mem = curr->next;
        }
        free(curr);

        FREE *new_node = (FREE*)malloc(sizeof(FREE));
        new_node->size = free_size;
        new_node->start = start;
        new_node->end = start + free_size-1;
        free_insert(free_mem, new_node);
        clean(free_mem);

        used_memory -= free_size;
        printf("releasing memory for process %s\n",proc_name);
    }
}
