#ifndef _CHOLESKYHOST_OPT0_HPP_
#define _CHOLESKYHOST_OPT0_HPP_

#include <iostream>
#include <atomic>
#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../configParams/configParams.hpp"
#include "../../../kernel/choleskyKernel/choleskyKernel.hpp"

using globalConfiguration_typeData::typeData;

class CholeskyHost_Opt0 {


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
        CholeskyHost_Opt0();
        ~CholeskyHost_Opt0();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE_N);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(CholeskyKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(CholeskyKernel& data, vector<double> &measureByPack, EventTimer &event);

        static void emsamble_dataToBuffers(CholeskyKernel& data, vector<typeData>& temp_A, vector<typeData>& temp_resultDevice);
        static void emsamble_buffersToData(CholeskyKernel& data, vector<typeData>& temp_resultDevice);
        static bool compareResults(CholeskyKernel& data);
 
};
#endif