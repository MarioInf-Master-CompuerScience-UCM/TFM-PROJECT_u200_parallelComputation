#include <iostream>
#include <iomanip>
#include <cmath> 
#include <omp.h>
#include "gemmKernel.hpp"


using namespace std;

//********************************
//* CONSTRUCTORS AND DESTRUCTORS *
//********************************
GemmKernel::GemmKernel(typeData alpha, typeData beta, unsigned int SIZE_I, unsigned int SIZE_J, unsigned int SIZE_K):
    alpha(alpha),
    beta(beta),
    SIZE_I(SIZE_I),
    SIZE_J(SIZE_J),
    SIZE_K(SIZE_K),
    A(vector< vector<typeData>>()),
    B(vector< vector<typeData>>()),
    C(vector< vector<typeData>>()),
    resultCPU(vector< vector<typeData>>()),
    resultCPU_opt(vector< vector<typeData>>()),
    resultDevice(vector< vector<typeData>>())
{
    initData_A();
    initData_B();
    initData_C();
    initData_resultCPU();
    initData_resultCPU_opt();
    initData_resultDevice();
}
GemmKernel::~GemmKernel(){}



//*********************
//* GENERAL FUNCTIONS *
//*********************
void GemmKernel::initData_A(){
    for (int i=0; i<get_SIZE_I(); i++) {
        get_A().push_back(vector<typeData>(get_SIZE_K(), 0.0f));
        for (int k=0; k<get_SIZE_K(); k++){
            get_A()[i][k] = (typeData)(i*(k+1) % get_SIZE_K()) / get_SIZE_K();
        }
    }
    return;
}


void GemmKernel::initData_B(){
    for (int k=0; k<get_SIZE_K(); k++) {
        get_B().push_back(vector<typeData>(get_SIZE_J(), 0.0f));
        for (int j=0; j<get_SIZE_J(); j++){
            get_B()[k][j] = (typeData)(k*(j+2) % get_SIZE_J()) / get_SIZE_J();
        }
    }
    return;
}


void GemmKernel::initData_C(){
    for (int i=0; i<get_SIZE_I(); i++) {
        get_C().push_back(vector<typeData>(get_SIZE_J(), 0.0f));
        for (int j=0; j<get_SIZE_J(); j++){
            get_C()[i][j] = (typeData)((i*j+1) % get_SIZE_I()) / get_SIZE_I();
        }
    }
    return;
}


void GemmKernel::initData_resultCPU(){
    for (int n1 = 0; n1 < get_SIZE_I(); n1++) {
        get_resultCPU().push_back(vector<typeData>(get_SIZE_J(), 0.0f));
    }
    return;
}


void GemmKernel::initData_resultCPU_opt(){
    for (int n1 = 0; n1 < get_SIZE_I(); n1++) {
        get_resultCPU_opt().push_back(vector<typeData>(get_SIZE_J(), 0.0f));
    }
    return;
}


void GemmKernel::initData_resultDevice(){
    for (int n1 = 0; n1 < get_SIZE_I(); n1++) {
        get_resultDevice().push_back(vector<typeData>(get_SIZE_J(), 0.0f));
    }
    return;
}


