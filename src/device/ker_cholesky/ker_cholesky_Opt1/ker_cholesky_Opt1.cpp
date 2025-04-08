#include <stdio.h>
#include <cmath>
#include <stdlib.h>

// TYPEDATA COMPILATOR VARIABLE
//**********************************
typedef float typeData;


// DATASIZE COMPILATOR VARIABLE
//**********************************
#ifdef MINI_DATASET
    #define SIZE_N 40
#elif defined(SMALL_DATASET)
    #define SIZE_N 120
#elif defined(MEDIUM_DATASET)
    #define SIZE_N 400
#elif defined(LARGE_DATASET)
    #define SIZE_N 2000
#elif defined(EXTRALARGE_DATASET)
    #define SIZE_N 4000
#else
    #define SIZE_N 0
#endif


extern "C"{

    //*************************************
    // MAIN KERNEL FUNCTION - START
    //*************************************
    #ifdef MINI_DATASET
        void ker_cholesky_Opt1_mini(typeData *inD_A, typeData *outD_A)
    #elif defined(SMALL_DATASET)
        void ker_cholesky_Opt1_small(typeData *inD_A, typeData *outD_A)
    #elif defined(MEDIUM_DATASET)
        void ker_cholesky_Opt1_medium(typeData *inD_A, typeData *outD_A)
    #elif defined(LARGE_DATASET)
        void ker_cholesky_Opt1_large(typeData *inD_A, typeData *outD_A)
    #elif defined(EXTRALARGE_DATASET)
        void ker_cholesky_Opt1_extralarge(typeData *inD_A, typeData *outD_A)
    #else
        void ker_cholesky_Opt1(typeData *inD_A, typeData *outD_A)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_A offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = outD_A offset = slave bundle = gmem 

        #pragma HLS INTERFACE s_axilite port = inD_A bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_A bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control

        typeData inD_A_local[SIZE_N*SIZE_N];
        typeData outD_A_local[SIZE_N*SIZE_N];


        for (int i = 0; i < SIZE_N*SIZE_N ; i++) {
            #pragma HLS PIPELINE off
            inD_A_local[i] = inD_A[i];
            outD_A_local[i] = 0.0;
        }

        for (int i = 0; i < SIZE_N; i++) {
            #pragma HLS PIPELINE off
            for (int j = 0; j < i; j++) {
                #pragma HLS PIPELINE off
                for (int k = 0; k < j; k++) {
                    #pragma HLS PIPELINE off
                    outD_A_local[(i*SIZE_N) + j] -= inD_A_local[(i*SIZE_N) + k] * inD_A_local[(j*SIZE_N) + k];
                }
                outD_A_local[(i*SIZE_N) + j] /= inD_A_local[(j*SIZE_N) + j];
            }

            for (int k = 0; k < i; k++) {
                #pragma HLS PIPELINE off
                outD_A[(i*SIZE_N) + i] -= inD_A_local[(i*SIZE_N) + k] * inD_A_local[(i*SIZE_N) + k];
            }
            outD_A_local[(i*SIZE_N) + i] = sqrt(inD_A_local[(i*SIZE_N) + i]);
        }

        for (int i = 0; i < SIZE_N*SIZE_N ; i++) {
            #pragma HLS PIPELINE off
            outD_A[i] = outD_A_local[i];
        }
        
        return;        
    }
}