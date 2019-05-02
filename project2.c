#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM_ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

// Previously Allocated Address
int previous_allocated_address = 0;


// -----------------------------
// Structures
//  - Process : process with size in bytes
// -----------------------------

typedef struct
{
    char* name;
    int size;
} Process;


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


    printf("\n\n");
}

/*
 * Function: printAllMemory
 *  prints ALL address of memory
 *
 *  @memory  : memory structure to print
 *  @size    : number of blocks
 */
void printAllMemory(char* main_memory[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("address: %i - process: %s\n", i, main_memory[i]); 

    }

    printf("\n\n");
}

void initializeMemory(char* main_memory[], int size)
{
    for (int i = 0; i < size; i++)
    {
        main_memory[i] = "NULL";
    }
}

Process createProcess(char* name, int size)
{
    static Process new_process;
    new_process.name = name;
    new_process.size = size;

    return new_process;
}

void allocate_process(Process process, char* main_memory[], int address)
{
    previous_allocated_address = address;
    for (int i = address; i < process.size + address; i++)
    {
        main_memory[i] = process.name;
    }
}


/*
 * Function: first_fit
 *  memory allocation algorithm to find first best address to fit given process
 *
 * returns:
 *      1 - successful allocation
 *      0 - no allocation
 */
int first_fit(char* main_memory[], Process process, int size)
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


               return 1;
            }


        }
    }
    
    printf("ERROR: no allocation possible\n");
    return 0;

} 


/*
 * Function: next_fit
 *  memory allocation algorithm to find next best address to fit given process
 *
 * returns:
 *      1 - successful allocation
 *      0 - no allocation
 */
int next_fit(char* main_memory[], Process process, int size)
{
    int current_memory_block_address = previous_allocated_address;
    int current_memory_block_size = 0;
    
    for (int i = current_memory_block_address; i < size; i++)
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
               previous_allocated_address = current_memory_block_address;

               return 1;
            }
        }
    }
    

    printf("ERROR: no allocation possible\n");
    return 0; 
    /*
    // If no next fit is possible from previuos allocated address
    //  start from beginning
    for (int i = 0; i < previous_allocated_address; i++)
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
               previous_allocated_address = current_memory_block_address;

               return;
            }
        }
    }
    */
} 


/*
 * Function: best_fit
 *  memory allocation algorithm to find ^best address to fit given process
 *
 *  ^note: the term 'best' here means the smallest memory block available within the entire memory structure 
 * 
 * returns:
 *      1 - successful allocation
 *      0 - no allocation
 */
int best_fit(char* main_memory[], Process process, int size)
{
    int best_address = -1;
    int current_memory_block_address = 0;
    int current_memory_block_size = 0;
    int smallest_memory_block_size = size;


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
                printf("current address : %d\n", current_memory_block_address);
                current_memory_block_address = i;
            }

            // Keep incrementing ...
            current_memory_block_size++;

            // Until we get to next occupied block
            // 
            // Note: the following if-else statements
            // are used to counter smallest-possible blocks
            // at the end of main memory
            if (i + 1 != size)
            {
                if (strcmp(main_memory[i + 1], "NULL") != 0)
                {
                    // If current memory block size is smaller than smallest memory block size
                    if (current_memory_block_size < smallest_memory_block_size)
                    {
                        if (current_memory_block_size >= process.size)
                        {
                            printf("Found new smallest block size\n");
                            smallest_memory_block_size = current_memory_block_size;
                            best_address = current_memory_block_address;
                        }
                    } 
                }
            }
            else
            {
                // If current memory block size is smaller than smallest memory block size
                if (current_memory_block_size < smallest_memory_block_size)
                {
                    if (current_memory_block_size >= process.size)
                    {
                        printf("Found new smallest block size\n");
                        smallest_memory_block_size = current_memory_block_size;
                        best_address = current_memory_block_address;
                    }
                } 
            }
        }
    }

    if (best_address == -1)
    {
       printf("ERROR: no allocation possible\n");
       return 0;
    } 

    printf("smallest block size starts at address: %d\n", best_address);
    allocate_process(process, main_memory, best_address);
    return 1;
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
    

    // -----------------------------
    // Allocation of Processes (currently testing)
    // -----------------------------
    Process processA = createProcess("A", 10);
    Process processB = createProcess("B", 5);
    Process processC = createProcess("C", 12);
    Process processD = createProcess("C", 11);
    Process test_process = createProcess("TEST", 6);

    allocate_process(processA, main_memory, 0);
    allocate_process(processB, main_memory, 10);
    allocate_process(processC, main_memory, 20); 

    printAllMemory(main_memory, TOTAL_ALLOC_SIZE);

    int allocation_success = best_fit(main_memory, test_process, TOTAL_ALLOC_SIZE); 
    
    printAllMemory(main_memory, TOTAL_ALLOC_SIZE);

    return 1;
}