string GemmKernel::printData_A(){
    string result="";
    for (int n1 = 0; n1 < get_A().size(); n1++) {
        for (int n2 = 0; n2 < get_A()[n1].size(); n2++){
            result += to_string(get_A()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string GemmKernel::printData_B(){
    string result="";
    for (int n1 = 0; n1 < get_B().size(); n1++) {
        for (int n2 = 0; n2 < get_B()[n1].size(); n2++){
            result += to_string(get_B()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string GemmKernel::printData_C(){
    string result="";
    for (int n1 = 0; n1 < get_C().size(); n1++) {
        for (int n2 = 0; n2 < get_C()[n1].size(); n2++){
            result += to_string(get_C()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string GemmKernel::printData_resultCPU(){
    string result="";
    for (int n1 = 0; n1 < get_resultCPU().size(); n1++) {
        for (int n2 = 0; n2 < get_resultCPU()[n1].size(); n2++){
            result += to_string(get_resultCPU()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string GemmKernel::printData_resultCPU_opt(){
    string result="";
    for (int n1 = 0; n1 < get_resultCPU_opt().size(); n1++) {
        for (int n2 = 0; n2 < get_resultCPU_opt()[n1].size(); n2++){
            result += to_string(get_resultCPU_opt()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string GemmKernel::printData_resultDevice(){
    string result="";
    for (int n1 = 0; n1 < get_resultDevice().size(); n1++) {
        for (int n2 = 0; n2 < get_resultDevice()[n1].size(); n2++){
            result += to_string(get_resultDevice()[n1][n2]) + "  ";
        }
        result += "\n";
    }
    return result;
}


string GemmKernel::printAll(){
    string result="";
    result += "RESULTS ARRAY A\n";
    result += "=====================\n";
    result += printData_A() + "\n";

    result += "RESULTS ARRAY B\n";
    result += "=====================\n";
    result += printData_B() + "\n";

    result += "RESULTS ARRAY C\n";
    result += "=====================\n";
    result += printData_C() + "\n";

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



void GemmKernel::kernel_gemm_CPU(){
    for (int i=0 ; i<get_SIZE_I() ; i++){
        for (int j=0; j<get_SIZE_J(); j++){
            get_resultCPU()[i][j] = get_C()[i][j] * get_beta();
            for (int k=0; k< get_SIZE_K(); k++){
                get_resultCPU()[i][j] += get_alpha() * get_A()[i][k] * get_B()[k][j];
            }
        }
    }
  return;
}


void GemmKernel::kernel_gemm_CPU_opt() {
    int SIZE_I = get_SIZE_I();
    int SIZE_J = get_SIZE_J();
    int SIZE_K = get_SIZE_K();
    double beta = get_beta();
    double alpha = get_alpha();
    auto& result = get_resultCPU_opt();
    auto C = get_C();
    auto A = get_A();
    auto B = get_B();
    
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < SIZE_I; i++) {
        for (int j = 0; j < SIZE_J; j++) {
            get_resultCPU_opt()[i][j] = C[i][j] * beta;
            for (int k = 0; k < SIZE_K; k++) {
                get_resultCPU_opt()[i][j] += alpha * A[i][k] * B[k][j];
            }
        }
    }
    return;
}



//*************************
//* GET AND SET FUNCTIONS *
//*************************
unsigned int GemmKernel::get_SIZE_I(){ return SIZE_I; }
void GemmKernel::set_SIZE_I(unsigned int data){ SIZE_I=data; }

unsigned int GemmKernel::get_SIZE_J(){ return SIZE_J; }
void GemmKernel::set_SIZE_J(unsigned int data){ SIZE_J=data; }

unsigned int GemmKernel::get_SIZE_K(){ return SIZE_K; }
void GemmKernel::set_SIZE_K(unsigned int data){ SIZE_K=data; }

typeData GemmKernel::get_alpha(){ return alpha; }
void GemmKernel::set_alpha(typeData data){ alpha=data; }
        
typeData GemmKernel::get_beta(){ return beta; }
void GemmKernel::set_beta(typeData data){ beta=data; }



vector< vector<typeData>>& GemmKernel::get_A(){ 
    return A; 
}
void GemmKernel::set_A(vector< vector<typeData>> newList){
    get_A().clear();
    for (int i=0 ; i<get_SIZE_I() ; i++) {
        get_A().push_back(vector<typeData>());
        for (int k=0 ; k<get_SIZE_K() ; k++) {
            get_A()[i].push_back(newList[i][k]);
        }
    }
}



vector< vector<typeData>>& GemmKernel::get_B(){ 
    return B; 
}
void GemmKernel::set_B(vector< vector<typeData>> newList){
    get_B().clear();
    for (int n1=0 ; n1<get_SIZE_K() ; n1++) {
        get_B().push_back(vector<typeData>());
        for (int n2=0 ; n2<get_SIZE_J() ; n2++) {
            get_B()[n1].push_back(newList[n1][n2]);
        }
    }
}



vector< vector<typeData>>& GemmKernel::get_C(){
    return C;
}
void GemmKernel::set_C(vector< vector<typeData>> newList){
    get_C().clear();
    for (int n1=0 ; n1<get_SIZE_I() ; n1++) {
        get_C().push_back(vector<typeData>());
        for (int n2=0 ; n2<get_SIZE_J() ; n2++) {
            get_C()[n1].push_back(newList[n1][n2]);
        }
    }
}



vector< vector<typeData>>& GemmKernel::get_resultCPU(){
    return resultCPU;
}
void GemmKernel::set_resultCPU(vector< vector<typeData>> newList){
    get_resultCPU().clear();
    for (int n1=0 ; n1<get_SIZE_I() ; n1++) {
        get_resultCPU().push_back(vector<typeData>());
        for (int n2=0 ; n2<get_SIZE_J() ; n2++) {
            get_resultCPU()[n1].push_back(newList[n1][n2]);
        }
    }
}



vector< vector<typeData>>& GemmKernel::get_resultCPU_opt(){
    return resultCPU_opt;
}
void GemmKernel::set_resultCPU_opt(vector< vector<typeData>>newList){
    get_resultCPU_opt().clear();
    for (int n1=0 ; n1<get_SIZE_I() ; n1++) {
        get_resultCPU_opt().push_back(vector<typeData>());
        for (int n2=0 ; n2<get_SIZE_J() ; n2++) {
            get_resultCPU_opt()[n1].push_back(newList[n1][n2]);
        }
    }
}



vector< vector<typeData>>& GemmKernel::get_resultDevice(){
    return resultDevice;
}
void GemmKernel::set_resultDevice(vector< vector<typeData>> newList){
    get_resultDevice().clear();
    for (int n1=0 ; n1<get_SIZE_I() ; n1++) {
        get_resultDevice().push_back(vector<typeData>());
        for (int n2=0 ; n2<get_SIZE_J() ; n2++) {
            get_resultDevice()[n1].push_back(newList[n1][n2]);
        }
    }
}
