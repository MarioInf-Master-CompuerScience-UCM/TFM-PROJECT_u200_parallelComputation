#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include "vectorAddKernel.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;

//********************************
//* CONSTRUCTORS AND DESTRUCTORS *
//********************************
VectorAddKernel::VectorAddKernel(unsigned int SIZE):
    SIZE(SIZE),
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
VectorAddKernel::~VectorAddKernel(){}



//*********************
//* GENERAL FUNCTIONS *
//*********************
void VectorAddKernel::initData_vA(){
    typeData temp;
    for(int i=0 ; i<get_SIZE() ; i++){
        temp=(i%10);
        temp=temp + (temp/10);
        get_vA().push_back(temp);
    }
    return;
}


void VectorAddKernel::initData_vB(){
    typeData temp;
    for(int i=0 ; i<get_SIZE() ; i++){
        temp=(i%10);
        temp=temp + (temp/10);
        get_vB().push_back( temp );
    }
    return;
}


void VectorAddKernel::initData_resultCPU(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU().push_back(0.0f);
    }
    return;
}

void VectorAddKernel::initData_resultCPU_opt(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU_opt().push_back(0.0f);
    }
    return;
}

void VectorAddKernel::initData_resultDevice(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultDevice().push_back(0.0f);
    }
    return;
}



string VectorAddKernel::printData_vA(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_vA()[i]) + "  ";
    }
    return result;
}


string VectorAddKernel::printData_vB(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_vB()[i]) + "  ";
    }
    return result;
}


string VectorAddKernel::printData_resultCPU(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_resultCPU()[i]) + "  ";
    }
    return result;
}


string VectorAddKernel::printData_resultCPU_opt(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_resultCPU_opt()[i]) + "  ";
    }
    return result;
}


string VectorAddKernel::printData_resultDevice(){
    string result="";
    for(int i=0 ; i<get_SIZE() ; i++){
        result += to_string(get_resultDevice()[i]) + "  ";
    }
    return result;
}


string VectorAddKernel::printAll(){
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



void VectorAddKernel::kernel_vectorAdd_CPU(){
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU()[i] = get_vA()[i] + get_vB()[i];
    }

  return;
}


void VectorAddKernel::kernel_vectorAdd_CPU_opt() {

    #pragma omp parallel for simd
    for(int i=0 ; i<SIZE ; i++){
        resultCPU_opt[i] = vA[i] + vB[i];
    }
    
    return;
}



//*************************
//* GET AND SET FUNCTIONS *
//*************************
unsigned int VectorAddKernel::get_SIZE(){ return SIZE; }
void VectorAddKernel::set_SIZE(unsigned int data){ SIZE=data; }


vector<typeData>& VectorAddKernel::get_vA(){ return vA; }
void VectorAddKernel::set_vA(vector<typeData> newList){
    get_vA().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_vA()[i]=newList[i];
    }
    return;
}


vector<typeData>& VectorAddKernel::get_vB(){ return vB; }
void VectorAddKernel::set_vB(vector<typeData> newList){
    get_vB().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_vB()[i]=newList[i];
    }
    return;
}


vector<typeData>& VectorAddKernel::get_resultCPU(){ return resultCPU; }
void VectorAddKernel::set_resultCPU(vector<typeData> newList){
    get_resultCPU().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU()[i]=newList[i];
    }
    return;
}


vector<typeData>& VectorAddKernel::get_resultCPU_opt(){ return resultCPU_opt; }
void VectorAddKernel::set_resultCPU_opt(vector<typeData> newList){
    get_resultCPU_opt().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultCPU_opt()[i]=newList[i];
    }
    return;
}


vector<typeData>& VectorAddKernel::get_resultDevice(){ return resultDevice; }
void VectorAddKernel::set_resultDevice(vector<typeData> newList){
    get_resultDevice().clear();
    for(int i=0 ; i<get_SIZE() ; i++){
        get_resultDevice()[i]=newList[i];
    }
    return;
}