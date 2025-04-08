#include <iostream>
#include <iomanip>
#include <math.h>
#include "doitgenKernel.hpp"

using globalConfiguration_typeData::typeData;
using namespace std;

//********************************
//* CONSTRUCTORS AND DESTRUCTORS *
//********************************
DoitgenKernel::DoitgenKernel(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P):
    SIZE_R(SIZE_R),
    SIZE_Q(SIZE_Q),
    SIZE_P(SIZE_P),
    A(vector< vector< vector<typeData>>>()),
    C4(vector< vector<typeData>>()),
    resultCPU(vector< vector< vector<typeData>>>()),
    resultCPU_opt(vector< vector< vector<typeData>>>()),
    resultDevice(vector< vector< vector<typeData>>>())
{
    initData_A(SIZE_R, SIZE_Q, SIZE_P);
    initData_C4(SIZE_P);
    initData_resultCPU(SIZE_R, SIZE_Q, SIZE_P);
    initData_resultCPU_opt(SIZE_R, SIZE_Q, SIZE_P);
    initData_resultDevice(SIZE_R, SIZE_Q, SIZE_P);
}
DoitgenKernel::~DoitgenKernel(){}



//*********************
//* GENERAL FUNCTIONS *
//*********************
void DoitgenKernel::initData_A(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P){
    for (int r = 0; r < SIZE_R; r++) {
        get_A().push_back(vector< vector<typeData>>());
        for (int q = 0; q < SIZE_Q; q++) {
            get_A()[r].push_back(vector<typeData>());
            for (int p = 0; p < SIZE_P; p++){
                #if defined(TYPEDATA_INT)
                    get_A()[r][q].push_back(  ((typeData) (  ((double) (((r*q + p)%SIZE_P)) * 10 ) / SIZE_P)) );
                #elif defined(TYPEDATA_FP)
                    get_A()[r][q].push_back((typeData) ((r*q + p)%SIZE_P) / SIZE_P);
                #else
                    get_A()[r][q].push_back((typeData) ((r*q + p)%SIZE_P) / SIZE_P);
                #endif
            }
        }
    }
    return;
}


void DoitgenKernel::initData_C4(unsigned int SIZE_P){
    for (int p1 = 0; p1 < SIZE_P; p1++) {
        get_C4().push_back(vector<typeData>());
        for (int p2 = 0; p2 < SIZE_P; p2++) {
            #if defined(TYPEDATA_INT)
                get_C4()[p1].push_back( (typeData) floor(((p1*p2 % SIZE_P) / SIZE_P) *10) );
            #elif defined(TYPEDATA_FP)
                get_C4()[p1].push_back((typeData) (p1*p2 % SIZE_P) / SIZE_P);
            #else
                get_C4()[p1].push_back((typeData) (p1*p2 % SIZE_P) / SIZE_P);
            #endif
        }
    }
    return;
}


void DoitgenKernel::initData_resultCPU(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P){
    for (int r = 0; r < SIZE_R; r++) {
        get_resultCPU().push_back(vector< vector<typeData>>());
        for (int q = 0; q < SIZE_Q; q++) {
            get_resultCPU()[r].push_back(vector<typeData>());
            for (int p = 0; p < SIZE_P; p++){
                #if defined(TYPEDATA_INT)
                    get_resultCPU()[r][q].push_back(0);
                #elif defined(TYPEDATA_FP)
                    get_resultCPU()[r][q].push_back(0.0);
                #else
                    get_resultCPU()[r][q].push_back(0.0);
                #endif
            }
        }
    }
    return;
}

void DoitgenKernel::initData_resultCPU_opt(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P){
    for (int r = 0; r < SIZE_R; r++) {
        get_resultCPU_opt().push_back(vector< vector<typeData>>());
        for (int q = 0; q < SIZE_Q; q++) {
            get_resultCPU_opt()[r].push_back(vector<typeData>());
            for (int p = 0; p < SIZE_P; p++){
                #if defined(TYPEDATA_INT)
                    get_resultCPU_opt()[r][q].push_back(0);
                #elif defined(TYPEDATA_FP)
                    get_resultCPU_opt()[r][q].push_back(0.0);
                #else
                    get_resultCPU_opt()[r][q].push_back(0.0);
                #endif
            }
        }
    }
    return;
}


