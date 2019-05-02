#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_ELEMENTS(x) (sizeof(x) / sizeof(x[0]))


// -----------------------------
// Structures
//  - Block   : block of memory (8 bytes)
//  - Process : process with size in bytes
// -----------------------------

struct Block
{
    char* process_name;
    int total_size;
    int used_size;
    int isOccupied;
};


struct Process
{
    char* name;
    int size;
};


// -----------------------------
// Functions
// -----------------------------


void setBlock(struct Block *block, struct Process process)
{
    block->process_name = process.name;
    block->total_size = 8;
    block->used_size = process.size;
    block->isOccupied = 1;
}


/*
 * Function: printMemory
 *  prints each address of memory
 *
 *  @memory  : memory structure to print
 *  @size    : number of blocks
 */
void printMemory(int main_memory[], int size)
{
    
}


void initializeMemoryBlocks(struct Block memory[], int num_blocks)
{
    for (int i = 0; i < num_blocks; i++)
    {
        memory[i].process_name = "NULL";
        memory[i].total_size = 8;
        memory[i].used_size = 0;
        memory[i].isOccupied = 0;  
    }
}


struct Process createProcess(char* name, int size)
{
    static struct Process new_process;
    new_process.name = name;
    new_process.size = size;

    return new_process;
}

void allocate_process(struct Process process, int main_memory[], int address)
{

}
/*
 * Function: main
 *  
 *  @argc: argument count
 *  @argv: argument values
 *
 * 
 */
int main(int argc, char** argv)
{
    // -----------------------------
    // User Inputted Arguments 
    // -----------------------------
    
    // Memory Algorithm to use
    char* memory_algorithm_option = argv[1];
    
    // Total Memory Allocation
    int TOTAL_ALLOC_SIZE = atoi(argv[2]);

    // File Name for Script Files
    char* file_name = argv[3];


    // -----------------------------
    // Files with scripts
    // -----------------------------

    FILE* file_argument = fopen(file_name, "r");

    
    // -----------------------------
    // Memory Structure
    // -----------------------------
     
    int main_memory[TOTAL_ALLOC_SIZE];
    printf("number of elements in main_memory: %lu\n", NUM_ELEMENTS(main_memory));

    struct Process processA = createProcess("A", 4);

    allocate_process(processA, main_memory, 0);



    return 1;
}


