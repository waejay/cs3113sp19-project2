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
//  - node    : node for buddy memory allocation a
//              algorithm
// -----------------------------

typedef struct
{
    char name[16];
    int size;
} Process;


struct node
{
    int address;
    int size;
    int isOccupied; 
    int hasChildren;
    struct node *left;
    struct node *right;
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

/*
 * Function: initializeMemory
 *  initializes each array in the main memory structure with "NULL"
 *
 */
void initializeMemory(char* main_memory[], int size)
{
    for (int i = 0; i < size; i++)
    {
        main_memory[i] = "NULL";
    }
}

/*
 * Function: createProcess
 *  creates a new process
 *
 *  @new_name  : name of process
 *  @size      : size of process
 *
 *  NOTE: function converts a string variable into integer for process.size
 *
 *  returns: a new Process object
 */
Process createProcess(char* new_name, char* size)
{
    Process new_process;
    strcpy(new_process.name, new_name);
    new_process.size = strtol(size, NULL, 10);
    
    return new_process;
}

/* Function: allocate_process
 *  allocates a process into main memory at a given address
 *
 *  @process     : process to allocate
 *  @main_memory : main memory structure
 *  @size        : size of main memory
 *  @address     : address of main memory to allocate process to
 *
 */
void allocate_process(Process process, char* main_memory[], int size, int address)
{
    previous_allocated_address = address;

    char* name = malloc(16*sizeof(char));

    strcpy(name, process.name);

    for (int i = address; i < address + process.size; i++)
    {
        main_memory[i] = name;
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
               //printf("Found available set of memory at address %d\n", current_memory_block_address); 
               if (current_memory_block_address + process.size == size)
               {
                   allocate_process(process, main_memory, size, current_memory_block_address - 1);
               }
               else
               {
                   allocate_process(process, main_memory, size, current_memory_block_address);
               }
               return current_memory_block_address;
            }


        }
    }
    
    return -1;

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
               //printf("Found available set of memory at address %d\n", current_memory_block_address); 
               if (current_memory_block_address + process.size == size)
               {
                   allocate_process(process, main_memory, size, current_memory_block_address - 1);
                   previous_allocated_address = current_memory_block_address - 1;
               }
               else
               {
                   allocate_process(process, main_memory, size, current_memory_block_address);
                   previous_allocated_address = current_memory_block_address;
               }

               return previous_allocated_address;
            }
        }
    }
    

    return -1; 
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
                            smallest_memory_block_size = current_memory_block_size;
                            best_address = current_memory_block_address;
                        }
                    } 
                }
            }
            else
            {
                // If current memory block size is smaller than smallest memory block size
                if (current_memory_block_size <= smallest_memory_block_size)
                {
                    if (current_memory_block_size > process.size)
                    {
                        smallest_memory_block_size = current_memory_block_size;
                        best_address = current_memory_block_address;
                    }
                    else if (current_memory_block_size == process.size)
                    {
                        best_address = current_memory_block_address - 1;
                    }
                } 
            }
        }
    }

    if (best_address == -1)
    {
       return -1;
    } 

    allocate_process(process, main_memory, size, best_address);
    return best_address;
}



/*
 * Function: buddy
 *  memory allocation algorithm that finds a "buddy" address to allocate
 * 
 * returns:
 *      [some address] - on successful allocation
 *      -1             - no allocation
 */