void DoitgenKernel::initData_resultDevice(unsigned int SIZE_R, unsigned int SIZE_Q, unsigned int SIZE_P){
    for (int r = 0; r < SIZE_R; r++) {
        get_resultDevice().push_back(vector< vector<typeData>>());
        for (int q = 0; q < SIZE_Q; q++) {
            get_resultDevice()[r].push_back(vector<typeData>());
            for (int p = 0; p < SIZE_P; p++){
                #if defined(TYPEDATA_INT)
                    get_resultDevice()[r][q].push_back(0);
                #elif defined(TYPEDATA_FP)
                    get_resultDevice()[r][q].push_back(0.0);
                #else
                    get_resultDevice()[r][q].push_back(0.0);
                #endif
            }
        }
    }
    return;
}



string DoitgenKernel::printData_A(){
    string result="";
    for (int r = 0; r < get_A().size(); r++) {
        result += "\nARRAY A, DIMENSION R=" + to_string(r+1) + " of " + to_string(get_A().size()) + "\n";
        for (int q = 0; q < get_A()[0].size(); q++) {
            for (int p = 0; p < get_A()[0][0].size(); p++) {
                #if defined(TYPEDATA_INT)
                    result += std::to_string(A[r][q][p]) + "  ";
                #elif defined(TYPEDATA_FP)
                    result += std::to_string(A[r][q][p]) + "  ";
                #else
                    result += std::to_string(A[r][q][p]) + "  ";
                #endif
            }
            result += "\n";
        }
        result += "\n";
    }
    return result;
}


string DoitgenKernel::printData_C4(){
    string result="";
    for (int p1 = 0; p1 < get_C4().size(); p1++) {
        for (int p2 = 0; p2 < get_C4()[0].size(); p2++) {
            #if defined(TYPEDATA_INT)
                result += to_string(C4[p1][p2]) + "  ";
            #elif defined(TYPEDATA_FP)
                result += to_string(C4[p1][p2]) + "  ";
            #else
                result += to_string(C4[p1][p2]) + "  ";
            #endif
        }
        result += "\n";
    }
    result += "\n";
    return result;
}


string DoitgenKernel::printData_resultCPU(){
    string result="";
    for (int r = 0; r < get_resultCPU().size(); r++) {
        result += "\nARRAY RESULTCPU, DIMENSION R=" + to_string(r+1) + " of " + to_string(get_A().size()) + "\n";
        for (int q = 0; q < get_resultCPU()[0].size(); q++) {
            for (int p = 0; p < get_resultCPU()[0][0].size(); p++) {
                #if defined(TYPEDATA_INT)
                    result += to_string(get_resultCPU()[r][q][p]) + "  ";
                #elif defined(TYPEDATA_FP)
                    result += to_string(get_resultCPU()[r][q][p]) + "  ";
                #else
                    result += to_string(get_resultCPU()[r][q][p]) + "  ";
                #endif
            }
            result += "\n";
        }
        result += "\n";
    }
    return result;
}


string DoitgenKernel::printData_resultCPU_opt(){
    string result="";
    for (int r = 0; r < get_resultCPU_opt().size(); r++) {
        result += "\nARRAY RESULTCPU, DIMENSION R=" + to_string(r+1) + " of " + to_string(get_A().size()) + "\n";
        for (int q = 0; q < get_resultCPU_opt()[0].size(); q++) {
            for (int p = 0; p < get_resultCPU_opt()[0][0].size(); p++) {
                #if defined(TYPEDATA_INT)
                    result += to_string(get_resultCPU_opt()[r][q][p]) + "  ";
                #elif defined(TYPEDATA_FP)
                    result += to_string(get_resultCPU_opt()[r][q][p]) + "  ";
                #else
                    result += to_string(get_resultCPU_opt()[r][q][p]) + "  ";
                #endif
            }
            result += "\n";
        }
        result += "\n";
    }
    return result;
}


