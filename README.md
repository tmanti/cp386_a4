# Operating System Process Memory Management System
assignment 4 for Operating systems. this program manages and controls processes memory allocation. it has 3 different methods in which it allocates memory: First fit, Best fit, Worst fit. 

## Makefile
the makefile is included with the project so that it can be easily run.

the only command is `make run` which runs the program with the default 1048576 bytes of memory to be used in allocation.

##Screenshots/Test cases/Use Example
![image](https://user-images.githubusercontent.com/8052078/180122292-2f7934c0-d7c7-4399-a2be-494bec30d33f.png)

Here is the screenshot of the basic output of the sample inputs

## Contribution

Thomas wrote:
```
struct free_node
struct allocated_node

void allocate_memory(FREE **free_mem, ALLOCATED **alloc_mem, char alg, char *proc_name, int size); //overall method to allocate memory
void free_memory(FREE **free_mem, ALLOCATED **alloc_mem, char *proc_name); //overall method to free_memory
void free_insert(FREE **free_mem, FREE *node); // insert the free memory block into the linked list
void alloc_insert(ALLOCATED **alloc_mem, ALLOCATED *node); //insert allocated memory into linked list
void clean(FREE **free_mem); //sweep free_memory linked list for illegal blocks of memory
int first_fit(FREE **free_mem, int size); //first_fit algorithm
```
Lan wrote:
```
int main(int argc, char *argv[]); //handling input and dispatching proper inputs to proper functions
int best_fit(FREE **free_mem, int size); //best_fit algorithm
int worst_fit(FREE **free_mem, int size); //worst_fit algorithm
```
## Features
The program has multiple commands:

RQ <process id/number> <size> <B>: this is a command used to simulate a new process requiring memory. the command takes 3 arguments, the process number/id, the size of memory needed, and finally the algorithm. the flags are as follows:
- "F" for first fit
- "B" for best fit
- "W" for worst fit

RL <process id/name>: this command releases the memory that has been allocated to a process

C: the c command is used to comapact the set of holes into one larger hole, it moves all process allocations to one end of the memory section and combines all free nodes into one large hole.

Status: reports the status of memory that has been entered

Exit: exits the input loop

## License
This Project is licensed under the terms of the MIT License
