#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "jsonConfiguration.hpp"

using namespace std;



//*******************************
// CONSTRUCTORS DEFINITION ZONE *
//*******************************
JsonConfiguration::JsonConfiguration():
    status(true),
    outDir(""),
    logFile(""),
    testList(vector<Test>()
){}
JsonConfiguration::JsonConfiguration(bool status, string outDir, string logFile, vector<Test> testList):
    status(status),
    outDir(outDir),
    logFile(logFile),
    testList(vector<Test>()
){
    set_testList(testList);
}

JsonConfiguration::~JsonConfiguration(){ }



//************************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES *
//************************************
string JsonConfiguration::displayInfo(string initLineString){
    string info = initLineString + "{\n";
    info += initLineString + "Verbose?: " + (get_verbose()? "true":"false") + "\n";
    info += initLineString + "Out Directory: " + get_outDir() + "\n";
    info += initLineString + "Log File: " +get_logFile()+ "\n";
    info += initLineString + "Global performance File: " +get_global_performanceFile()+ "\n";
    info += initLineString + "Global power File: " +get_global_powerFile()+ "\n";
    info += initLineString + "Generate global performance graphics?: " + (get_generate_global_PerformanceGraphics()? "true":"false") + "\n";
    info += initLineString + "Generate global power graphics?: " + (get_generate_global_PowerGraphics()? "true":"false") + "\n";
    info += initLineString + "Test List:\n";
    for (size_t i = 0; i < get_testList().size(); ++i) {
        info += get_testList()[i].displayInfo(initLineString + "\t");
    }
    
    info += initLineString + "}\n";
    return info;
}



//**********************************************************
// ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES *
//**********************************************************
bool JsonConfiguration::get_status() const{ return status; }
void JsonConfiguration::set_status(bool data){ status = data; }

bool JsonConfiguration::get_verbose() const{ return verbose; }
void JsonConfiguration::set_verbose(bool data){ verbose = data; }

string JsonConfiguration::get_outDir() const{ return outDir; }
void JsonConfiguration::set_outDir(string data){ outDir=data; }

string JsonConfiguration::get_logFile() const{ return logFile; }
void JsonConfiguration::set_logFile(string data){ logFile=data; }

string JsonConfiguration::get_global_performanceFile() const{ return global_performanceFile; }
void JsonConfiguration::set_global_performanceFile(string data){ global_performanceFile=data; }

string JsonConfiguration::get_global_powerFile() const{ return global_powerFile; }
void JsonConfiguration::set_global_powerFile(string data){ global_powerFile=data; }

bool JsonConfiguration::get_generate_global_PerformanceGraphics() const{ return generate_global_PerformanceGraphics; }
void JsonConfiguration::set_generate_global_PerformanceGraphics(bool data){ generate_global_PerformanceGraphics=data; }

bool JsonConfiguration::get_generate_global_PowerGraphics() const{ return generate_global_PowerGraphics; }
void JsonConfiguration::set_generate_global_PowerGraphics(bool data){ generate_global_PowerGraphics=data; }

vector<Test>& JsonConfiguration::get_testList(){ return testList; }
void JsonConfiguration::set_testList(vector<Test> newList){
    get_testList().clear();
    for (int i=0 ; i<newList.size() ; i++) {
        get_testList().push_back(newList[i]);
    }
}