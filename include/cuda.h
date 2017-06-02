/**
 * @file cuda.h
 * @author cs
 * @brief This header file contains the CUDA kernels used in benchmark.
 */
#ifndef CUDA_H
#define CUDA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cublas.h>

/* #include <iostream> */
/* #include <cstdlib> */
/* #include <ctime> */
/* #include <cublas_v2.h> */
/* #include <curand.h> */

/* #include <thrust/host_vector.h> */
/* #include <thrust/device_vector.h> */

double timeDiff( struct timespec *t1, struct timespec *t2)
{
  double T1, T2;
  T2 = (double)t2->tv_sec + (double)t2->tv_nsec / 1.0e9;
  T1 = (double)t1->tv_sec - (double)t1->tv_nsec / 1.0e9;
  return(T2 - T1);
}

/**
 * @brief General Matrix Multiplication Using Double Precision
 *
 * See https://wiki.rc.ufl.edu/doc/CUDA_Examples.
 *
 */
int dgemm(double *dgemm_time, double *dgemm_rate)
{
    int       dim = 1000;
    int       i,j/*,k*/;
    int       status;

    double    *psa, *psb, *psc;
    double    *sap, *sbp, *scp;
    double    *pda, *pdb, *pdc;
    // double    *dap, *dbp, *dcp;

    double alpha   = 1.0;
    double beta    = 0.0;
    // double gflops  = 0.0;
    float  deltaT  = 0.0;
    double gflopCnt = 2.0 * dim * dim * dim / 1.0e9;
    // struct timespec t1;
    // struct timespec t2;
    clock_t start, end;
 
    int ptime();

    pda = NULL;
    pdb = NULL;
    pdc = NULL;
    psa = (double *) malloc(dim * dim * sizeof(*psa) );
    psb = (double *) malloc(dim * dim * sizeof(*psb) );
    psc = (double *) malloc(dim * dim * sizeof(*psc) );

    /* Initialize CUDA */
    /* printf("Initializing CUDA..."); */
    status = cublasInit();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! CUBLAS initialization error\n");
        return EXIT_FAILURE;
    }
    /* printf("Done.\n"); */

    /* printf("Initializing Matrices..."); */
    // clock_gettime(CLOCK_MONOTONIC, &t1);
    sap = psa;
    sbp = psb;
    scp = psc;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            *sap++ = 1.0;
            *sbp++ = 1.0;
            *scp++ = 0.0;
        }
    }
    // clock_gettime(CLOCK_MONOTONIC, &t2); 
    // deltaT = timeDiff(&t1, &t2);
    /* printf("Done.  Elapsed Time = %6.4f secs\n", deltaT); */
    fflush(stdout);

    /* Allocate device memory for the matrices */
    /* printf("Starting CUDA DGEMM..."); */
    // clock_gettime(CLOCK_MONOTONIC, &t1);
    start = clock();
  
    status = cublasAlloc(dim*dim, sizeof(*pda), (void**) &pda);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (A)\n");
        return EXIT_FAILURE;
    }

    status = cublasAlloc(dim*dim, sizeof(*pdb), (void**) &pdb);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (B)\n");
        return EXIT_FAILURE;
    }

    status = cublasAlloc(dim*dim, sizeof(*pdc), (void**) &pdc);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (C)\n");
        return EXIT_FAILURE;
    }

    /* initialize the device matrices with the host matrices */
    status = cublasSetVector(dim*dim, sizeof(*psa), psa, 1, pda, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write A)\n");
        return EXIT_FAILURE;
    }

    status = cublasSetVector(dim*dim, sizeof(*pdb), psb, 1, pdb, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write B)\n");
        return EXIT_FAILURE;
    }

    status = cublasSetVector(dim*dim, sizeof(*psc), psc, 1, pdc, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write C)\n");
        return EXIT_FAILURE;
    }

    /* Clear last error */
    cublasGetError();

    /* Performs operation using cublas */
    cublasDgemm('n', 'n', dim, dim, dim, alpha, pda, dim, pdb, dim, beta, pdc, dim);
    status = cublasGetError();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! kernel execution error.\n");
        return EXIT_FAILURE;
    }

    /* Read the result back */
    status = cublasGetVector(dim*dim, sizeof(*psc), pdc, 1, psc, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (read C)\n");
        return EXIT_FAILURE;
    }
    // clock_gettime(CLOCK_MONOTONIC, &t2);
    end = clock();
    // deltaT = timeDiff(&t1, &t2);
    deltaT = (end-start)/(double)CLOCKS_PER_SEC;
    /* printf("Done.       Elapsed Time = %6.4f secs\n", deltaT); */
    /* printf("                                  "); */
    /* printf("GFlOP Rate   = %8.4f\n", gflopCnt/deltaT); */
    *dgemm_time = deltaT;
    *dgemm_rate = gflopCnt/deltaT;
    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////

