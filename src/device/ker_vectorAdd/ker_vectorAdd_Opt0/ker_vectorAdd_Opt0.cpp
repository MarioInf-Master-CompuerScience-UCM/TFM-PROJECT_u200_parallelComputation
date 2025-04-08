#include <stdio.h>
#include <cmath>
#include <stdlib.h>

// TYPEDATA COMPILER VARIABLE
//**********************************
typedef float typeData;


// DATASIZE COMPILER VARIABLE
//**********************************
#ifdef MINI_DATASET
    #define SIZE (1024 * 1024 * 2)
#elif defined(SMALL_DATASET)
    #define SIZE (1024 * 1024 * 4)
#elif defined(MEDIUM_DATASET)
    #define SIZE (1024 * 1024 * 8)
#elif defined(LARGE_DATASET)
    #define SIZE (1024 * 1024 * 16)
#elif defined(EXTRALARGE_DATASET)
    #define SIZE (1024 * 1024 * 32)
#else
    #define SIZE 0
#endif


extern "C"{

    #ifdef MINI_DATASET
        void ker_vectorAdd_Opt0_mini(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(SMALL_DATASET)
        void ker_vectorAdd_Opt0_small(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(MEDIUM_DATASET)
        void ker_vectorAdd_Opt0_medium(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(LARGE_DATASET)
        void ker_vectorAdd_Opt0_large(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(EXTRALARGE_DATASET)
        void ker_vectorAdd_Opt0_extralarge(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #else
        void ker_vectorAdd_Opt0(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_vA offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = inD_vB offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = outD_result offset = slave bundle = gmem 

        #pragma HLS INTERFACE s_axilite port = inD_vA bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_vB bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_result bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control

        for (int i = 0; i < SIZE; i++) {
        #pragma HLS PIPELINE off
            outD_result[i] = inD_vA[i] + inD_vB[i];
        }    

        return;
    }    
}