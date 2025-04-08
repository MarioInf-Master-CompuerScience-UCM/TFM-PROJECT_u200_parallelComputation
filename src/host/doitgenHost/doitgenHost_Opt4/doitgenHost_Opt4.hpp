#ifndef _DOITGENHOST_OPT4_HPP_
#define _DOITGENHOST_OPT4_HPP_

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
using globalConfiguration_typeData::typeData_fixed;


class DoitgenHost_Opt4{


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
        DoitgenHost_Opt4();
        ~DoitgenHost_Opt4();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE_R, unsigned int &SIZE_Q, unsigned int &SIZE_P);

        static void emsamble_dataToBuffers(DoitgenKernel& data, typeData_fixed *temp_A,  typeData_fixed *temp_C4, typeData_fixed *temp_resultDevice);
        static void emsamble_buffersToData(DoitgenKernel& data, typeData_fixed *temp_resultDevice);
        static bool compareResults(DoitgenKernel& data);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(DoitgenKernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(DoitgenKernel& data, vector<double> &measureByPack, EventTimer &event);

};
#endif