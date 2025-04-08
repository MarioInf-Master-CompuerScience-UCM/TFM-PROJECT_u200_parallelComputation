#ifndef _STUDYCASE3KERNEL_HPP_
#define _STUDYCASE3KERNEL_HPP_

#include <vector>
#include <iostream>
#include "../../configParams/configParams.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;


class StudyCase3Kernel{

    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        unsigned int SIZE;

        vector<typeData> vA;              //SIZE 
        vector<typeData> vB;              //SIZE 
        vector<typeData> resultCPU;       //SIZE
        vector<typeData> resultCPU_opt;   //SIZE
        vector<typeData> resultDevice;    //SIZE



    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:

        //********************************
        //* CONSTRUCTORS AND DESTRUCTORS *
        //********************************
        StudyCase3Kernel(unsigned int SIZE);
        ~StudyCase3Kernel();

        void initData_vA();
        void initData_vB();
        void initData_resultCPU();
        void initData_resultCPU_opt();
        void initData_resultDevice();
        
        string printData_vA();
        string printData_vB();
        string printData_resultCPU();
        string printData_resultCPU_opt();
        string printData_resultDevice();
        string printAll();

        void kernel_studyCase3_a_CPU();
        void kernel_studyCase3_a_CPU_opt();
        void kernel_studyCase3_b_CPU();
        void kernel_studyCase3_b_CPU_opt();
        void kernel_studyCase3_c_CPU();
        void kernel_studyCase3_c_CPU_opt();
        void kernel_studyCase3_d_CPU();
        void kernel_studyCase3_d_CPU_opt();

    private:
        double generateRandomNumber();


    public:
        //*************************
        //* GET AND SET FUNCTIONS *
        //*************************
        unsigned int get_SIZE();
        void set_SIZE(unsigned int data);


        vector<typeData>& get_vA();
        void set_vA(vector<typeData> newList);

        vector<typeData>& get_vB();
        void set_vB(vector<typeData> newList);

        vector<typeData>& get_resultCPU();
        void set_resultCPU(vector<typeData> newList);

        vector<typeData>& get_resultCPU_opt();
        void set_resultCPU_opt(vector<typeData> newList);

        vector<typeData>& get_resultDevice();
        void set_resultDevice(vector<typeData> newList);
};

#endif
