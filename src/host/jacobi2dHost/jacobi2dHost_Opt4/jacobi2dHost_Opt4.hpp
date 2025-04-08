#ifndef _JACOBI2DHOST_OPT4_HPP_
#define _JACOBI2DHOST_OPT4_HPP_

#include <iostream>

#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../configParams/configParams.hpp"
#include "../../../kernel/jacobi_2dKernel/jacobi_2dKernel.hpp"

using globalConfiguration_typeData::typeData;
using globalConfiguration_typeData::typeData_fixed;

class Jacobi2dHost_Opt4 {


    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        static atomic<bool> stop_thread;
        static double sharedVariable;


    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:
        Jacobi2dHost_Opt4();
        ~Jacobi2dHost_Opt4();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &STEPS, unsigned int &SIZE_N);

        static void ensamble_dataToBuffers(Jacobi_2dKernel& data, typeData_fixed *temp_A, typeData_fixed *temp_B);
        static void ensamble_buffersToData(Jacobi_2dKernel& data, typeData_fixed *temp_A, typeData_fixed *temp_B);
        static bool compareResults(Jacobi_2dKernel& data);
 
        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(Jacobi_2dKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(Jacobi_2dKernel& data, vector<double> &measureByPack, EventTimer &event);
 
};
#endif