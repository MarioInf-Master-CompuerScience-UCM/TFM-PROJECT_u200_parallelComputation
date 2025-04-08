#include <iostream>
#include <iomanip>
#include <math.h>
#include "jacobi_2dKernel.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;

//********************************
//* CONSTRUCTORS AND DESTRUCTORS *
//********************************
Jacobi_2dKernel::Jacobi_2dKernel(unsigned int STEPS, unsigned int SIZE_N):
    STEPS(STEPS),
    SIZE_N(SIZE_N),
    A(vector< vector<typeData>>()),
    B(vector< vector<typeData>>()),
    resultCPU(vector< vector<typeData>>()),
    resultCPU_opt(vector< vector<typeData>>()),
    resultDevice(vector< vector<typeData>>())
{
    initData_A(SIZE_N);
    initData_B(SIZE_N);
    initData_resultCPU(SIZE_N);
    initData_resultCPU_opt(SIZE_N);
    initData_resultDevice(SIZE_N);
}
Jacobi_2dKernel::~Jacobi_2dKernel(){}



//*********************
//* GENERAL FUNCTIONS *
//*********************
void Jacobi_2dKernel::initData_A(unsigned int SIZE_N){
    for(int n1=0 ; n1<get_SIZE_N() ; n1++){
        get_A().push_back(vector<typeData>(get_SIZE_N()));
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_A()[n1][n2] = ((typeData) n1*(n2+2) +2) / get_SIZE_N();
        }
    }
    return;
}


void Jacobi_2dKernel::initData_B(unsigned int SIZE_N){
    for(int n1=0 ; n1<get_SIZE_N() ; n1++){
        get_B().push_back(vector<typeData>(get_SIZE_N()));
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_B()[n1][n2] = ((typeData) n1*(n2+3) +3) / get_SIZE_N();
        }
    }
    return;
}


void Jacobi_2dKernel::initData_resultCPU(unsigned int SIZE_N){
    for (int n = 0; n < (get_SIZE_N()*2) ; n++) {
        get_resultCPU().push_back(vector<typeData>(get_SIZE_N(), 0.0f));
    }
    return;
}

void Jacobi_2dKernel::initData_resultCPU_opt(unsigned int SIZE_N){
    for (int n = 0; n < (get_SIZE_N()*2) ; n++) {
        get_resultCPU_opt().push_back(vector<typeData>(get_SIZE_N(), 0.0f));
    }
    return;
}

void Jacobi_2dKernel::initData_resultDevice(unsigned int SIZE_N){
    for (int n = 0; n < (get_SIZE_N()*2) ; n++) {
        get_resultDevice().push_back(vector<typeData>(get_SIZE_N(), 0.0f));
    }
    return;
}



