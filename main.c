//
//  main.c
//  first_c_program
//
//  Created by Johan Larsson on 2024-09-03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    
    // ##############################################
    // Stack allocation
    // ##############################################
    
    /*
    int size = 1e7;

    int as[size];
    for ( size_t ix = 0; ix < size; ++ix )
      as[ix] = 0;

    printf("%d\n", as[0]);
    */
    
    // The array as is allocated on the stack. Stack memory is limited, so increasing
    // size will eventually lead to a segmentation fault when the stack
    // limit is exceeded. This happens when I went from 1e6 to 1e7
    
    // ##############################################
    // Heap allocation
    // ##############################################
    
    /*
    int size = 1e7;

    int * as = (int*) malloc(sizeof(int) * size);
    for ( size_t ix = 0; ix < size; ++ix )
      as[ix] = 0;

    printf("%d\n", as[0]);

    free(as);
    */
    
    // Heap allocation using malloc() is more flexible, allowing larger arrays without
    // causing a segmentation fault. However, memory management is the programmer's
    // responsibility, and it must be freed using free(). As seen, 1e7 works here.
    
    // ##############################################
    // Reducing memory fragmentation
    // ##############################################
    
    // Using contiguous memory:
    
    /*
    size: This integer represents the dimensions of the matrix. In this case, the matrix is of size size x size, so if size = 10, the matrix will have 100 elements.
    
    asentries: This pointer (int *asentries) points to a block of memory large enough to store the entire matrix. The memory is allocated using malloc with the size of size * size * sizeof(int). This creates a contiguous block of memory for all the matrix elements.

    as: This pointer (int **as) points to an array of pointers, each pointing to the start of one row in the matrix. It is allocated with malloc, creating space for size pointers. These pointers are then set to different sections of asentries.

    ix, jx: These variables are loop indices. ix is used to iterate over the rows, and jx is used to iterate over the columns (or elements within each row). In the loop initializing as, jx accumulates the offsets for different rows.
    */
    
    /*
    int size = 10;

    int * asentries = (int*) malloc(sizeof(int) * size*size); // Allocate one big block of memory
    int ** as = (int**) malloc(sizeof(int*) * size);
    for ( size_t ix = 0, jx = 0; ix < size; ++ix, jx+=size )
      as[ix] = asentries + jx;

    for ( size_t ix = 0; ix < size; ++ix )
      for ( size_t jx = 0; jx < size; ++jx )
        as[ix][jx] = 0;

    printf("%d\n", as[0][0]);

    free(as);
    free(asentries);
    */
    
    // This method avoids fragmentation because all data is stored in a single contiguous memory block.
    
    // Using non-contiguous memory:
    
    /*
     
    Same variables as before with following difference:

    as: This pointer (int **as) is an array of pointers, each pointing to the beginning of a row in the matrix. In this method, each row is allocated separately, so as[ix] points to its own block of memory.
    
    */
    
    /*
    int size = 10;

    int ** as = (int**) malloc(sizeof(int*) * size);
    for ( size_t ix = 0; ix < size; ++ix )
      as[ix] = (int*) malloc(sizeof(int) * size);

    for ( size_t ix = 0; ix < size; ++ix )
      for ( size_t jx = 0; jx < size; ++jx )
        as[ix][jx] = 0;

    printf("%d\n", as[0][0]);

    for ( size_t ix = 0; ix < size; ++ix )
        free(as[ix]);
    free(as);
    */
    
    // This approach can lead to memory fragmentation, since each row (as[ix]) is allocated
    // separately using malloc, meaning the rows are not guaranteed to be contiguous in memory.
    // They may be placed in different locations depending on the state of the heap at the
    // time of allocation. Hence, memory is scattered and fragmented rather than stored in one block.
    
    // Conclusion:
    // The first approach avoids fragmentation by allocating memory
    // contiguously, while the second approach allocates each row
    // separately, which can lead to memory fragmentation.
    
    // ##############################################
    // Writing to files
    // ##############################################
    
    // Program 1: Writing the Matrix to a File
    
    /*
    // 1) Opens a file for writing
    FILE *file = fopen("matrix.txt", "w");
    int size = 10;

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // 2) Writes a square matrix of size 10 with int entries (ix*jx in the ix-th row and jx-th column) to that file
    for (int ix = 0; ix < size; ++ix) {
        for (int jx = 0; jx < size; ++jx) {
            fprintf(file, "%d ", (int) ix * jx);
        }
        fprintf(file, "\n");
    }

    // 3) Closes the file.
    fclose(file);
    */
    
    
    // Program 2: Reading the Matrix from a File
    
    /*
    // 1) Reopens the file for reading
    FILE *file = fopen("matrix.txt", "r");
    int size = 10;
    int value;

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // 2) Reads the matrix from the file
    for (int ix = 0; ix < size; ++ix) {
        for (int jx = 0; jx < size; ++jx) {
            fscanf(file, "%d", &value);
            
            // 3) Checks that the entry in the ix-th row and jx-th column equals ix*jx
            if (value != ix * jx) {
                printf("Mismatch at (%d, %d): expected %d, found %d\n", ix, jx, ix * jx, value);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    printf("Matrix read correctly!\n");
    */
    
    // How does your choice of memory allocation (contiguous vs. noncontiguous)
    // impact the possibilties to write the matrix in text and binary format?
    
    // ANSWER:
    /*
    Contiguous Memory Allocation:
    - In both text and binary formats, this method is simpler and more efficient.
    - For binary format, the entire matrix can be written and read in a single fwrite/fread operation, making it extremely fast and convenient.
    - Text format is also straightforward since you can traverse the single block of memory in a loop.
     
    Noncontiguous Memory Allocation:
    - In text format, the process is only slightly more complex since you need to handle each row separately.
    - In binary format, it is significantly less efficient because you must write and read each row separately, leading to multiple fwrite/fread operations. This increases complexity and reduces performance.
     */
    
    
    // ##############################################
    // Parsing command line arguments
    // ##############################################
    
    /*
    int A = 0, B = 0;  // Variables to store the values of A and B

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            // Handle "-a 2" case by checking if the next argument exists
            A = atoi(argv[i + 1]);
            i++;  // Skip the next argument as it's part of the current flag
        }
        else if (strncmp(argv[i], "-a", 2) == 0) {
            // Handle "-a2" case
            A = atoi(argv[i] + 2);
        }
        else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            // Handle "-b 4" case by checking if the next argument exists
            B = atoi(argv[i + 1]);
            i++;  // Skip the next argument
        }
        else if (strncmp(argv[i], "-b", 2) == 0) {
            // Handle "-b4" case
            B = atoi(argv[i] + 2);
        }
    }

    // Print the values of A and B
    printf("A is %d and B is %d\n", A, B);
    */
    
    // This program parses -a and -b options, extracting the integers A and B and printing them
    
    // ##############################################
    // Naive benchmarking
    // ##############################################
    
    long long int sum = 0;
    int iterations = 1e1;  // Number of times to repeat the computation

    clock_t start = clock();  // Start time

    for (int i = 0; i < iterations; ++i) {
        sum = 0;
        for (int j = 0; j < 1e9; ++j) {  // Sum of first billion integers
            sum += j;
        }
    }

    clock_t end = clock();  // End time
    
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sum: %lld\n", sum);
    printf("Time per iteration: %f seconds\n", elapsed_time / iterations);
    
    return 0;
    
    /*
    Following compilers were used:
     -O0: No optimization. The program runs exactly as written without any compiler optimizations.
     -O1: Basic optimizations are applied.
     -O2: More aggressive optimizations without compromising the performance vs. compilation time.
     -O3: Maximum optimizations are applied for performance, which may include aggressive inlining and loop unrolling.
     -Os: Optimizes for code size, potentially sacrificing some performance.
     -Og: Optimizes for debugging, preserving the debuggability of the code.
     
    Hence compiling with:
     gcc -O0 benchmarking.c -o benchmarking_O0
     gcc -O1 benchmarking.c -o benchmarking_O1
     gcc -O2 benchmarking.c -o benchmarking_O2
     gcc -O3 benchmarking.c -o benchmarking_O3
     gcc -Os benchmarking.c -o benchmarking_Os
     gcc -Og benchmarking.c -o benchmarking_Og
    
    Results (mean over 10 iterations):
     - O0: 2.101504 seconds
     - O0: 0.000000 seconds
     - O0: 0.000000 seconds
     - O0: 0.000000 seconds
     - O0: 0.000000 seconds
    
    Discussion:
     With no optimizations (-O0), the compiler executes the code exactly as written.
     This will likely result in the slowest runtime because no attempts are made to
     improve performance. As you increase the optimization level (-O1, -O2, -O3),
     the compiler applies techniques such as loop unrolling (compiler might unroll
     the loop to reduce the number of iterations), constant folding (if the sum
     computation is predictable, the compiler might precompute parts of it) and
     register allocation (variables might be stored in CPU registers for faster
     access). Os optimizes for size, so it may avoid certain optimizations that
     bloat the code (like loop unrolling), while Og balances optimizations with
     debugging, ensuring that the program is still debuggable while applying some
     optimizations.
     
    */
}

 
