#ifndef _GEMMPERHOST_OPT1_HPP_
#define _GEMMPERHOST_OPT1_HPP_

#include <iostream>
#include <atomic>
#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../kernel/gemmPerKernel/gemmPerKernel.hpp"
#include "../../../configParams/configParams.hpp"

using globalConfiguration_typeData::typeData;

class GemmPerHost_Opt1 {


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
        GemmPerHost_Opt1();
        ~GemmPerHost_Opt1();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
         
        static bool initParameter(Execution exec, unsigned int &SIZE_I, unsigned int &SIZE_J, unsigned int &SIZE_K);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(GemmPerKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(GemmPerKernel& data, vector<double> &measureByPack, EventTimer &event);

        static void emsamble_dataToBuffers(GemmPerKernel& data, vector<typeData> &temp_A, vector<typeData>& temp_B, vector<typeData>& temp_C, vector<typeData>& temp_resultDevice);
        static void emsamble_buffersToData(GemmPerKernel& data, vector<typeData>& temp_resultDevice);
        static bool compareResults(GemmPerKernel& data);
};
#endif