string DoitgenKernel::printData_resultDevice(){
    string result="";
    for (int r = 0; r < get_resultDevice().size(); r++) {
        result += "\nARRAY RESULTDEVICE, DIMENSION R=" + to_string(r+1) + " of " + to_string(get_A().size()) + "\n";
        for (int q = 0; q < get_resultDevice()[0].size(); q++) {
            for (int p = 0; p < get_resultDevice()[0][0].size(); p++) {
                #if defined(TYPEDATA_INT)
                    result += to_string(resultDevice[r][q][p]) + "  ";
                #elif defined(TYPEDATA_FP)
                    result += to_string(resultDevice[r][q][p]) + "  ";
                #else
                    result += to_string(resultDevice[r][q][p]) + "  ";
                #endif
            }
            result += "\n";
        }
        result += "\n";
    }
    return result;
}


string DoitgenKernel::printAll(){
    string result="";
    result += "RESULTS ARRAY A\n";
    result += "=====================\n";
    result += printData_A() + "\n";

    result += "RESULTS ARRAY C4\n";
    result += "=====================\n";
    result += printData_C4() + "\n";

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



void DoitgenKernel::kernel_doitgen_CPU(){

    vector<typeData> sum = vector<typeData>(get_SIZE_P(), 0.0);

    for (int r = 0; r < get_SIZE_R(); r++){
      for (int q = 0; q < get_SIZE_Q(); q++){
        for (int p = 0; p < get_SIZE_P(); p++){
            sum[p]=0.0; 
            for (int s = 0; s < get_SIZE_P(); s++){
                sum[p] += get_A()[r][q][s] * get_C4()[s][p];
            }   
        }

        for (int p = 0; p < get_SIZE_P(); p++){
            get_resultCPU()[r][q][p] = sum[p];
        }
      }
    }

  return;
}


void DoitgenKernel::kernel_doitgen_CPU_opt() {
    const auto& A = get_A();
    const auto& C4 = get_C4();
    const unsigned int SIZE_R = get_SIZE_R();
    const unsigned int SIZE_Q = get_SIZE_Q();
    const unsigned int SIZE_P = get_SIZE_P();
    auto& resultCPU_opt = get_resultCPU_opt();
    vector<typeData> sum(get_SIZE_P(), 0.0);

    #pragma omp parallel for collapse(2) firstprivate(sum) shared(resultCPU_opt)
    for (int r = 0; r < SIZE_R; r++) {
        for (int q = 0; q < SIZE_Q; q++) {
            for (int p = 0; p < SIZE_P; p++) {
                sum[p] = 0.0;
                
                #pragma omp simd
                for (int s = 0; s < SIZE_P; s++) {
                    sum[p] += A[r][q][s] * C4[s][p];
                }
            }

            for (int p = 0; p < SIZE_P; p++) {
                #pragma omp atomic write
                    resultCPU_opt[r][q][p] = sum[p];
            }
        }
    }
}




//*************************
//* GET AND SET FUNCTIONS *
//*************************
unsigned int DoitgenKernel::get_SIZE_R(){ return SIZE_R; }
void DoitgenKernel::set_SIZE_R(unsigned int data){ SIZE_R=data; }

unsigned int DoitgenKernel::get_SIZE_Q(){ return SIZE_Q; }
void DoitgenKernel::set_SIZE_Q(unsigned int data){ SIZE_Q=data; }

unsigned int DoitgenKernel::get_SIZE_P(){ return SIZE_P; }
void DoitgenKernel::set_SIZE_P(unsigned int data){ SIZE_P=data; }


vector< vector< vector<typeData>>>& DoitgenKernel::get_A(){ 
    return A; 
}
typeData DoitgenKernel::getElement_A_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP){
    return get_A()[indexR][indexQ][indexP];
}
void DoitgenKernel::set_A(vector< vector< vector<typeData>>> newList){
    get_A().clear();
    for (int r=0 ; r<newList.size() ; r++) {
        get_A().push_back(vector< vector<typeData>>());
        for (int q=0 ; q<newList.size() ; q++) {
            get_A()[r].push_back(vector<typeData>());
            for (int p=0 ; p<newList.size() ; p++) {
                get_A()[r][q].push_back(newList[r][q][p]);
            }
        }
    }
}
void DoitgenKernel::setElement_A_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value){
    get_A()[indexR][indexQ][indexP]=value;
}



