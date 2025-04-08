#ifndef _DOITGENKERNEL_HPP_
#define _DOITGENKERNEL_HPP_

#include <vector>
#include <iostream>
#include "../../configParams/configParams.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;


class DoitgenKernel{

    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        unsigned int SIZE_R;
        unsigned int SIZE_Q;
        unsigned int SIZE_P;

        vector< vector< vector<typeData>>> A;               //SIZE_R x SIZE_Q x SIZE_P
        vector< vector< typeData>> C4;                      //SIZE_P x SIZE_P
        vector< vector< vector<typeData>>> resultCPU;       //SIZE_R x SIZE_Q x SIZE_P
        vector< vector< vector<typeData>>> resultCPU_opt;   //SIZE_R x SIZE_Q x SIZE_P
        vector< vector< vector<typeData>>> resultDevice;    //SIZE_R x SIZE_Q x SIZE_P



    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:

        //********************************
        //* CONSTRUCTORS AND DESTRUCTORS *
        //********************************
        DoitgenKernel(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P);
        ~DoitgenKernel();

        void initData_A(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P);
        void initData_C4(unsigned int SIZE_P);
        void initData_resultCPU(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P);
        void initData_resultCPU_opt(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P);
        void initData_resultDevice(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P);
        
        string printData_A();
        string printData_C4();
        string printData_resultCPU();
        string printData_resultCPU_opt();
        string printData_resultDevice();
        string printAll();

        void kernel_doitgen_CPU();
        void kernel_doitgen_CPU_opt();



        //*************************
        //* GET AND SET FUNCTIONS *
        //*************************
        unsigned int get_SIZE_R();
        void set_SIZE_R(unsigned int data);

        unsigned int get_SIZE_Q();
        void set_SIZE_Q(unsigned int data);

        unsigned int get_SIZE_P();
        void set_SIZE_P(unsigned int data);


        vector< vector< vector<typeData>>>& get_A();
        typeData getElement_A_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP);
        void set_A(vector< vector< vector<typeData>>> newList);
        void setElement_A_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value);

        vector< vector<typeData>>& get_C4();
        typeData getElement_C4_byIndex(unsigned int indexP1, unsigned int indexP2);
        void set_C4(vector< vector<typeData>> newList);
        void setElement_C4_byIndex(unsigned int indexP1, unsigned int indexP2, typeData value);

        vector< vector< vector<typeData>>>& get_resultCPU();
        typeData getElement_resultCPU_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP);
        void set_resultCPU(vector< vector< vector<typeData>>> newList);
        void setElement_resultCPU_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value);

        vector< vector< vector<typeData>>>& get_resultCPU_opt();
        typeData getElement_resultCPU_opt_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP);
        void set_resultCPU_opt(vector< vector< vector<typeData>>> newList);
        void setElement_resultCPU_opt_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value);

        vector< vector< vector<typeData>>>& get_resultDevice();
        typeData getElement_resultDevice_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP);
        void set_resultDevice(vector< vector< vector<typeData>>> newList);
        void setElement_resultDevice_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value);

        
};

#endif
