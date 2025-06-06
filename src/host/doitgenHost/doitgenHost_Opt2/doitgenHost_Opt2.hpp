#ifndef _DOITGENHOST_OPT2_HPP_
#define _DOITGENHOST_OPT2_HPP_

#include <iostream>
#include <typeinfo>
#include <atomic>
#include "../../../configParams/configParams.hpp"
#include "../../../kernel/doitgenKernel/doitgenKernel.hpp"
#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"

using globalConfiguration_typeData::typeData;


class DoitgenHost_Opt2{


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
        DoitgenHost_Opt2();
        ~DoitgenHost_Opt2();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE_R, unsigned int &SIZE_Q, unsigned int &SIZE_P);

        static void emsamble_dataToBuffers(DoitgenKernel& data, typeData *temp_A,  typeData *temp_C4, typeData *temp_resultDevice);
        static void emsamble_buffersToData(DoitgenKernel& data, typeData *temp_resultDevice);
        static bool compareResults(DoitgenKernel& data);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(DoitgenKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(DoitgenKernel& data, vector<double> &measureByPack, EventTimer &event);

};
#endif