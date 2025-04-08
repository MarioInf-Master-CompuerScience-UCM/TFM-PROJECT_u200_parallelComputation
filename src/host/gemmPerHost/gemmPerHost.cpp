#include "gemmPerHost.hpp"

using namespace std;

GemmPerHost::GemmPerHost(){};
GemmPerHost::~GemmPerHost(){};



bool GemmPerHost::exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile){

    bool result = false;
    string hostName = exec.get_host();
    for (char& c : hostName) {
        c = tolower(c);
    } 

    if(hostName == Helper::getNameOfType(typeid(GemmPerHost_Opt0).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(GemmPerHost_Opt0).name()) + "host version");
        result = GemmPerHost_Opt0::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else if(hostName == Helper::getNameOfType(typeid(GemmPerHost_Opt1).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(GemmPerHost_Opt1).name()) + "host version");
        result = GemmPerHost_Opt1::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else if(hostName == Helper::getNameOfType(typeid(GemmPerHost_Opt2).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(GemmPerHost_Opt2).name()) + "host version");
        result = GemmPerHost_Opt2::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else if(hostName == Helper::getNameOfType(typeid(GemmPerHost_Opt3).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(GemmPerHost_Opt3).name()) + "host version");
        result = GemmPerHost_Opt3::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else if(hostName == Helper::getNameOfType(typeid(GemmPerHost_Opt4).name())){
        fileWriter_logFile.writeln("KernelPackage selected matches with " + Helper::getNameOfType(typeid(GemmPerHost_Opt4).name()) + "host version");
        result = GemmPerHost_Opt4::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_statsFile);

    }else{
        fileWriter_logFile.writeln("ERROR..: GemmPerHost host name unknow (" + hostName + ").");
        return false;
    }

    return result;
}
