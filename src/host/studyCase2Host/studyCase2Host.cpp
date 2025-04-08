#include "studyCase2Host.hpp"

using namespace std;


StudyCase2Host::StudyCase2Host(){};
StudyCase2Host::~StudyCase2Host(){};



bool StudyCase2Host::exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile){

    bool result = false;
    string hostName = exec.get_host();
    for (char& c : hostName) {
        c = tolower(c);
    } 

    if(hostName == Helper::getNameOfType(typeid(StudyCase2Host_a).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(StudyCase2Host_a).name()) + "host version");
        result = StudyCase2Host_a::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

     }else if(hostName == Helper::getNameOfType(typeid(StudyCase2Host_b).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with" + Helper::getNameOfType(typeid(StudyCase2Host_b).name()) + "host version");
        result = StudyCase2Host_b::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);
       
    }else if(hostName == Helper::getNameOfType(typeid(StudyCase2Host_c).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(StudyCase2Host_c).name()) + " host version");
        result = StudyCase2Host_c::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else if(hostName == Helper::getNameOfType(typeid(StudyCase2Host_d).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(StudyCase2Host_d).name()) + " host version");
        result = StudyCase2Host_d::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else{
        fileWriter_logFile.writeln("ERROR..: StudyCase2 host name unknow (" + hostName + ").");
        return false;
    }

    return result;
}
