#ifndef _STUDYCASE2HOST_B_HPP_
#define _STUDYCASE2HOST_B_HPP_

#include <iostream>
#include <atomic>

#include "../../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../../utilities/event_timer/event_timer.hpp"
#include "../../../utilities/xilinx_ocl_helper/xilinx_ocl_helper.hpp"
#include "../../../configParams/configParams.hpp"
#include "../../../kernel/studyCase2Kernel/studyCase2Kernel.hpp"

using globalConfiguration_typeData::typeData;

class StudyCase2Host_b {


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
        StudyCase2Host_b();
        ~StudyCase2Host_b();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:
        static bool initParameter(Execution exec, unsigned int &SIZE);

        static float searchPropertyValue(const string& texto, const string& subcadena);
        static void threadFunction_DevicePowerMeasure();
        static double executeAndMeasure_CPU(StudyCase2Kernel& data, EventTimer &event);
        static double executeAndMeasure_CPUopt(StudyCase2Kernel& data, vector<double> &measureByPack, EventTimer &event);

        static void ensamble_dataToBuffers(StudyCase2Kernel& data, typeData *temp_A, typeData *temp_B, typeData *temp_resultDevice);
        static void ensamble_buffersToData(StudyCase2Kernel& data, typeData *temp_resultDevice);
        static bool compareResults(StudyCase2Kernel& data);
 
};
#endif