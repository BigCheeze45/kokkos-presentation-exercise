#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"
#include "common/Measurements.h"
// SAVE #include "../common/Configuration.h"

using namespace std;

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

    // Checking command line options
    configuration.parse(argc, argv);
    if (!checkCommandLineOptions(configuration)) {
        return 1;
    }
    // End command line parsing

    // 2 - data allocation and initialization
    int Nx = configuration.getInt("Nx");
    int lower_bound_i = 0;
    int upper_bound_i = Nx - 1;
    float *A = NULL;
    float *B = NULL;
    float *C = NULL;

    // Allocate time-steps 0 & 1
    if (!allocateSpace(&B, configuration)) {
        printf("Could not allocate space array\n");
        return 1;
    }
    initializeSpace(B, configuration);

    if (!allocateSpace(&C, configuration)) {
        printf("Could not allocate array\n");
    }
    initializeSpace(C, configuration);

    if (!allocateSpace(&A, configuration)) {
        printf("Could not allocate array\n");
    }

    // run serial Jacobi 1D
    for (int i = lower_bound_i; i <= upper_bound_i; ++i) {
        A[i] = B[i] + C[i];
    }

    /*
     * SAVE
     * Begin timed test
     * double start_time = omp_get_wtime();
     * double end_time = omp_get_wtime();
     * double time = end_time - start_time
     * measurements.setField("elapsedTime",time);
     * End timed test
     */

    // 4 - Verification & output (optional)
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

    // Free the space in memory
    free(A);
    free(B);
    free(C);
    return 0;
}