// /**
//  * @brief Fill the array A(nr_rows_A, nr_cols_A) with random numbers on GPU
//  */
// void GPU_fill_rand(float *A, int nr_rows_A, int nr_cols_A) {
// 	// Create a pseudo-random number generator
// 	curandGenerator_t prng;
// 	curandCreateGenerator(&prng, CURAND_RNG_PSEUDO_DEFAULT);

// 	// Set the seed for the random number generator using the system clock
// 	curandSetPseudoRandomGeneratorSeed(prng, (unsigned long long) clock());

// 	// Fill the array with random numbers on the device
// 	curandGenerateUniform(prng, A, nr_rows_A * nr_cols_A);
// }


// /**
//  * @brief Multiply the arrays A and B on GPU and save the result in C
//  * C(m,n) = A(m,k) * B(k,n)
//  */
// void gpu_blas_mmul(const float *A, const float *B, float *C, const int m, const int k, const int n) {
// 	int lda=m,ldb=k,ldc=m;
// 	const float alf = 1;
// 	const float bet = 0;
// 	const float *alpha = &alf;
// 	const float *beta = &bet;

// 	// Create a handle for CUBLAS
// 	cublasHandle_t handle;
// 	cublasCreate(&handle);

// 	// Do the actual multiplication
// 	cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);

// 	// Destroy the handle
// 	cublasDestroy(handle);
// }

// /**
//  * @brief Print matrix A(nr_rows_A, nr_cols_A) storage in column-major format
//  */
// void print_matrix(const thrust::device_vector<float> &A, int nr_rows_A, int nr_cols_A) {

//     for(int i = 0; i < nr_rows_A; ++i){
//         for(int j = 0; j < nr_cols_A; ++j){
//             std::cout << A[j * nr_rows_A + i] << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << std::endl;
// }

// /**
//  * @brief General Matrix Multiplication Using Single Precision
//  *
//  * See https://solarianprogrammer.com/2012/05/31/matrix-multiplication-cuda-cublas-curand-thrust/.
//  * High level matrix multiplication on GPU using CUDA with Thrust, CURAND and CUBLAS
//  * C(m,n) = A(m,k) * B(k,n)
//  */
// int sgemm() {
// 	// Allocate 3 arrays on CPU
// 	int nr_rows_A, nr_cols_A, nr_rows_B, nr_cols_B, nr_rows_C, nr_cols_C;

// 	// for simplicity we are going to use square arrays
// 	nr_rows_A = nr_cols_A = nr_rows_B = nr_cols_B = nr_rows_C = nr_cols_C = 3;

// 	thrust::device_vector<float> d_A(nr_rows_A * nr_cols_A), d_B(nr_rows_B * nr_cols_B), d_C(nr_rows_C * nr_cols_C);

// 	// Fill the arrays A and B on GPU with random numbers
// 	GPU_fill_rand(thrust::raw_pointer_cast(&d_A[0]), nr_rows_A, nr_cols_A);
// 	GPU_fill_rand(thrust::raw_pointer_cast(&d_B[0]), nr_rows_B, nr_cols_B);

// 	// Optionally we can print the data
// 	std::cout << "A =" << std::endl;
// 	print_matrix(d_A, nr_rows_A, nr_cols_A);
// 	std::cout << "B =" << std::endl;
// 	print_matrix(d_B, nr_rows_B, nr_cols_B);

// 	// Multiply A and B on GPU
// 	gpu_blas_mmul(thrust::raw_pointer_cast(&d_A[0]), thrust::raw_pointer_cast(&d_B[0]), thrust::raw_pointer_cast(&d_C[0]), nr_rows_A, nr_cols_A, nr_cols_B);

// 	//Print the result
// 	std::cout << "C =" << std::endl;
// 	print_matrix(d_C, nr_rows_C, nr_cols_C);

// 	return 0;
// }

#endif
