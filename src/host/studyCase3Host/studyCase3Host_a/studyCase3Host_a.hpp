#ifndef _STUDYCASE3HOST_A_HPP_
#define _STUDYCASE3HOST_A_HPP_

#include <iostream>
#include <atomic>

#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../configParams/configParams.hpp"
#include "../../../kernel/studyCase3Kernel/studyCase3Kernel.hpp"

using globalConfiguration_typeData::typeData;
using globalConfiguration_typeData::typeData_fixed;

class StudyCase3Host_a {


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
        StudyCase3Host_a();
        ~StudyCase3Host_a();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(StudyCase3Kernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(StudyCase3Kernel& data, vector<double> &measureByPack, EventTimer &event);

        static void ensamble_dataToBuffers(StudyCase3Kernel& data, typeData_fixed *temp_A, typeData_fixed *temp_B, typeData_fixed *temp_resultDevice);
        static void ensamble_buffersToData(StudyCase3Kernel& data, typeData_fixed *temp_resultDevice);
        static bool compareResults(StudyCase3Kernel& data);

};
#endif