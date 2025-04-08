#include "studyCase3Host.hpp"

using namespace std;


StudyCase3Host::StudyCase3Host(){};
StudyCase3Host::~StudyCase3Host(){};



bool StudyCase3Host::exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile){

    bool result = false;
    string hostName = exec.get_host();
    for (char& c : hostName) {
        c = tolower(c);
    } 

    if(hostName == Helper::getNameOfType(typeid(StudyCase3Host_a).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(StudyCase3Host_a).name()) + "host version");
        result = StudyCase3Host_a::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

     }else if(hostName == Helper::getNameOfType(typeid(StudyCase3Host_b).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with" + Helper::getNameOfType(typeid(StudyCase3Host_b).name()) + "host version");
        result = StudyCase3Host_b::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);
       
    }else if(hostName == Helper::getNameOfType(typeid(StudyCase3Host_c).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(StudyCase3Host_c).name()) + " host version");
        result = StudyCase3Host_c::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else if(hostName == Helper::getNameOfType(typeid(StudyCase3Host_d).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(StudyCase3Host_d).name()) + " host version");
        result = StudyCase3Host_d::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else{
        fileWriter_logFile.writeln("ERROR..: StudyCase3 host name unknow (" + hostName + ").");
        return false;
    }

    return result;
}
