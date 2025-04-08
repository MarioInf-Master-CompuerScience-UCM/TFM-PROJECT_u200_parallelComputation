#ifndef _GEMMHOST_OPT3_HPP_
#define _GEMMHOST_OPT3_HPP_

#include <iostream>
#include <atomic>
#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../kernel/gemmKernel/gemmKernel.hpp"
#include "../../../configParams/configParams.hpp"

using globalConfiguration_typeData::typeData;

class GemmHost_Opt3 {


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
        GemmHost_Opt3();
        ~GemmHost_Opt3();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE_I, unsigned int &SIZE_J, unsigned int &SIZE_K);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(GemmKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(GemmKernel& data, vector<double> &measureByPack, EventTimer &event);

        static void emsamble_dataToBuffers(GemmKernel& data, typeData *temp_A, typeData *temp_B, typeData *temp_C,typeData *temp_resultDevice);
        static void emsamble_buffersToData(GemmKernel& data, typeData *temp_resultDevice);
        static bool compareResults(GemmKernel& data);
};
#endif