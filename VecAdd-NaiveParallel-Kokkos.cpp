#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <string>
#include <sstream>

#include "util.h"
#include "common/Measurements.h"
#include "common/Configuration.h"

// EXERCISE: import Kokkos
 #include <Kokkos_Core.hpp>

using namespace std;
/*
 * Vector Add:
 *  A[i] = B[i] + C[i]
 */
float *A = NULL;
float *B = NULL;
float *C = NULL;

// EXERCISE: complete Vector Add functor
/*
 * A functor (or function objects) is simply a class or struct with a public operator() method
 * that defines the task to be done within the loop
 */
struct vec_add {
    /*
     * A functor's operator() defines the loop body. It takes an integer value which is the index
     * to use in the loop (parallel_for in our case). The operator() method must be const and must be marked
     * with the KOKKOS_INLINE_FUNCTION macro.
     *
     * If working with CUDA this marks your method as suitable for running on the CUDA device
     * as well as the host. No harm done if not using CUDA
     *
     * Kokkos maps work to cores
     *  each iteration is a unit of work
     *  the index identifies a particular unit of work
     *  iteration range identifies a total amount of work
     */
     KOKKOS_INLINE_FUNCTION
    void operator()(const int i) const {
        A[i] = B[i] + C[i];
    }
};

int main(int argc, char *argv[]) {
    // Rather than calling fflush
    setbuf(stdout, NULL);

    // 1 - Command line parsing
    Measurements measurements;
    Configuration configuration;

    /**************************************************************************
    **  Parameter options. Help and verify are constructor defaults  **********
    **************************************************************************/
    configuration.addParamInt("Nx", 'k', 100,
                              "--Nx <problem-size> for x-axis in elements (N)");

    configuration.addParamInt("Ny", 'l', 100,
                              "--Ny <problem-size> for y-axis in elements (N)");

    configuration.addParamInt("num_threads", 'p', 1,
                              "-p <num_threads>, number of cores");

    configuration.addParamInt("global_seed", 'g', 1524,
                              "--global_seed <global_seed>, seed for rng");

    configuration.addParamBool("n", 'n', false, "-n do not print time");

    configuration.parse(argc, argv);

    // Checking command line options
    if (!checkCommandLineOptions(configuration)) {
        return 1;
    }

    // End Command line parsing

    // EXERCISE: initialize Kokkos runtime
    /*
     * You must call initialize() before making any call to Kokkos.
     * with no arguments Kokkos is initialize in the default execution space or
     * you may also pass in argc and argv, analogously to MPI_Init(). It reads and removes
     * command-line arguments that start with ''--kokkos-'' for example:
     * --kokkos-threads (total number of threads)
     * --kokkos-device (device (GPU) ID to use)
     */
     Kokkos::initialize(argc, argv);

    // 2 - data allocation and initialization
    int Nx = configuration.getInt("Nx");
    /* Un-comment when using lambda implementation */
//    int lower_bound_i = 0;
//    int upper_bound_i = Nx - 1;

    // Allocate time-steps 0 and 1
    if (!allocateSpace(&B, configuration)) {
        printf("Could not allocate space array\n");
        return 1;
    }
    initializeSpace(B, configuration);

    if (!allocateSpace(&C, configuration)) {
        printf("Could not allocate space array\n");
        return 1;
    }
    initializeSpace(C, configuration);

    if (!allocateSpace(&A, configuration)) {
        printf("Could not allocate array\n");
    }
    
    Kokkos::parallel_for(Nx, vec_add());


    /*
     * If Kokkos was built with C++11 you can use lambdas functions to define loop body
     * making code more concise and readable.
     * functor or lambda? You choose!
    Kokkos::parallel_for(Nx, KOKKOS_LAMBDA(const int i){
        A[i] = B[i] + C[i];
    });
     */

    /*
     * Begin timed test
     * double start_time = omp_get_wtime();
     * double end_time = omp_get_wtime();
     * double time = end_time - start_time
     * measurements.setField("elapsedTime",time);
     * End timed test
     */

    // 4 - Verification and output (optional)
    if (configuration.getBool("v")) {
        if (verifyResultVecAdd(A, configuration)) {
            measurements.setField("\nverification", "SUCCESS");
        } else {
            measurements.setField("\nverification", "FAILURE");
        }
    }

    // Output
    if (!configuration.getBool("n")) {
        string ldap = configuration.toLDAPString();
        ldap += measurements.toLDAPString();
        cout << ldap;
        COUNT_MACRO_PRINT();
        cout << endl;
    }

    // End verification and output
    // EXERCISE: shutdown Kokkos to release allocated resources
    Kokkos::finalize();

    // Free the space in memory
    free(A);
    free(B);
    free(C);
    return 0;
}
