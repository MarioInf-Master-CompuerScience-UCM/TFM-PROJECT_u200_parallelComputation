#include <ap_fixed.h>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <hls_math.h>


// TYPEDATA COMPILATOR VARIABLE
//**********************************
#define TYPEDATA_BITS_SIZE 16
#define TYPEDATA_BITS_INT 7
typedef ap_fixed<TYPEDATA_BITS_SIZE, TYPEDATA_BITS_INT> typeData;


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

    void readData(typeData *inD_A, typeData *inD_A_local){
        for (int i = 0; i < SIZE_N*SIZE_N ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N max=SIZE_N
            #pragma HLS UNROLL factor=4
            inD_A_local[i] = inD_A[i];
        }
        return;
    }

    void processData(typeData *inD_A_local, typeData *outD_A_local){
        for (int i = 0; i < SIZE_N; i++) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < j; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS LOOP_TRIPCOUNT min=0 max=SIZE_N
                    #pragma HLS UNROLL factor=4
                    outD_A_local[(i*SIZE_N) + j] -= inD_A_local[(i*SIZE_N) + k] * inD_A_local[(j*SIZE_N) + k];
                }
                outD_A_local[(i*SIZE_N) + j] /= inD_A_local[(j*SIZE_N) + j];
            }

            for (int k = 0; k < i; k++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS LOOP_TRIPCOUNT min=0 max=SIZE_N
                #pragma HLS UNROLL factor=4
                outD_A_local[(i*SIZE_N) + i] -= inD_A_local[(i*SIZE_N) + k] * inD_A_local[(i*SIZE_N) + k];
            }
            outD_A_local[(i*SIZE_N) + i] = hls::sqrt(inD_A_local[(i*SIZE_N) + i]);
        }        
    }

    void writeData(typeData *outD_A, typeData *outD_A_local){
        for (int i = 0; i < SIZE_N*SIZE_N ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N max=SIZE_N
            #pragma HLS UNROLL factor=4
            outD_A[i] = outD_A_local[i];
        }
        return;
    }


    //*************************************
    // MAIN KERNEL FUNCTION - START
    //*************************************
    #ifdef MINI_DATASET
        void ker_cholesky_Opt4_mini(typeData *inD_A, typeData *outD_A)
    #elif defined(SMALL_DATASET)
        void ker_cholesky_Opt4_small(typeData *inD_A, typeData *outD_A)
    #elif defined(MEDIUM_DATASET)
        void ker_cholesky_Opt4_medium(typeData *inD_A, typeData *outD_A)
    #elif defined(LARGE_DATASET)
        void ker_cholesky_Opt4_large(typeData *inD_A, typeData *outD_A)
    #elif defined(EXTRALARGE_DATASET)
        void ker_cholesky_Opt4_extralarge(typeData *inD_A, typeData *outD_A)
    #else
        void ker_cholesky_Opt4(typeData *inD_A, typeData *outD_A)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_A offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = outD_A offset = slave bundle = gmem1

        #pragma HLS INTERFACE s_axilite port = inD_A bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_A bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control

        typeData inD_A_local[SIZE_N*SIZE_N];
        typeData outD_A_local[SIZE_N*SIZE_N];

        readData(inD_A, inD_A_local);
        processData(inD_A_local, outD_A_local);
        writeData(outD_A, outD_A_local);        
        return;        
    }
}