int buddy(char* main_memory[], Process process, struct node* head, int size)
{
    if (head->isOccupied == 0)
    {
        printf("head size is : %d and process size is %d\n", head->size, process.size); 

        // No children; process is equal to total size of main memory
        if (head->hasChildren == 0 && head->size == process.size)
        {
            head->isOccupied = 1;
            allocate_process(process, main_memory, size,  head->address);
            return head->address;
        } 

        // No children but process is smaller than total size
        else if (head->hasChildren == 0 && process.size < head->size)
        {
            if (head->size / 2 <= process.size)
            {
                head->isOccupied = 1;
                allocate_process(process, main_memory, size, head->address);
                return head->address;
            }

            head->left = malloc(sizeof(struct node)); 
            head->left->size = head->size / 2;
            head->left->address = head->address;
            head->left->isOccupied = 0;
            head->left->hasChildren = 0;
            
            head->right = malloc(sizeof(struct node));
            head->right->size = head->size / 2;
            head->right->address = head->size / 2 + 1;
            head->right->isOccupied = 0;
            head->right->hasChildren = 0;

            head->hasChildren = 1;
            return buddy(main_memory, process, head->left, size / 2);
        }
        else if (head->hasChildren)
        {
            int address = buddy(main_memory, process, head->left, size / 2);
            if (address > -1)
            {
                return address;
            }
            else
            {
                address = buddy(main_memory, process, head->right, size / 2);
                if (address > -1)
                {
                    return address;
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    
    return -1;
}
/*
 * Function: processScript
 *  processes user-given script for memory allocation
 *
 */
void processScript(FILE* file_script, char* main_memory[], char* memory_algorithm_option, int size)
{
    char line_buffer[100];
    int allocation_success = 0;
    int temp;

    while(fgets(line_buffer, sizeof(line_buffer), file_script))
    {
        if (line_buffer[0] == '#') continue;

        char* commands[10];
            
        int j = 0;
        commands[j] = strtok(line_buffer, " ");
        while(commands[j] != NULL)
        {
            commands[++j] = strtok(NULL, " \n");
        }

        if (strcmp(commands[0], "REQUEST") == 0)
        {
            Process new_process = createProcess(commands[1], commands[2]);

            if (strcmp(memory_algorithm_option, "BESTFIT") == 0)
            {
                allocation_success = best_fit(main_memory, new_process, size);
            }
            else if (strcmp(memory_algorithm_option, "FIRSTFIT") == 0) 
            { 
                allocation_success = first_fit(main_memory, new_process, size);
            }
            else if (strcmp(memory_algorithm_option, "NEXTFIT") == 0)
            {
                allocation_success = next_fit(main_memory, new_process, size);
            }
            else if (strcmp(memory_algorithm_option, "BUDDYFIT") == 0)
            {
            }
            else
            {
                printf("ERROR: Invalid memory allocation algorithm provided\n");
                exit(-1);
            }
            
            if (allocation_success > -1)
            {
                printf("ALLOCATED %s %d\n", new_process.name, allocation_success);
            }
            else
            {
                printf("FAIL REQUEST %s %d\n", new_process.name, new_process.size);
            }
        }
        if (strcmp(commands[0], "RELEASE") == 0)
        {
            int isReleased = 0;
            int current_address = -1;
            int process_size_freed = 0;
            for (int i = 0; i < size; i++)
            {
                if (strcmp(main_memory[i], commands[1]) == 0)
                {
                    // Get size first
                    int j = i;
                    while (strcmp(main_memory[j], commands[1]) == 0)
                    {
                        j++;
                    }

                    if (current_address == -1) current_address = i;
                    isReleased = 1;
                    strcpy(main_memory[i], "NULL");
                    process_size_freed = (j - i);
                    break;
                }
            }

            if (isReleased)
            {
                printf("FREE %s %d %d\n", commands[1], process_size_freed, current_address); 
            }
            else
            {
                printf("FAIL RELEASE %s\n", commands[1]); 
            }

        }

        if (strcmp(commands[0], "LIST") == 0)
        {
            if (strcmp(commands[1], "AVAILABLE") == 0)
            {
                int isFull = 0;
                int num_allocated = 0;
                int current_address = 0;
                int current_size_block = 0;

                // Check if main memory is full first
                int k = 0;
                while (strcmp(main_memory[k], "NULL") != 0)
                {
                   k++; 
                }
                
                if (k == size - 1) isFull = 1;

                if (isFull)
                {
                    printf("FULL\n");
                    continue;
                }

                for (int i = 0; i < size; i++)
                {
                    if (strcmp(main_memory[i], "NULL") != 0)
                    {
                        if (current_size_block > 0)
                        {
                            printf("(%d, %d) ", current_size_block, current_address); 
                            num_allocated++;
                        }
                        else if (current_size_block == 0 && current_address + 1 == size)
                        {
                            isFull = 1;
                            break;
                        }
                        current_address = i + 1;
                        current_size_block = 0;

                    }
                    else
                    {
                        current_size_block++; 
                        if (i + 1 == size)
                        {
                            if (current_size_block > 0)
                            {
                                printf("(%d, %d) ", current_size_block, current_address); 
                                current_size_block = 0;
                                num_allocated++;
                            }
                        }
                    }
                
                }
                printf("\n");
            }
            else if (strcmp(commands[1], "ASSIGNED") == 0)
            {
                int isEmpty = 1;
                char* process_name;
                int process_size;
                int current_address;

                for (int i = 0; i < size; i++)
                {
                    if (strcmp(main_memory[i], "NULL") != 0)
                    {
                        process_name = main_memory[i];
                        process_size++;
                        isEmpty = 0;

                        if (i + 1 != size)
                        {
                           if (strcmp(process_name, main_memory[i + 1]) != 0)
                           {
                                printf("(%s, %d, %d) ", process_name, process_size, current_address);                                
                                current_address = i + 1;
                                process_size = 0;
                                continue;
                           } 
                           else
                           {
                               process_size++;
                           }
                        }
                        else
                        {
                            if (process_size > 0)
                            {
                                printf("(%s, %d, %d) ", process_name, process_size, current_address);
                            }
                        }
                    }
                    else
                    {
                        process_size = 0;
                        current_address = i + 1;
                    }
                }
            if (isEmpty)
            {
                printf("NONE\n");
                continue;
            }
            printf("\n");
            }
            else
            {
                printf("ERROR: no option for LIST %s", commands[1]);
            }


        }

        if (strcmp(commands[0], "FIND") == 0)
        {
            int process_size = 0;
            int current_address = -1;

            int i = 0;
            while (i < size)
            {
                // If a match is found..
                if (strcmp(main_memory[i], commands[1]) == 0)
                {
                    process_size++;
                    if (current_address == -1) current_address = i;
                }
                else
                {
                    if (process_size > 0)
                    {
                        printf("%s, %d, %d\n", commands[1], process_size, current_address);
                        break;
                    }
                    else if (i + 1 == size && process_size == 0)
                    {
                        printf("FAULT\n");
                        break;
                    }
                }
                i++;
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

    FILE* file_script = fopen(file_name, "r");
    
    // -----------------------------
    // Memory Structure
    // -----------------------------
     
    char* main_memory[TOTAL_ALLOC_SIZE];
    initializeMemory(main_memory, TOTAL_ALLOC_SIZE);
    // -----------------------------
    // Read Script
    // -----------------------------
    if (file_script)
    {
        processScript(file_script, main_memory, memory_algorithm_option, TOTAL_ALLOC_SIZE);
    }
    else
    {
        printf("ERROR: file argument invalid");
    }
    /*
    // -----------------------------
    // Allocation of Processes (currently for testing)
    // -----------------------------

    Process processA = createProcess("A", "10");
    Process processB = createProcess("B", "5");
    Process processC = createProcess("C", "12");
    Process processD = createProcess("D", "11");
    Process test_process = createProcess("TEST", "5");

    allocate_process(processA, main_memory, TOTAL_ALLOC_SIZE,  0);
    allocate_process(processB, main_memory, TOTAL_ALLOC_SIZE,  10);
    allocate_process(processC, main_memory, TOTAL_ALLOC_SIZE,  20); 

    printAllMemory(main_memory, TOTAL_ALLOC_SIZE);

    int allocation_success = best_fit(main_memory, test_process, TOTAL_ALLOC_SIZE); 
    
    printAllMemory(main_memory, TOTAL_ALLOC_SIZE);
    */


    return 1;
}


