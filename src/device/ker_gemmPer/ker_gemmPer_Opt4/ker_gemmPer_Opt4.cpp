#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <ap_fixed.h>

// TYPEDATA COMPILATOR VARIABLE
//**********************************
#define TYPEDATA_BITS_SIZE 16
#define TYPEDATA_BITS_INT 7
typedef ap_fixed<TYPEDATA_BITS_SIZE, TYPEDATA_BITS_INT> typeData;

// DATASIZE COMPILATOR VARIABLE
//**********************************
#ifdef MINI_DATASET
    #define NI 20
    #define NJ 25
    #define NK 30
#elif defined(SMALL_DATASET)
    #define NI 60
    #define NJ 70
    #define NK 80
#elif defined(MEDIUM_DATASET)
    #define NI 200
    #define NJ 220
    #define NK 240
#elif defined(LARGE_DATASET)
    #define NI 1000
    #define NJ 1100
    #define NK 1200
#elif defined(EXTRALARGE_DATASET)
    #define NI 2000
    #define NJ 2300
    #define NK 2600
#else
    #define NI 0
    #define NJ 0
    #define NK 0
#endif

#define GEMM_ALPHA 1.5f
#define GEMM_BETA 1.2f


extern "C"{

    void readData_A(typeData *inD_A, typeData *inD_A_local){
        for (int i = 0 ; i < NI*NK ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=NI*NK max=NI*NK
            #pragma HLS UNROLL factor=2
            inD_A_local[i] = inD_A[i];
        }
        return;
    }

    void readData_B(typeData *inD_B, typeData *inD_B_local){
        for (int i = 0 ; i < NK*NJ ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=NK*NJ max=NK*NJ
            #pragma HLS UNROLL factor=2
            inD_B_local[i] = inD_B[i];
        }
        return;
    }

    void readData_C(typeData *inD_C, typeData *inD_C_local, typeData *outD_result_local){
        for (int i = 0 ; i < NI*NJ ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=NI*NJ max=NI*NJ
            #pragma HLS UNROLL factor=2
            inD_C_local[i] = inD_C[i];
            outD_result_local[i] = inD_C[i];
        }  
        return;
    }

    void readData(typeData *inD_A, typeData *inD_A_local, typeData *inD_B, typeData *inD_B_local, typeData *inD_C, typeData *inD_C_local, typeData *outD_result_local){
        #pragma HLS DATAFLOW
        readData_A(inD_A, inD_A_local);
        readData_B(inD_B, inD_B_local);
        readData_C(inD_C, inD_C_local, outD_result_local);
        return;
    }

    void processData(typeData *inD_A_local, typeData *inD_B_local, typeData *inD_C_local, typeData *outD_result_local){
        typeData alpha = GEMM_ALPHA;
        typeData beta = GEMM_BETA;

        for (int i = 0; i < NI; i++) {
            for (int j = 0; j < NJ; j++){
                #pragma HLS PIPELINE II=1   
                #pragma HLS LOOP_TRIPCOUNT min=NJ max=NJ
                #pragma HLS UNROLL factor=2    
                outD_result_local[(i*NJ)+j] *= beta;
            }
            for (int k = 0; k < NK; k++){
                for (int j = 0; j < NJ; j++){
                    #pragma HLS PIPELINE II=1
                    #pragma HLS LOOP_TRIPCOUNT min=NJ max=NJ
                    #pragma HLS UNROLL factor=2    
                    outD_result_local[(i*NJ)+j] += alpha * inD_A_local[(i*NK)+k] * inD_B_local[(k*NJ)+j];
                }
            }
        }
        return;
    }

    void writedata(typeData *outD_result, typeData *outD_result_local){
        for (int i=0; i<NI; i++){
            for (int j=0; j<NJ; ++j){
                #pragma HLS PIPELINE II=1
                #pragma HLS LOOP_TRIPCOUNT min=NK max=NK
                #pragma HLS UNROLL factor=2  
                outD_result[(i*NJ)+j] = outD_result_local[(i*NJ)+j];
            }
        }
        return;
    }


    #ifdef MINI_DATASET
        void ker_gemmPer_Opt4_mini(typeData *inD_A, typeData *inD_B, typeData *inD_C, typeData *outD_result)
    #elif defined(SMALL_DATASET)
        void ker_gemmPer_Opt4_small(typeData *inD_A, typeData *inD_B, typeData *inD_C, typeData *outD_result)
    #elif defined(MEDIUM_DATASET)
        void ker_gemmPer_Opt4_medium(typeData *inD_A, typeData *inD_B, typeData *inD_C, typeData *outD_result)
    #elif defined(LARGE_DATASET)
        void ker_gemmPer_Opt4_large(typeData *inD_A, typeData *inD_B, typeData *inD_C, typeData *outD_result)
    #elif defined(EXTRALARGE_DATASET)
        void ker_gemmPer_Opt4_extralarge(typeData *inD_A, typeData *inD_B, typeData *inD_C, typeData *outD_result)
    #else
        void ker_gemmPer_Opt4(typeData *inD_A, typeData *inD_B, typeData *inD_C, typeData *outD_result)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_A offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = inD_B offset = slave bundle = gmem1
        #pragma HLS INTERFACE m_axi port = inD_C offset = slave bundle = gmem2
        #pragma HLS INTERFACE m_axi port = outD_result offset = slave bundle = gmem2

        #pragma HLS INTERFACE s_axilite port = inD_A bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_B bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_C bundle = control
        #pragma HLS INTERFACE s_axilite port = outD_result bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control

        typeData inD_A_local[NI*NK];
        typeData inD_B_local[NK*NJ];
        typeData inD_C_local[NI*NJ];
        typeData outD_result_local[NI*NJ];

        readData(inD_A, inD_A_local, inD_B, inD_B_local, inD_C, inD_C_local, outD_result_local);
        processData(inD_A_local,  inD_B_local,  inD_C_local,  outD_result_local);
        writedata(outD_result, outD_result_local);

        return;
    }
}