string Jacobi_2dKernel::printData_A(){
    string result="";
    for(int n1=0 ; n1<get_SIZE_N() ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            result += std::to_string(get_A()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string Jacobi_2dKernel::printData_B(){
    string result="";
    for(int n1=0 ; n1<get_SIZE_N() ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            result += std::to_string(get_B()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string Jacobi_2dKernel::printData_resultCPU(){
    string result="";
    for(int n1=0 ; n1<get_resultCPU().size() ; n1++){
        for(int n2=0 ; n2<get_resultCPU()[n1].size() ; n2++){
            result += std::to_string(get_resultCPU()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string Jacobi_2dKernel::printData_resultCPU_opt(){
    string result="";
    for(int n1=0 ; n1<get_resultCPU_opt().size() ; n1++){
        for(int n2=0 ; n2<get_resultCPU_opt()[n1].size() ; n2++){
            result += std::to_string(get_resultCPU_opt()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string Jacobi_2dKernel::printData_resultDevice(){
    string result="";
    for(int n1=0 ; n1<get_resultDevice().size() ; n1++){
        for(int n2=0 ; n2<get_resultDevice()[n1].size() ; n2++){
            result += std::to_string(get_resultDevice()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string Jacobi_2dKernel::printAll(){
    string result="";
    result += "RESULTS ARRAY A\n";
    result += "=====================\n";
    result += printData_A() + "\n";

    result += "RESULTS ARRAY B\n";
    result += "=====================\n";
    result += printData_B() + "\n";

    result += "RESULTS FROM CPU\n";
    result += "=====================\n";
    result += printData_resultCPU() + "\n";

    result += "RESULTS FROM CPU OPTIMIZED\n";
    result += "=====================\n";
    result += printData_resultCPU_opt() + "\n";

    result += "RESULTS FROM DEVICE\n";
    result += "=====================\n";
    result += printData_resultDevice() + "\n";

  return result;
}



void Jacobi_2dKernel::kernel_jacobi_2d_CPU(){

    for (int t=0; t<get_STEPS() ; t++){
        for (int i = 1; i < get_SIZE_N() - 1 ; i++){
            for (int j = 1; j < get_SIZE_N() - 1 ; j++){
                get_B()[i][j] = 0.2 * (get_A()[i][j] + get_A()[i][j-1] + get_A()[i][1+j] + get_A()[1+i][j] + get_A()[i-1][j]);
            }
        }
        for (int i = 1; i < get_SIZE_N() - 1 ; i++){
            for (int j = 1; j < get_SIZE_N() - 1 ; j++){
                get_A()[i][j] = 0.2 * (get_B()[i][j] + get_B()[i][j-1] + get_B()[i][1+j] + get_B()[1+i][j] + get_B()[i-1][j]);
            }
        }
    }

  return;
}


void Jacobi_2dKernel::kernel_jacobi_2d_CPU_opt() {
    const int STEPS = get_STEPS();
    const int SIZE_N = get_SIZE_N();

    for (int t = 0; t < STEPS; t++) {
        #pragma omp parallel for collapse(2) shared(A, B)
        for (int i = 1; i < SIZE_N - 1; i++) {
            for (int j = 1; j < SIZE_N - 1; j++) {
                B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][j + 1] + A[i + 1][j] + A[i - 1][j]);
            }
        }
        #pragma omp parallel for collapse(2) shared(A, B)
        for (int i = 1; i < SIZE_N - 1; i++) {
            for (int j = 1; j < SIZE_N - 1; j++) {
                A[i][j] = 0.2 * (B[i][j] + B[i][j - 1] + B[i][j + 1] + B[i + 1][j] + B[i - 1][j]);
            }
        }
    }
    return;
}


void Jacobi_2dKernel::saveResults(){
    for (int i = 0; i < get_SIZE_N() ; i++){
        for (int j = 0; j < get_SIZE_N() ; j++){
            get_resultCPU()[i][j] = get_B()[i][j];
            get_resultCPU()[get_SIZE_N()+i][j] = get_A()[i][j];
        }
    }
    return;
}


void Jacobi_2dKernel::saveResults_opt(){
    for (int i = 0; i < get_SIZE_N() ; i++){
        for (int j = 0; j < get_SIZE_N() ; j++){
            get_resultCPU_opt()[i][j] = get_B()[i][j];
            get_resultCPU_opt()[get_SIZE_N()+i][j] = get_A()[i][j];
        }
    }
    return;
}



//*************************
//* GET AND SET FUNCTIONS *
//*************************
unsigned int Jacobi_2dKernel::get_SIZE_N(){ return SIZE_N; }
void Jacobi_2dKernel::set_SIZE_N(unsigned int data){ SIZE_N=data; }


unsigned int Jacobi_2dKernel::get_STEPS(){ return STEPS; }
void Jacobi_2dKernel::set_STEPS(unsigned int data){ STEPS=data; }


vector< vector<typeData>>& Jacobi_2dKernel::get_A(){ return A; }
void Jacobi_2dKernel::set_A(vector< vector<typeData>> newList){
    get_A().clear();
    for(int n1=0 ; n1<get_SIZE_N() ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_A()[n1][n2]=newList[n1][n2];
        }
    }
    return;
}


vector< vector<typeData>>& Jacobi_2dKernel::get_B(){ return B; }
void Jacobi_2dKernel::set_B(vector< vector<typeData>> newList){
    get_B().clear();
    for(int n1=0 ; n1<get_SIZE_N() ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_B()[n1][n2]=newList[n1][n2];
        }
    }
    return;
}


vector< vector<typeData>>& Jacobi_2dKernel::get_resultCPU(){ return resultCPU; }
void Jacobi_2dKernel::set_resultCPU(vector< vector<typeData>> newList){
    for(int n1=0 ; n1<get_SIZE_N()*2 ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_resultCPU()[n1][n2]=newList[n1][n2];
        }
    }
    return;
}


vector< vector<typeData>>& Jacobi_2dKernel::get_resultCPU_opt(){ return resultCPU_opt; }
void Jacobi_2dKernel::set_resultCPU_opt(vector< vector<typeData>> newList){
    for(int n1=0 ; n1<get_SIZE_N()*2 ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_resultCPU_opt()[n1][n2]=newList[n1][n2];
        }
    }
    return;
}


vector< vector<typeData>>& Jacobi_2dKernel::get_resultDevice(){ return resultDevice; }
void Jacobi_2dKernel::set_resultDevice(vector< vector<typeData>> newList){
    for(int n1=0 ; n1<get_SIZE_N()*2 ; n1++){
        for(int n2=0 ; n2<get_SIZE_N() ; n2++){
            get_resultDevice()[n1][n2]=newList[n1][n2];
        }
    }
    return;
}