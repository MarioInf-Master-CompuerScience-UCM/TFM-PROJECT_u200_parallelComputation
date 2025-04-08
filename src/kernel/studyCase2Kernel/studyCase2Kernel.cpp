#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include "studyCase2Kernel.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;

//********************************
//* CONSTRUCTORS AND DESTRUCTORS *
//********************************
StudyCase2Kernel::StudyCase2Kernel(unsigned int SIZE):
    SIZE(SIZE),
    TIMES(3),
    vA(vector<typeData>()),
    vB(vector<typeData>()),
    resultCPU(vector<typeData>()),
    resultCPU_opt(vector<typeData>()),
    resultDevice(vector<typeData>())
{
    initData_vA();
    initData_vB();
    initData_resultCPU();
    initData_resultCPU_opt();
    initData_resultDevice();
}
StudyCase2Kernel::~StudyCase2Kernel(){}



//*********************
//* GENERAL FUNCTIONS *
//*********************
void StudyCase2Kernel::initData_vA(){
    typeData temp;
    for(int i=0 ; i<get_SIZE() ; i++){
        temp=(i%10);
        temp=temp + (temp/10);
        get_vA().push_back(temp);
    }
    return;
}


void StudyCase2Kernel::initData_vB(){
    typeData temp;
    for(int i=0 ; i<get_SIZE() ; i++){
        temp=(i%10);
        temp=temp + (temp/10);
        get_vB().push_back( temp );
    }
    return;
}


void StudyCase2Kernel::initData_resultCPU(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU().push_back(0.0f);
    }
    return;
}

void StudyCase2Kernel::initData_resultCPU_opt(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU_opt().push_back(0.0f);
    }
    return;
}

void StudyCase2Kernel::initData_resultDevice(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultDevice().push_back(0.0f);
    }
    return;
}



string StudyCase2Kernel::printData_vA(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_vA()[i]) + "  ";
    }
    return result;
}


string StudyCase2Kernel::printData_vB(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_vB()[i]) + "  ";
    }
    return result;
}


string StudyCase2Kernel::printData_resultCPU(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_resultCPU()[i]) + "  ";
    }
    return result;
}


string StudyCase2Kernel::printData_resultCPU_opt(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_resultCPU_opt()[i]) + "  ";
    }
    return result;
}


string StudyCase2Kernel::printData_resultDevice(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_resultDevice()[i]) + "  ";
    }
    return result;
}


string StudyCase2Kernel::printAll(){
    string result="";
    result += "RESULTS ARRAY A\n";
    result += "=====================\n";
    result += printData_vA() + "\n\n";

    result += "RESULTS ARRAY B\n";
    result += "=====================\n";
    result += printData_vB() + "\n\n";

    result += "RESULTS FROM CPU\n";
    result += "=====================\n";
    result += printData_resultCPU() + "\n\n";

    result += "RESULTS FROM CPU OPTIMIZED\n";
    result += "=====================\n";
    result += printData_resultCPU_opt() + "\n\n";

    result += "RESULTS FROM DEVICE\n";
    result += "=====================\n";
    result += printData_resultDevice() + "\n\n";

  return result;
}



void StudyCase2Kernel::kernel_studyCase2_a_CPU(){

    for(int time=0 ; time<get_TIMES() ; time++){
        for(int i=0 ; i<get_SIZE() ; i++){
            get_resultCPU()[i] += (get_vA()[i] + get_vB()[i]);
        }
    }

  return;
}


void StudyCase2Kernel::kernel_studyCase2_a_CPU_opt() {

    #pragma omp parallel for simd collapse(2)
    for(int time=0 ; time<TIMES ; time++){
        for(int i=0 ; i<SIZE ; i++){
            resultCPU_opt[i] += (vA[i] + vB[i]);
        }
    }
    
    return;
}



void StudyCase2Kernel::kernel_studyCase2_b_CPU(){

    for(int time=0 ; time<get_TIMES() ; time++){
        for(int i=0 ; i<get_SIZE() ; i++){
            get_resultCPU()[i] += (get_vA()[i] + get_vB()[i]);
        }
    }

  return;
}


void StudyCase2Kernel::kernel_studyCase2_b_CPU_opt() {

    #pragma omp parallel for simd collapse(2)
    for(int time=0 ; time<TIMES ; time++){
        for(int i=0 ; i<SIZE ; i++){
            resultCPU_opt[i] += (vA[i] + vB[i]);
        }
    }
    
    return;
}



void StudyCase2Kernel::kernel_studyCase2_c_CPU(){

    for(int time=0 ; time<get_TIMES() ; time++){
        for(int i=0 ; i<get_SIZE() ; i++){
            get_resultCPU()[i] += (get_vA()[i] + get_vB()[i]);
        }
    }

  return;
}


void StudyCase2Kernel::kernel_studyCase2_c_CPU_opt() {

    #pragma omp parallel for simd collapse(2)
    for(int time=0 ; time<TIMES ; time++){
        for(int i=0 ; i<SIZE ; i++){
            resultCPU_opt[i] += (vA[i] + vB[i]);
        }
    }

    return;
}



void StudyCase2Kernel::kernel_studyCase2_d_CPU(){

    for(int time=0 ; time<get_TIMES() ; time++){
        for(int i=0 ; i<get_SIZE() ; i++){
            get_resultCPU()[i] += (get_vA()[i] + get_vB()[i]);
        }
    }

  return;
}


void StudyCase2Kernel::kernel_studyCase2_d_CPU_opt() {

    #pragma omp parallel for simd collapse(2)
    for(int time=0 ; time<TIMES ; time++){
        for(int i=0 ; i<SIZE ; i++){
            resultCPU_opt[i] += (vA[i] + vB[i]);
        }
    }

    return;
}



//*************************
//* GET AND SET FUNCTIONS *
//*************************
unsigned int StudyCase2Kernel::get_SIZE(){ return SIZE; }
void StudyCase2Kernel::set_SIZE(unsigned int data){ SIZE=data; }

unsigned int StudyCase2Kernel::get_TIMES(){ return TIMES; }
void StudyCase2Kernel::set_TIMES(unsigned int data){ TIMES=data; }


vector<typeData>& StudyCase2Kernel::get_vA(){ return vA; }
void StudyCase2Kernel::set_vA(vector<typeData> newList){
    get_vA().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_vA()[i]=newList[i];
    }
    return;
}


vector<typeData>& StudyCase2Kernel::get_vB(){ return vB; }
void StudyCase2Kernel::set_vB(vector<typeData> newList){
    get_vB().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_vB()[i]=newList[i];
    }
    return;
}


vector<typeData>& StudyCase2Kernel::get_resultCPU(){ return resultCPU; }
void StudyCase2Kernel::set_resultCPU(vector<typeData> newList){
    get_resultCPU().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU()[i]=newList[i];
    }
    return;
}


vector<typeData>& StudyCase2Kernel::get_resultCPU_opt(){ return resultCPU_opt; }
void StudyCase2Kernel::set_resultCPU_opt(vector<typeData> newList){
    get_resultCPU_opt().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU_opt()[i]=newList[i];
    }
    return;
}


vector<typeData>& StudyCase2Kernel::get_resultDevice(){ return resultDevice; }
void StudyCase2Kernel::set_resultDevice(vector<typeData> newList){
    get_resultDevice().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultDevice()[i]=newList[i];
    }
    return;
}