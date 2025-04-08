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

#define TIMES 1        

// READING BY CHUNKS
//**********************************
#define WIDTH_OF_ACCESS 512
#define SIZE_OF_TYPEDATA sizeof(typeData)
#define VECTOR_SIZE (WIDTH_OF_ACCESS/SIZE_OF_TYPEDATA)
#define STREAM_SIZE 1024



extern "C"{

    //*************************************
    // MAIN KERNEL FUNCTION - START
    //*************************************
    #ifdef MINI_DATASET
        void ker_studyCase1_a_mini(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(SMALL_DATASET)
        void ker_studyCase1_a_small(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(MEDIUM_DATASET)
        void ker_studyCase1_a_medium(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(LARGE_DATASET)
        void ker_studyCase1_a_large(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(EXTRALARGE_DATASET)
        void ker_studyCase1_a_extralarge(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #else
        void ker_studyCase1_a(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_vA offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = inD_vB offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = outD_result offset = slave bundle = gmem 

        #pragma HLS INTERFACE s_axilite port = inD_vA bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_vB bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_result bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control

        typeData inD_vA_local[STREAM_SIZE];
        typeData inD_vB_local[STREAM_SIZE];
        typeData outD_result_local[STREAM_SIZE];
        int actualChunkSize=0;

        for (int i = 0; i < SIZE; i += STREAM_SIZE) {

            actualChunkSize = STREAM_SIZE;
            if ((i + STREAM_SIZE) > SIZE){
                actualChunkSize = SIZE - i;
            }

            for (int j = 0; j < actualChunkSize; j++) {
                #pragma HLS PIPELINE off
                inD_vA_local[j] = inD_vA[i + j];
                inD_vB_local[j] = inD_vB[i + j];
                outD_result_local[j] = 0.0f;
            }

            for (int time = 0; time < TIMES; time++) {
                #pragma HLS PIPELINE off
                for (int j = 0; j < actualChunkSize; j++) {
                    #pragma HLS PIPELINE off
                    outD_result_local[j] += (inD_vA_local[j] + inD_vB_local[j]);
                }
            }

            for (int j = 0; j < actualChunkSize; j++) {
                #pragma HLS PIPELINE off
                outD_result[i + j] += outD_result_local[j];
            }
        }

        return;
    }
}