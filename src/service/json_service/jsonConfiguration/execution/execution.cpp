#include <iostream>
#include "execution.hpp"


//*******************************
// CONSTRUCTORS DEFINITION ZONE *
//*******************************
Execution::Execution():
    host(""),
    kernelPackage(""),
    kernel(""),
    measurePower_CPU(false),
    measurePower_CPUopt(false),
    measurePower_device(false),
    printResults(false),
    numExecutions_cool(0),
    numExecutions_hot(0)
{}
Execution::Execution(string host, string kernelPackage, string kernel, bool measurePower_CPU, bool measurePower_CPUopt, bool measurePower_device, bool printResults, unsigned int numExecutions_cool, unsigned int numExecutions_hot):
    host(host),
    kernelPackage(kernelPackage),
    kernel(kernel),
    measurePower_CPU(measurePower_CPU),
    measurePower_CPUopt(measurePower_CPUopt),
    measurePower_device(measurePower_device),
    printResults(printResults),
    numExecutions_cool(numExecutions_cool),
    numExecutions_hot(numExecutions_hot)
{}
Execution::~Execution(){}



//************************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES *
//************************************
string Execution::displayInfo(string initLineString){
    string info = initLineString + "{\n";
    info += initLineString + "Host: " + get_host() + "\n";
    info += initLineString + "Kernel Package: " + get_kernelPackage() + "\n";
    info += initLineString + "Kernel: " + get_kernel() + "\n";
    info += initLineString + "Data Size: " + get_dataSize() + "\n";
    info += initLineString + "Measure power CPU?: " + (get_measurePower_CPU()? "true":"false") + "\n";
    info += initLineString + "Measure power CPU opt?: " + (get_measurePower_CPUopt()? "true":"false") + "\n";
    info += initLineString + "Measure power device?: " + (get_measurePower_device()? "true":"false") + "\n";
    info += initLineString + "Print Results?: " + (get_printResults()? "true":"false") + "\n";
    info += initLineString + "Number of Cool Executions: " + to_string(get_numExecutions_cool()) + "\n";
    info += initLineString + "Number of Hot Executions: " + to_string(get_numExecutions_hot()) + "\n";
    info += initLineString + "}\n";
    return info;
}



//*************************
//* GET AND SET FUNCTIONS *
//*************************
string Execution::get_host() const{ return host; }
void Execution::set_host(string data){ host=data; }

string Execution::get_kernelPackage() const{ return kernelPackage; }
void Execution::set_kernelPackage(string data){ kernelPackage=data; }

string Execution::get_kernel() const{ return kernel; }
void Execution::set_kernel(string data){ kernel=data; }

string Execution::get_dataSize() const{ return dataSize; }
void Execution::set_dataSize(string data){ dataSize=data; }

bool Execution::get_measurePower_CPU() const{ return measurePower_CPU; }
void Execution::set_measurePower_CPU(bool data){ measurePower_CPU=data; }

bool Execution::get_measurePower_CPUopt() const{ return measurePower_CPUopt; }
void Execution::set_measurePower_CPUopt(bool data){ measurePower_CPUopt=data; }
        
bool Execution::get_measurePower_device() const{ return measurePower_device; }
void Execution::set_measurePower_device(bool data){ measurePower_device=data; }

bool Execution::get_printResults() const{ return printResults; }
void Execution::set_printResults(bool data){ printResults = data; }

unsigned int Execution::get_numExecutions_cool() const{ return numExecutions_cool; }
void Execution::set_numExecutions_cool(unsigned int data){ numExecutions_cool=data; }
        
unsigned int Execution::get_numExecutions_hot() const{ return numExecutions_hot; }
void Execution::set_numExecutions_hot(unsigned int data){ numExecutions_hot=data; }