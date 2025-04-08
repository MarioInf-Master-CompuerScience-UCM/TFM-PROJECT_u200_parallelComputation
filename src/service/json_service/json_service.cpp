#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <jsoncpp/json/json.h>
#include "json_service.hpp"

using namespace std;
using namespace Json;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Json_service::Json_service(){}
Json_service::Json_service(string jsonFileURL){
    setFileURL(jsonFileURL);
}

Json_service::~Json_service(){ }



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
JsonConfiguration Json_service::getJSONConfiguration_FromFile() {

    JsonConfiguration jsonConfiguration = JsonConfiguration();
     
    ifstream file(getFileURL());
    if (!file.is_open()) {
        cerr << "ERROR..: Couldn't open the configuration Json file (" << getFileURL() << ")"  << endl;
        jsonConfiguration.set_status(false);
        return jsonConfiguration;
    }

    CharReaderBuilder builder;
    Value root;
    CharReader *reader;
    JSONCPP_STRING errs;
    bool result = true;
    
    reader = builder.newCharReader();
    result = parseFromStream(builder, file, &root, &errs);
    if(!result){
        cerr << "ERROR..: Couldn't parse the content of the configuration Json file (" << getFileURL() << ")" << endl ;
        cerr << errs << endl;
        jsonConfiguration.set_status(false);
        return jsonConfiguration;
    }
    file.close();

    jsonConfiguration.set_verbose(root["verbose"].asBool());
    jsonConfiguration.set_logFile(root["logFile"].asString());
    jsonConfiguration.set_outDir(root["outDir"].asString());
    jsonConfiguration.set_global_performanceFile(root["global_performanceFile"].asString());
    jsonConfiguration.set_global_powerFile(root["global_powerFile"].asString());
    jsonConfiguration.set_generate_global_PerformanceGraphics(root["generate_global_PerformanceGraphics"].asBool());
    jsonConfiguration.set_generate_global_PowerGraphics(root["generate_global_PowerGraphics"].asBool());

    Test testTemp;
    Execution executionTemp;
    Value testSelected = Value::null;
    for (const auto &test : root["testList"]) {
        testTemp = Test();
        testTemp.set_name(test["name"].asString());
        testTemp.set_performanceFile(test["performanceFile"].asString());
        testTemp.set_powerFile(test["powerFile"].asString());
        testTemp.set_generate_performanceGraphics(test["generate_performanceGraphics"].asBool());
        testTemp.set_generate_powerGraphics(test["generate_powerGraphics"].asBool());

        for (const auto &execution : test["executionList"]) {
            executionTemp = Execution();
            executionTemp.set_host(execution["host"].asString());
            executionTemp.set_kernelPackage(execution["kernelPackage"].asString());
            executionTemp.set_kernel(execution["kernel"].asString());
            executionTemp.set_dataSize(execution["dataSize"].asString());
            executionTemp.set_measurePower_CPU(execution["measurePower_CPU"].asBool());
            executionTemp.set_measurePower_CPUopt(execution["measurePower_CPUopt"].asBool());
            executionTemp.set_measurePower_device(execution["measurePower_device"].asBool());
            executionTemp.set_printResults(execution["printResults"].asBool());
            executionTemp.set_numExecutions_cool(execution["numExecutions_cool"].asUInt());
            executionTemp.set_numExecutions_hot(execution["numExecutions_hot"].asUInt());
            testTemp.get_executionList().push_back(executionTemp);
        }
        jsonConfiguration.get_testList().push_back(testTemp);        
    }

    return jsonConfiguration;
}


//********************************************************
// ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
//********************************************************
string Json_service::getFileURL(){ return fileURL; }
void Json_service::setFileURL(string data){ fileURL = data; }