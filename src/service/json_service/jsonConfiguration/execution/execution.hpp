#ifndef _EXECUTION_HPP_
#define _EXECUTION_HPP_

#include <string>

using namespace std;

class Execution{

    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        string host;
        string kernelPackage;
        string kernel;
        string dataSize;
        bool measurePower_CPU;
        bool measurePower_CPUopt;
        bool measurePower_device;
        bool printResults;
        unsigned int numExecutions_cool;
        unsigned int numExecutions_hot;


    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:


        //********************************
        //* CONSTRUCTORS AND DESTRUCTORS *
        //********************************
        Execution();
        Execution(string host, string kernelPackage, string kernel, bool measurePower_CPU, bool measurePower_CPUopt, bool measurePower_device, bool printResults, unsigned int numExecutions_cool, unsigned int numExecutions_hot);
        ~Execution();


        string displayInfo(string initLineString="");



        //*************************
        //* GET AND SET FUNCTIONS *
        //*************************
        string get_host() const;
        void set_host(string data);

        string get_kernelPackage() const;
        void set_kernelPackage(string data);

        string get_kernel() const;
        void set_kernel(string data);

        string get_dataSize() const;
        void set_dataSize(string data);

        bool get_measurePower_CPU() const;
        void set_measurePower_CPU(bool data);

        bool get_measurePower_CPUopt() const;
        void set_measurePower_CPUopt(bool data);
        
        bool get_measurePower_device() const;
        void set_measurePower_device(bool data);
        
        bool get_printResults() const;
        void set_printResults(bool data);
        
        unsigned int get_numExecutions_cool() const;
        void set_numExecutions_cool(unsigned int data);
        
        unsigned int get_numExecutions_hot() const;
        void set_numExecutions_hot(unsigned int data);
};

#endif