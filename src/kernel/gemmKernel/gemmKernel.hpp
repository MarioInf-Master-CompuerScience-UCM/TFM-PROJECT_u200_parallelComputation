#ifndef _GEMMKERNEL_HPP_
#define _GEMMKERNEL_HPP_

#include <vector>
#include <iostream>
#include "../../configParams/configParams.hpp"

using namespace std;
using globalConfiguration_typeData::typeData;

class GemmKernel{



    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        unsigned int SIZE_I;
        unsigned int SIZE_J;
        unsigned int SIZE_K;

        typeData alpha;
        typeData beta;

        vector< vector<typeData>> A;               //SIZE_I x SIZE_K
        vector< vector<typeData>> B;               //SIZE_K x SIZE_J
        vector< vector<typeData>> C;               //SIZE_I x SIZE_J

        vector< vector<typeData>> resultCPU;       //SIZE_I x SIZE_J
        vector< vector<typeData>> resultCPU_opt;   //SIZE_I x SIZE_J
        vector< vector<typeData>> resultDevice;    //SIZE_I x SIZE_J



    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:

        //********************************
        //* CONSTRUCTORS AND DESTRUCTORS *
        //********************************
        GemmKernel(typeData alpha, typeData beta, unsigned int SIZE_I, unsigned int SIZE_J, unsigned int SIZE_K);
        ~GemmKernel();

        void initData_A();
        void initData_B();
        void initData_C();
        void initData_resultCPU();
        void initData_resultCPU_opt();
        void initData_resultDevice();
        
        string printData_A();
        string printData_B();
        string printData_C();
        string printData_resultCPU();
        string printData_resultCPU_opt();
        string printData_resultDevice();
        string printAll();

        void kernel_gemm_CPU();
        void kernel_gemm_CPU_opt();



        //*************************
        //* GET AND SET FUNCTIONS *
        //*************************
        unsigned int get_SIZE_I();
        void set_SIZE_I(unsigned int data);

        unsigned int get_SIZE_J();
        void set_SIZE_J(unsigned int data);

        unsigned int get_SIZE_K();
        void set_SIZE_K(unsigned int data);

        typeData get_alpha();
        void set_alpha(typeData data);
        
        typeData get_beta();
        void set_beta(typeData data);

        vector< vector<typeData>>& get_A();
        void set_A(vector< vector<typeData>> newList);
        
        vector< vector<typeData>>& get_B();
        void set_B(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_C();
        void set_C(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_resultCPU();
        void set_resultCPU(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_resultCPU_opt();
        void set_resultCPU_opt(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_resultDevice();
        void set_resultDevice(vector< vector<typeData>> newList);

        
};
#endif
