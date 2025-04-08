#ifndef _JACOBI_2DKERNEL_HPP_
#define _JACOBI_2DKERNEL_HPP_

#include <vector>
#include <iostream>
#include "../../configParams/configParams.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;


class Jacobi_2dKernel{

    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        unsigned int SIZE_N;
        unsigned int STEPS;

        vector< vector< typeData>> A;               //SIZE_N x SIZE_N
        vector< vector< typeData>> B;               //SIZE_N x SIZE_N
        vector< vector< typeData>> resultCPU;       //SIZE_N x SIZE_N x 2
        vector< vector< typeData>> resultCPU_opt;   //SIZE_N x SIZE_N x 2
        vector< vector< typeData>> resultDevice;    //SIZE_N x SIZE_N x 2



    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:

        //********************************
        //* CONSTRUCTORS AND DESTRUCTORS *
        //********************************
        Jacobi_2dKernel(unsigned int STEPS, unsigned int SIZE_N);
        ~Jacobi_2dKernel();

        void initData_A(unsigned int SIZE_N);
        void initData_B(unsigned int SIZE_N);
        void initData_resultCPU(unsigned int SIZE_N);
        void initData_resultCPU_opt(unsigned int SIZE_N);
        void initData_resultDevice(unsigned int SIZE_N);
        
        string printData_A();
        string printData_B();
        string printData_resultCPU();
        string printData_resultCPU_opt();
        string printData_resultDevice();
        string printAll();

        void kernel_jacobi_2d_CPU();
        void kernel_jacobi_2d_CPU_opt();
        void saveResults();
        void saveResults_opt();



        //*************************
        //* GET AND SET FUNCTIONS *
        //*************************
        unsigned int get_SIZE_N();
        void set_SIZE_N(unsigned int data);

        unsigned int get_STEPS();
        void set_STEPS(unsigned int data);

        vector< vector<typeData>>& get_A();
        void set_A(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_B();
        void set_B(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_resultCPU();
        void set_resultCPU(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_resultCPU_opt();
        void set_resultCPU_opt(vector< vector<typeData>> newList);

        vector< vector<typeData>>& get_resultDevice();
        void set_resultDevice(vector< vector<typeData>> newList);
};

#endif
