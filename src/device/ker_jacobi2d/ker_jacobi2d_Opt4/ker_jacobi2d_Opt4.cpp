#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <ap_fixed.h>

// TYPEDATA COMPILER VARIABLE
//**********************************
#define TYPEDATA_BITS_SIZE 16
#define TYPEDATA_BITS_INT 7
typedef ap_fixed<TYPEDATA_BITS_SIZE, TYPEDATA_BITS_INT> typeData;


// DATASIZE COMPILATOR VARIABLE
//**********************************
#ifdef MINI_DATASET
    #define STEPS 20
    #define SIZE_N 30
#elif defined(SMALL_DATASET)
    #define STEPS 40
    #define SIZE_N 90
#elif defined(MEDIUM_DATASET)
    #define STEPS 100
    #define SIZE_N 250
#elif defined(LARGE_DATASET)
    #define STEPS 500
    #define SIZE_N 1300
#elif defined(EXTRALARGE_DATASET)
    #define STEPS 1000
    #define SIZE_N 2800
#else
    #define STEPS 0
    #define SIZE_N 0
#endif


#define WIDTH_OF_ACCESS 512
#define SIZE_OF_TYPEDATA sizeof(typeData)
#define VECTOR_SIZE (WIDTH_OF_ACCESS/SIZE_OF_TYPEDATA)

extern "C"{

    void readData_A(typeData *inD_A, typeData *inD_A_local){
        for (int i = 0; i < SIZE_N*SIZE_N; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N-1 max=SIZE_N-1
            #pragma HLS UNROLL factor=2
            inD_A_local[i] = inD_A[i];
        }
        return;
    }

    void readData_B(typeData *inD_B, typeData *inD_B_local){
        for (int i = 0; i < SIZE_N*SIZE_N ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N-1 max=SIZE_N-1
            #pragma HLS UNROLL factor=2
            inD_B_local[i] = inD_B[i];
        }        
        return;
    }

    void readData(typeData *inD_A, typeData *inD_B, typeData *inD_A_local, typeData *inD_B_local){
        #pragma HLS DATAFLOW
        readData_A(inD_A, inD_A_local);
        readData_B(inD_B, inD_B_local);
        return;
    }

    void innerLoop1(typeData *inD_A_local, typeData *inD_B_local, int i){
        typeData factor=0.2;
        for (int j = 1; j < SIZE_N - 1 ; j++){
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N-1 max=SIZE_N-1
            #pragma HLS UNROLL factor=2      
            inD_B_local[(i*SIZE_N)+j] = factor * (inD_A_local[(i*SIZE_N)+j] + inD_A_local[(i*SIZE_N)+(j-1)] + inD_A_local[(i*SIZE_N)+(j+1)] + inD_A_local[((i+1)*SIZE_N)+j] + inD_A_local[((i-1)*SIZE_N)+j]);
        }
        return;
    }

    void innerLoop2(typeData *inD_A_local, typeData *inD_B_local, int i){
        typeData factor=0.2;
        for (int j = 1; j < SIZE_N - 1 ; j++){
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N-1 max=SIZE_N-1
            #pragma HLS UNROLL factor=2
            inD_A_local[(i*SIZE_N)+j] = factor * (inD_B_local[(i*SIZE_N)+j] + inD_B_local[(i*SIZE_N)+(j-1)] + inD_B_local[(i*SIZE_N)+(j+1)] + inD_B_local[((i+1)*SIZE_N)+j] + inD_B_local[((i-1)*SIZE_N)+j]);
        }
        return;  
    }

    void writeData_A(typeData *inD_A, typeData *inD_A_local){
        for (int i = 0; i < SIZE_N*SIZE_N; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N*SIZE_N; max=SIZE_N*SIZE_N;
            #pragma HLS UNROLL factor=2
            inD_A[i] = inD_A_local[i];
        }
        return;
    }

    void writeData_B(typeData *inD_B, typeData *inD_B_local){
        for (int i = 0; i < SIZE_N*SIZE_N ; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS LOOP_TRIPCOUNT min=SIZE_N*SIZE_N; max=SIZE_N*SIZE_N;
            #pragma HLS UNROLL factor=2
            inD_B[i] = inD_B_local[i];
        }        
        return;
    }

    void writeData(typeData *inD_A, typeData *inD_B, typeData *inD_A_local, typeData *inD_B_local) {
        #pragma HLS DATAFLOW
        readData_A(inD_A, inD_A_local);
        readData_B(inD_B, inD_B_local);
        return;
    }



    //*************************************
    // MAIN KERNEL FUNCTION - START
    //*************************************
    #ifdef MINI_DATASET
        void ker_jacobi2d_Opt4_mini(typeData *inD_A, typeData *inD_B)
    #elif defined(SMALL_DATASET)
        void ker_jacobi2d_Opt4_small(typeData *inD_A, typeData *inD_B)
    #elif defined(MEDIUM_DATASET)
        void ker_jacobi2d_Opt4_medium(typeData *inD_A, typeData *inD_B)
    #elif defined(LARGE_DATASET)
        void ker_jacobi2d_Opt4_large(typeData *inD_A, typeData *inD_B)
    #elif defined(EXTRALARGE_DATASET)
        void ker_jacobi2d_Opt4_extralarge(typeData *inD_A, typeData *inD_B)
    #else
        void ker_jacobi2d_Opt4(typeData *inD_A, typeData *inD_B)
    #endif
    {
        #pragma HLS INTERFACE m_axi port = inD_A offset = slave bundle = gmem
        #pragma HLS INTERFACE m_axi port = inD_B offset = slave bundle = gmem1

        #pragma HLS INTERFACE s_axilite port = inD_A bundle = control
        #pragma HLS INTERFACE s_axilite port = inD_B bundle = control
        #pragma HLS INTERFACE s_axilite port = return bundle = control

        typeData inD_A_local[SIZE_N*SIZE_N];
        typeData inD_B_local[SIZE_N*SIZE_N];

        readData(inD_A, inD_B, inD_A_local, inD_B_local);
        for (int t=0; t<STEPS ; t++){
            #pragma HLS PIPELINE off
            for (int i = 1; i < SIZE_N - 1 ; i++){
                #pragma HLS PIPELINE off
                innerLoop1(inD_A_local, inD_B_local, i);
            }
            for (int i = 1; i < SIZE_N - 1 ; i++){
                #pragma HLS PIPELINE off
                innerLoop2(inD_A_local, inD_B_local, i);
            }
        }
        writeData(inD_A, inD_B, inD_A_local, inD_B_local);
        
        return;   
    }
}
