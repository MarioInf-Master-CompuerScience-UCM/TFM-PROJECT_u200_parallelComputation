#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <hls_stream.h>
#include <ap_fixed.h>
#include <hls_math.h>

// TYPEDATA COMPILER VARIABLE
//**********************************
#define TYPEDATA_BITS_SIZE 16
#define TYPEDATA_BITS_INT 7
typedef ap_fixed<TYPEDATA_BITS_SIZE, TYPEDATA_BITS_INT> typeData;


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

  #define UNROLL_FACTOR 8


// READING BY CHUNKS
//**********************************
#define WIDTH_OF_ACCESS 512
#define SIZE_OF_TYPEDATA sizeof(typeData)
#define VECTOR_SIZE (WIDTH_OF_ACCESS/SIZE_OF_TYPEDATA)
#define STREAM_SIZE 1024

using namespace hls;


extern "C"{

    void read_data(typeData *inD_vA, stream<typeData> &outStreamA, int offset) {
        for (int j = 0; j < STREAM_SIZE; j++) {
            #pragma HLS STREAM variable=outStreamA depth=STREAM_SIZE
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=STREAM_SIZE max=STREAM_SIZE
            #pragma HLS UNROLL factor=UNROLL_FACTOR
            outStreamA.write(inD_vA[offset + j]);
        }
        return;
    }

    void process_data(stream<typeData> &inStreamA, typeData *outD, int offset) {
        for (int j = 0; j < STREAM_SIZE; j++) {
            #pragma HLS STREAM variable=inStreamA depth=STREAM_SIZE
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=STREAM_SIZE max=STREAM_SIZE
            #pragma HLS UNROLL factor=UNROLL_FACTOR
            typeData a = inStreamA.read();
            outD[offset + j] =  hls::sqrt(a);
        }
        return;
    }

    //*************************************
    // MAIN KERNEL FUNCTION - START
    //*************************************
    #ifdef MINI_DATASET
        void ker_studyCase3_d_mini(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(SMALL_DATASET)
        void ker_studyCase3_d_small(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(MEDIUM_DATASET)
        void ker_studyCase3_d_medium(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(LARGE_DATASET)
        void ker_studyCase3_d_large(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #elif defined(EXTRALARGE_DATASET)
        void ker_studyCase3_d_extralarge(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #else
        void ker_studyCase3_d(typeData *inD_vA, typeData *inD_vB, typeData *outD_result)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_vA offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = inD_vB offset = slave bundle = gmem1
        #pragma HLS INTERFACE m_axi port = outD_result offset = slave bundle = gmem2

        #pragma HLS INTERFACE s_axilite port = inD_vA bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_vB bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_result bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control
        
        hls::stream<typeData> inD_vA_localStream;

        for (int i = 0; i < SIZE; i += STREAM_SIZE) {
            #pragma HLS DATAFLOW
            read_data(inD_vA, inD_vA_localStream, i);
            process_data(inD_vA_localStream, outD_result, i);
        }

        return;
    }
}