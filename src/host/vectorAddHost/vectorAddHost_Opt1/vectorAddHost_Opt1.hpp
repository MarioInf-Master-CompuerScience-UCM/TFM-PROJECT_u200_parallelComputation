#ifndef _VECTORADDHOST_OPT1_HPP_
#define _VECTORADDHOST_OPT1_HPP_

#include <iostream>
#include <atomic>

#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../configParams/configParams.hpp"
#include "../../../kernel/vectorAddKernel/vectorAddKernel.hpp"

using globalConfiguration_typeData::typeData;

class VectorAddHost_Opt1 {


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
        VectorAddHost_Opt1();
        ~VectorAddHost_Opt1();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(VectorAddKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(VectorAddKernel& data, vector<double> &measureByPack, EventTimer &event);

        static void ensamble_dataToBuffers(VectorAddKernel& data, vector<typeData> &temp_A, vector<typeData> &temp_B, vector<typeData>& temp_resultDevice);
        static void ensamble_buffersToData(VectorAddKernel& data, vector<typeData>& temp_resultDevice);
        static bool compareResults(VectorAddKernel& data);
 
};
#endif