#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <hls_stream.h>

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
        
#define TIMES 3

// READING BY CHUNKS
//**********************************
#define WIDTH_OF_ACCESS 512
#define SIZE_OF_TYPEDATA sizeof(typeData)
#define VECTOR_SIZE (WIDTH_OF_ACCESS/SIZE_OF_TYPEDATA)
#define STREAM_SIZE 1024
#define UNROLL_FACTOR 8

using namespace hls;


extern "C"{

    void read_data(typeData *inD_vA, typeData *inD_vB, stream<typeData> &outStreamA, stream<typeData> &outStreamB, int offset) {
        for (int j = 0; j < STREAM_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=STREAM_SIZE max=STREAM_SIZE
            #pragma HLS UNROLL factor=UNROLL_FACTOR
            outStreamA.write(inD_vA[offset + j]);
            outStreamB.write(inD_vB[offset + j]);
        }
        return;
    }

    void process_data(stream<typeData> &inStreamA, stream<typeData> &inStreamB, typeData *outD, int offset) {
        typeData a[STREAM_SIZE];
        typeData b[STREAM_SIZE];
        typeData resultTemp[STREAM_SIZE];

        for (int j = 0; j < STREAM_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=STREAM_SIZE max=STREAM_SIZE
            #pragma HLS UNROLL factor=UNROLL_FACTOR
            a[j] = inStreamA.read();
            b[j] = inStreamB.read();
            resultTemp[j] = 0.0;
        }
        for (int time = 0; time < TIMES ; time++) {
            for (int j = 0; j < STREAM_SIZE; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS LOOP_TRIPCOUNT min=STREAM_SIZE max=STREAM_SIZE
                #pragma HLS UNROLL factor=UNROLL_FACTOR
                resultTemp[j] += a[j] + b[j];
            }
        }
        for (int j = 0; j < STREAM_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=STREAM_SIZE max=STREAM_SIZE
            #pragma HLS UNROLL factor=UNROLL_FACTOR
            outD[offset + j] = resultTemp[j];
        }
        return;
    }


    //*************************************
    // MAIN KERNEL FUNCTION - START
    //*************************************
    #ifdef MINI_DATASET
        void ker_studyCase2_c_mini(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(SMALL_DATASET)
        void ker_studyCase2_c_small(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(MEDIUM_DATASET)
        void ker_studyCase2_c_medium(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(LARGE_DATASET)
        void ker_studyCase2_c_large(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(EXTRALARGE_DATASET)
        void ker_studyCase2_c_extralarge(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #else
        void ker_studyCase2_c(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_vA offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = inD_vB offset = slave bundle = gmem1
        #pragma HLS INTERFACE m_axi port = outD_result offset = slave bundle = gmem2

        #pragma HLS INTERFACE s_axilite port = inD_vA bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_vB bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_result bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control
        
        stream<typeData> inD_vA_localStream;
        stream<typeData> inD_vB_localStream;

        for (int i = 0; i < SIZE; i += STREAM_SIZE) {
            #pragma HLS DATAFLOW
            read_data(inD_vA, inD_vB, inD_vA_localStream, inD_vB_localStream, i);
            process_data(inD_vA_localStream, inD_vB_localStream, outD_result, i);
        }

        return;
    }
}