vector< vector<typeData>>& DoitgenKernel::get_C4(){
    return C4;
}
typeData DoitgenKernel::getElement_C4_byIndex(unsigned int indexP1, unsigned int indexP2){
    return get_C4()[indexP1][indexP2];
}
void DoitgenKernel::set_C4(vector< vector<typeData>> newList){
    get_C4().clear();
    for (int p1=0 ; p1<newList.size() ; p1++) {
        get_C4().push_back(vector<typeData>());
        for (int p2=0 ; p2<newList.size() ; p2++) {
            get_C4()[p1].push_back(newList[p1][p2]);
        }
    } 
}
void DoitgenKernel::setElement_C4_byIndex(unsigned int indexP1, unsigned int indexP2, typeData value){
    get_C4()[indexP1][indexP2];
}



vector< vector< vector<typeData>>>& DoitgenKernel::get_resultCPU(){
    return resultCPU;
}
typeData DoitgenKernel::getElement_resultCPU_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP){
    return get_resultCPU()[indexR][indexQ][indexP];
}
void DoitgenKernel::set_resultCPU(vector< vector< vector<typeData>>> newList){
    get_resultCPU().clear();
    for (int r=0 ; r<newList.size() ; r++) {
        get_resultCPU().push_back(vector< vector<typeData>>());
        for (int q=0 ; q<newList.size() ; q++) {
            get_resultCPU()[r].push_back(vector<typeData>());
            for (int p=0 ; p<newList.size() ; p++) {
                get_resultCPU()[r][q].push_back(newList[r][q][p]);
            }
        }
    }
}
void DoitgenKernel::setElement_resultCPU_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value){
    get_resultCPU()[indexR][indexQ][indexP]=value;
}



vector< vector< vector<typeData>>>& DoitgenKernel::get_resultCPU_opt(){
    return resultCPU_opt;
}
typeData DoitgenKernel::getElement_resultCPU_opt_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP){
    return get_resultCPU_opt()[indexR][indexQ][indexP];
}
void DoitgenKernel::set_resultCPU_opt(vector< vector< vector<typeData>>> newList){
    get_resultCPU_opt().clear();
    for (int r=0 ; r<newList.size() ; r++) {
        get_resultCPU_opt().push_back(vector< vector<typeData>>());
        for (int q=0 ; q<newList.size() ; q++) {
            get_resultCPU_opt()[r].push_back(vector<typeData>());
            for (int p=0 ; p<newList.size() ; p++) {
                get_resultCPU_opt()[r][q].push_back(newList[r][q][p]);
            }
        }
    }
}
void DoitgenKernel::setElement_resultCPU_opt_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value){
    get_resultCPU_opt()[indexR][indexQ][indexP]=value;
}



vector< vector< vector<typeData>>>& DoitgenKernel::get_resultDevice(){
    return resultDevice;
}
typeData DoitgenKernel::getElement_resultDevice_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP){
    return get_resultDevice()[indexR][indexQ][indexP];
}
void DoitgenKernel::set_resultDevice(vector< vector< vector<typeData>>> newList){
    get_resultDevice().clear();
    for (int r=0 ; r<newList.size() ; r++) {
        get_resultDevice().push_back(vector< vector<typeData>>());
        for (int q=0 ; q<newList.size() ; q++) {
            get_resultDevice()[r].push_back(vector<typeData>());
            for (int p=0 ; p<newList.size() ; p++) {
                get_resultDevice()[r][q].push_back(newList[r][q][p]);
            }
        }
    }
}
void DoitgenKernel::setElement_resultDevice_byIndex(unsigned int indexR, unsigned int indexQ, unsigned int indexP, typeData value){
    get_resultDevice()[indexR][indexQ][indexP]=value;
}
