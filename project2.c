#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM_ELEMENTS(x) (sizeof(x) / sizeof(x[0]))


// -----------------------------
// Structures
//  - Process : process with size in bytes
// -----------------------------

struct Process
{
    char* name;
    int size;
};


// -----------------------------
// Functions
// -----------------------------


/*
 * Function: printMemory
 *  prints each address of memory
 *
 *  @memory  : memory structure to print
 *  @size    : number of blocks
 */
void printMemory(char* main_memory[], int size)
{

    int number_null = 0;

    for (int i = 0; i < size; i++)
    {
       // Check if current address has no process
       if (strcmp(main_memory[i], "NULL") == 0)
       {
           number_null++;
       }
       else
       {
           number_null = 0;
       }

       // If too many empty addresses, skip printing NULL addresses
       if (number_null > 5)
       {
           if (number_null % 10 == 0) { printf("...\n"); }
           continue;
       }
       else
       {
            printf("address: %i - process: %s\n", i, main_memory[i]); 
       }

    }
}


void initializeMemory(char* main_memory[], int size)
{
    for (int i = 0; i < size; i++)
    {
        main_memory[i] = "NULL";
    }
}

struct Process createProcess(char* name, int size)
{
    static struct Process new_process;
    new_process.name = name;
    new_process.size = size;

    return new_process;
}

void allocate_process(struct Process process, char* main_memory[], int address)
{
    for (int i = address; i < process.size + address; i++)
    {
        main_memory[i] = process.name;
    }
}


/*
 * Function: first_fit
 *  memory allocation algorithm to find first address to fit process
 *
 */
void first_fit(char* main_memory[], struct Process process, int size)
{
    int current_memory_block_address = 0;
    int current_memory_block_size = 0;
    
    for (int i = 0; i < size; i++)
    {

        // If current address isn't empty
        if (strcmp(main_memory[i], "NULL") != 0)
        {
            // Set current memory block size to 0
            current_memory_block_size = 0;
        }
        else
        {
            // Set new current address to beginning 
            // address of next wave of available memory
            if (current_memory_block_size == 0) 
            {
                current_memory_block_address = i;
            }

            // Keep incrementing ...
            current_memory_block_size++;

            //... until we find a large enough available memory block size
            if (current_memory_block_size == process.size)
            {
               printf("Found available set of memory at address %d\n", current_memory_block_address); 
               allocate_process(process, main_memory, current_memory_block_address);


               return;
            }


        }
    }


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
     
    char* main_memory[TOTAL_ALLOC_SIZE];
    initializeMemory(main_memory, TOTAL_ALLOC_SIZE);
    
    struct Process processA = createProcess("A", 10);
    struct Process processB = createProcess("B", 5);
    struct Process test_process = createProcess("TEST", 5);

    allocate_process(processA, main_memory, 0);
    allocate_process(processB, main_memory, 14);
    printMemory(main_memory, TOTAL_ALLOC_SIZE);


    first_fit(main_memory, test_process, TOTAL_ALLOC_SIZE); 
    

    printMemory(main_memory, TOTAL_ALLOC_SIZE);

    return 1;
}


