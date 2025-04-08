#include <iostream>
#include <unistd.h>
#include <cmath>
#include "configParams/configParams.hpp"
#include "host/choleskyHost/choleskyHost.hpp"
#include "host/doitgenHost/doitgenHost.hpp"
#include "host/gemmHost/gemmHost.hpp"
#include "host/gemmPerHost/gemmPerHost.hpp"
#include "host/jacobi2dHost/jacobi2dHost.hpp"
#include "host/vectorAddHost/vectorAddHost.hpp"
#include "host/studyCase1Host/studyCase1Host.hpp"
#include "host/studyCase2Host/studyCase2Host.hpp"
#include "host/studyCase3Host/studyCase3Host.hpp"
#include "utilities/dateAndTime/dateAndTime.hpp"
#include "service/json_service/json_service.hpp"
#include "service/json_service/jsonConfiguration/jsonConfiguration.hpp"
#include "service/externProgramsConnection_service/externProgramsConnection_service.hpp"

bool runExecution(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_performanceFile);
void printFinalMessage(unsigned int numFailures, FileWriter_service fileWriter_logFile);
void printResults(FileWriter_service &fileLog, FileWriter_service &fileStats, vector<double> &resultList, string size);
using namespace std;


//*************************************
// MAIN FUNCTION - START
//*************************************
int main(int argc, char** argv){

    Json_service json_service = Json_service(argv[1]);
    JsonConfiguration jsonConfiguration = json_service.getJSONConfiguration_FromFile();
    if(jsonConfiguration.get_status() == false){
        cerr << "Closing Application..." << endl;
        return 0;
    }

    unsigned int numFailures = 0;
    bool result = false;
    string outFolderID = "/exec_" +DateAndTime::getCurrentDateTime();
    FileWriter_service fileWriter_logFile;
    FileWriter_service fileWriter_performanceFile;
    FileWriter_service fileWriter_powerFile;
    ExternProgramsConnection_service externConnec_performanceGraphics = ExternProgramsConnection_service("generateGaphics_performance.py");
    ExternProgramsConnection_service externConnec_powerGraphics = ExternProgramsConnection_service("generateGaphics_power.py");
    ExternProgramsConnection_service externConnec_performanceTable = ExternProgramsConnection_service("generateTable_performance.py");
    ExternProgramsConnection_service externConnec_powerTable = ExternProgramsConnection_service("generateTable_power.py");
    vector<double> resultsPerformance = vector<double>();
    vector<double> resultsPower = vector<double>();
    vector<double> resultsPerformance_average = vector<double>();
    vector<double> resultsPower_average = vector<double>();

    FileWriter_service fileWriter_global_performanceFile;
    FileWriter_service fileWriter_global_powerFile;
    ExternProgramsConnection_service externConnec_global_performanceGraphics = ExternProgramsConnection_service("generateGaphics_global_performance.py");
    ExternProgramsConnection_service externConnec_global_powerGraphics = ExternProgramsConnection_service("generateGaphics_global_power.py");
    ExternProgramsConnection_service externConnec_global_performanceTable = ExternProgramsConnection_service("generateTable_global_performance.py");
    ExternProgramsConnection_service externConnec_global_powerTable = ExternProgramsConnection_service("generateTable_global_power.py");
    vector<double> resultsGlobal_performance_mini = vector<double>(2, 0.0f);
    vector<double> resultsGlobal_performance_small = vector<double>(2, 0.0f);
    vector<double> resultsGlobal_performance_medium = vector<double>(2, 0.0f);
    vector<double> resultsGlobal_performance_large = vector<double>(2, 0.0f);
    vector<double> resultsGlobal_performance_extralarge = vector<double>(2, 0.0f);
    vector<double> resultsGlobal_power_mini = vector<double>(4, 0.0f);
    vector<double> resultsGlobal_power_small = vector<double>(4, 0.0f);
    vector<double> resultsGlobal_power_medium = vector<double>(4, 0.0f);
    vector<double> resultsGlobal_power_large = vector<double>(4, 0.0f);
    vector<double> resultsGlobal_power_extralarge = vector<double>(4, 0.0f);
    string tempString_toWrite="";

    fileWriter_logFile = FileWriter_service(jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_logFile(), jsonConfiguration.get_verbose());
    fileWriter_logFile.writeln("Contenido del fichero de configuración:");
    fileWriter_logFile.writeln(jsonConfiguration.displayInfo("\t"));

    fileWriter_global_performanceFile = FileWriter_service(jsonConfiguration.get_outDir() + outFolderID + "/" + jsonConfiguration.get_global_performanceFile(), jsonConfiguration.get_verbose());
    fileWriter_global_performanceFile.writeln("X,CPU execution time,CPU optimized execution time,Opt0 execution time,Opt1 execution time,Opt2 execution time,Opt3 execution time,Opt4 execution time", false);

    fileWriter_global_powerFile = FileWriter_service(jsonConfiguration.get_outDir() + outFolderID + "/" + jsonConfiguration.get_global_powerFile(), jsonConfiguration.get_verbose());
    fileWriter_global_powerFile.writeln("X,CPU energy consumption,CPU execution time,CPU optimized energy consumption,CPU optimized execution time,Opt0 energy consumption,Opt0 execution time,Opt1 energy consumption,Opt1 execution time,Opt2 energy consumption,Opt2 execution time,Opt3 energy consumption,Opt3 execution time,Opt4 energy consumption,Opt4 execution time", false);


    for(int i=0 ; i<jsonConfiguration.get_testList().size() ; i++){
        fileWriter_performanceFile = FileWriter_service(jsonConfiguration.get_outDir() + outFolderID + "/" + jsonConfiguration.get_testList()[i].get_performanceFile(), jsonConfiguration.get_verbose());
        fileWriter_performanceFile.writeln("X,CPU execution time,CPU optimized execution time,Device execution time,Transmision (S+R) time,Send to device time,Recieve from device time", false);
    
        fileWriter_powerFile = FileWriter_service(jsonConfiguration.get_outDir() + outFolderID + "/" + jsonConfiguration.get_testList()[i].get_powerFile(), jsonConfiguration.get_verbose());
        fileWriter_powerFile.writeln("X,Device energy consumption,Device execution time,CPU energy consumption,CPU execution time,CPU optimized energy consumption,CPU optimized execution time,CPU-1,CPU-2", false);
    

        for(int j=0 ; j<jsonConfiguration.get_testList()[i].get_executionList().size() ; j++){
            resultsPerformance_average.clear();
            resultsPower_average.clear();

            //Executing cool executions
            for(int k=0 ; k<jsonConfiguration.get_testList()[i].get_executionList()[j].get_numExecutions_cool() ; k++){
                fileWriter_logFile.writeln("\033[1;34m\n*************\n"
                                            "** Running test " + to_string(i+1) + "/" + to_string(jsonConfiguration.get_testList().size()) +
                                            " with execution "+ to_string(j+1) + "/" + to_string(jsonConfiguration.get_testList()[i].get_executionList().size()) +
                                            " and cool repetition "+ to_string(k+1) + "/" + to_string(jsonConfiguration.get_testList()[i].get_executionList()[j].get_numExecutions_cool()) + "\n" +
                                            "*\033[0m", true);
                resultsPerformance.clear();   
                resultsPower.clear();   
                result = runExecution(jsonConfiguration.get_testList()[i].get_executionList()[j], resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);
                fileWriter_logFile.writeln("\033[1;34m\n*\n**\n*************\n\033[0m", true);
            }


            //Executing hot executions            
            for(int k=0 ; k<jsonConfiguration.get_testList()[i].get_executionList()[j].get_numExecutions_hot() ; k++){
                fileWriter_logFile.writeln("\033[1;34m\n*************\n"
                                            "** Running test " + to_string(i+1) + "/" + to_string(jsonConfiguration.get_testList().size()) +
                                            " with execution "+ to_string(j+1) + "/" + to_string(jsonConfiguration.get_testList()[i].get_executionList().size()) +
                                            " and hot repetition "+ to_string(k+1) + "/" + to_string(jsonConfiguration.get_testList()[i].get_executionList()[j].get_numExecutions_hot()) + "\n" +
                                            "*\033[0m", true);
                
                resultsPerformance.clear();
                resultsPower.clear();
                result = runExecution(jsonConfiguration.get_testList()[i].get_executionList()[j], resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);
                if(!result){
                    numFailures++;
                }
                
                for (int execResult=0 ; execResult<resultsPerformance.size() ; execResult++){
                    if((execResult) >= resultsPerformance_average.size()){
                        resultsPerformance_average.push_back(resultsPerformance[execResult]);
                    }else{
                        resultsPerformance_average[execResult] = ( (resultsPerformance_average[execResult]+ resultsPerformance[execResult]) );
                    }
                }

                for (int execResult=0 ; execResult<resultsPower.size() ; execResult++){
                    if((execResult) >= resultsPower_average.size()){
                        resultsPower_average.push_back(resultsPower[execResult]);
                    }else{
                        resultsPower_average[execResult] = ( (resultsPower_average[execResult]+ resultsPower[execResult]) );
                    }
                }

                fileWriter_logFile.writeln("\033[1;34m\n*\n**\n*************\n\033[0m", true);
            }


            //Calculating Performance average results 
            for (int execResult=0 ; execResult<resultsPerformance.size() ; execResult++){
                resultsPerformance_average[execResult] = ( resultsPerformance_average[execResult] / jsonConfiguration.get_testList()[i].get_executionList()[j].get_numExecutions_hot() );
            }
            tempString_toWrite=jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()+",";
            for (int execResult=0 ; execResult<resultsPerformance.size() ; execResult++){
                if(execResult==resultsPerformance.size()-1){
                    tempString_toWrite += to_string(resultsPerformance_average[execResult]);
                }else{
                    tempString_toWrite += to_string(resultsPerformance_average[execResult]) + ",";
                }
            }
            fileWriter_logFile.writeln("\nAverage performance results:\nX,CPU execution time,CPU optimized execution time,Device execution time,Transmision (S+R) time,Send to device time, Recieve from device time", true);
            fileWriter_logFile.writeln(tempString_toWrite, true);  
            fileWriter_performanceFile.writeln(tempString_toWrite, false);


            //Calculating Power average results 
            for (int execResult=0 ; execResult<resultsPower.size() ; execResult++){
                resultsPower_average[execResult] = ( resultsPower_average[execResult] / jsonConfiguration.get_testList()[i].get_executionList()[j].get_numExecutions_hot() );
            }
            tempString_toWrite=jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()+",";
            for (int execResult=0 ; execResult<resultsPower.size() ; execResult++){
                if(execResult==resultsPower.size()-1){
                    tempString_toWrite += to_string(resultsPower_average[execResult]);
                }else{
                    tempString_toWrite += to_string(resultsPower_average[execResult]) + ",";
                }
            }
            fileWriter_logFile.writeln("\nAverage energy consumption results:\nX,Device energy consumption,Device execution time,CPU energy consumption,CPU execution time,CPU optimized energy consumption,CPU optimized execution time,CPU-1,CPU-2", true);
            fileWriter_logFile.writeln(tempString_toWrite, true);  
            fileWriter_powerFile.writeln(tempString_toWrite, false);  


            //Calculating general Performance average results 
            if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="mini"){
                resultsGlobal_performance_mini[0] = resultsGlobal_performance_mini[0] + resultsPerformance_average[0];      //Add CPU time result
                resultsGlobal_performance_mini[1] = resultsGlobal_performance_mini[1] + resultsPerformance_average[1];      //Add CPU opt time result
                resultsGlobal_performance_mini.push_back(resultsPerformance_average[2]+resultsPerformance_average[3]);      //Add Device OPTX + Trans time result
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="small"){
                resultsGlobal_performance_small[0] = resultsGlobal_performance_small[0] + resultsPerformance_average[0];
                resultsGlobal_performance_small[1] = resultsGlobal_performance_small[1] + resultsPerformance_average[1];
                resultsGlobal_performance_small.push_back(resultsPerformance_average[2]+resultsPerformance_average[3]);                
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="medium"){
                resultsGlobal_performance_medium[0] = resultsGlobal_performance_medium[0] + resultsPerformance_average[0];
                resultsGlobal_performance_medium[1] = resultsGlobal_performance_medium[1] + resultsPerformance_average[1];
                resultsGlobal_performance_medium.push_back(resultsPerformance_average[2]+resultsPerformance_average[3]);
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="large"){
                resultsGlobal_performance_large[0] = resultsGlobal_performance_large[0] + resultsPerformance_average[0];
                resultsGlobal_performance_large[1] = resultsGlobal_performance_large[1] + resultsPerformance_average[1];
                resultsGlobal_performance_large.push_back(resultsPerformance_average[2]+resultsPerformance_average[3]);
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="extralarge"){
                resultsGlobal_performance_extralarge[0] = resultsGlobal_performance_extralarge[0] + resultsPerformance_average[0];
                resultsGlobal_performance_extralarge[1] = resultsGlobal_performance_extralarge[1] + resultsPerformance_average[1];
                resultsGlobal_performance_extralarge.push_back(resultsPerformance_average[2]+resultsPerformance_average[3]);
            }


            //Calculating general Performance average results 
            if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="mini"){
                resultsGlobal_power_mini[0] = resultsGlobal_power_mini[0] + resultsPower_average[2];        //Add CPU consumption result
                resultsGlobal_power_mini[1] = resultsGlobal_power_mini[1] + resultsPower_average[3];        //Add CPU time result
                resultsGlobal_power_mini[2] = resultsGlobal_power_mini[2] + resultsPower_average[4];        //Add CPU Opt consumption result
                resultsGlobal_power_mini[3] = resultsGlobal_power_mini[3] + resultsPower_average[5];        //Add CPU Opt time result
                resultsGlobal_power_mini.push_back(resultsPower_average[0]);                                //Add device OPTX + Trans consumption result
                resultsGlobal_power_mini.push_back(resultsPower_average[1]);                                //Add device OPTX + Trans time result
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="small"){
                resultsGlobal_power_small[0] = resultsGlobal_power_small[0] + resultsPower_average[2];
                resultsGlobal_power_small[1] = resultsGlobal_power_small[1] + resultsPower_average[3];
                resultsGlobal_power_small[2] = resultsGlobal_power_small[2] + resultsPower_average[4];
                resultsGlobal_power_small[3] = resultsGlobal_power_small[3] + resultsPower_average[5];
                resultsGlobal_power_small.push_back(resultsPower_average[0]);
                resultsGlobal_power_small.push_back(resultsPower_average[1]);               
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="medium"){
                resultsGlobal_power_medium[0] = resultsGlobal_power_medium[0] + resultsPower_average[2];
                resultsGlobal_power_medium[1] = resultsGlobal_power_medium[1] + resultsPower_average[3];
                resultsGlobal_power_medium[2] = resultsGlobal_power_medium[2] + resultsPower_average[4];
                resultsGlobal_power_medium[3] = resultsGlobal_power_medium[3] + resultsPower_average[5];
                resultsGlobal_power_medium.push_back(resultsPower_average[0]);
                resultsGlobal_power_medium.push_back(resultsPower_average[1]);
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="large"){
                resultsGlobal_power_large[0] = resultsGlobal_power_large[0] + resultsPower_average[2];
                resultsGlobal_power_large[1] = resultsGlobal_power_large[1] + resultsPower_average[3];
                resultsGlobal_power_large[2] = resultsGlobal_power_large[2] + resultsPower_average[4];
                resultsGlobal_power_large[3] = resultsGlobal_power_large[3] + resultsPower_average[5];
                resultsGlobal_power_large.push_back(resultsPower_average[0]);
                resultsGlobal_power_large.push_back(resultsPower_average[1]);
            }else if(jsonConfiguration.get_testList()[i].get_executionList()[j].get_dataSize()=="extralarge"){
                resultsGlobal_power_extralarge[0] = resultsGlobal_power_extralarge[0] + resultsPower_average[2];
                resultsGlobal_power_extralarge[1] = resultsGlobal_power_extralarge[1] + resultsPower_average[3];
                resultsGlobal_power_extralarge[2] = resultsGlobal_power_extralarge[2] + resultsPower_average[4];
                resultsGlobal_power_extralarge[3] = resultsGlobal_power_extralarge[3] + resultsPower_average[5];
                resultsGlobal_power_extralarge.push_back(resultsPower_average[0]);
                resultsGlobal_power_extralarge.push_back(resultsPower_average[1]);
            }

        }

        //Generating performance graphics and tables
        if(jsonConfiguration.get_testList()[i].get_generate_performanceGraphics()){
            result = externConnec_performanceGraphics.executeCommand(
                jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_performanceFile());
            if(!result){
                fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_performanceFile() );
            }
            result = externConnec_performanceTable.executeCommand(
                jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_performanceFile());
            if(!result){
                fileWriter_logFile.writeln("ERROR..: Couldn't generate the table of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_performanceFile() );
            }
        }
    
        //Generating power graphics and tables
        if(jsonConfiguration.get_testList()[i].get_generate_powerGraphics()){
            result = externConnec_powerGraphics.executeCommand(
                jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_powerFile());
            if(!result){
                fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_powerFile() );
            }
            result = externConnec_powerTable.executeCommand(
                jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_powerFile());
            if(!result){
                fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_testList()[i].get_powerFile() );
            }           
        }
    }


    //Calculating, printing and generating tables of general performance results 
    resultsGlobal_performance_mini[0]=resultsGlobal_performance_mini[0]/(resultsGlobal_performance_mini.size()-2);
    resultsGlobal_performance_mini[1]=resultsGlobal_performance_mini[1]/(resultsGlobal_performance_mini.size()-2);
    resultsGlobal_performance_small[0]=resultsGlobal_performance_small[0]/(resultsGlobal_performance_small.size()-2);
    resultsGlobal_performance_small[1]=resultsGlobal_performance_small[1]/(resultsGlobal_performance_small.size()-2);
    resultsGlobal_performance_medium[0]=resultsGlobal_performance_medium[0]/(resultsGlobal_performance_medium.size()-2);
    resultsGlobal_performance_medium[1]=resultsGlobal_performance_medium[1]/(resultsGlobal_performance_medium.size()-2);
    resultsGlobal_performance_large[0]=resultsGlobal_performance_large[0]/(resultsGlobal_performance_large.size()-2);
    resultsGlobal_performance_large[1]=resultsGlobal_performance_large[1]/(resultsGlobal_performance_large.size()-2);
    resultsGlobal_performance_extralarge[0]=resultsGlobal_performance_extralarge[0]/(resultsGlobal_performance_extralarge.size()-2);
    resultsGlobal_performance_extralarge[1]=resultsGlobal_performance_extralarge[1]/(resultsGlobal_performance_extralarge.size()-2);

    printResults(fileWriter_logFile, fileWriter_global_performanceFile, resultsGlobal_performance_mini, "mini");
    printResults(fileWriter_logFile, fileWriter_global_performanceFile, resultsGlobal_performance_small, "small");
    printResults(fileWriter_logFile, fileWriter_global_performanceFile, resultsGlobal_performance_medium, "medium");
    printResults(fileWriter_logFile, fileWriter_global_performanceFile, resultsGlobal_performance_large, "large");
    printResults(fileWriter_logFile, fileWriter_global_performanceFile, resultsGlobal_performance_extralarge, "extralarge");

    if(jsonConfiguration.get_generate_global_PerformanceGraphics()){
        result = externConnec_global_performanceGraphics.executeCommand(
            jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_performanceFile());
        if(!result){
            fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_performanceFile());
        }
        result = externConnec_global_performanceTable.executeCommand(
            jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_performanceFile());
        if(!result){
            fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_performanceFile());
        }
    }

    //Calculating, printing and generating tables of general performance results 
    resultsGlobal_power_mini[0]=resultsGlobal_power_mini[0]/((resultsGlobal_power_mini.size()-4)/2);
    resultsGlobal_power_mini[1]=resultsGlobal_power_mini[1]/((resultsGlobal_power_mini.size()-4)/2);
    resultsGlobal_power_mini[2]=resultsGlobal_power_mini[2]/((resultsGlobal_power_mini.size()-4)/2);
    resultsGlobal_power_mini[3]=resultsGlobal_power_mini[3]/((resultsGlobal_power_mini.size()-4)/2);
    resultsGlobal_power_small[0]=resultsGlobal_power_small[0]/((resultsGlobal_power_small.size()-4)/2);
    resultsGlobal_power_small[1]=resultsGlobal_power_small[1]/((resultsGlobal_power_small.size()-4)/2);
    resultsGlobal_power_small[2]=resultsGlobal_power_small[2]/((resultsGlobal_power_small.size()-4)/2);
    resultsGlobal_power_small[3]=resultsGlobal_power_small[3]/((resultsGlobal_power_small.size()-4)/2);
    resultsGlobal_power_medium[0]=resultsGlobal_power_medium[0]/((resultsGlobal_power_medium.size()-4)/2);
    resultsGlobal_power_medium[1]=resultsGlobal_power_medium[1]/((resultsGlobal_power_medium.size()-4)/2);
    resultsGlobal_power_medium[2]=resultsGlobal_power_medium[2]/((resultsGlobal_power_medium.size()-4)/2);
    resultsGlobal_power_medium[3]=resultsGlobal_power_medium[3]/((resultsGlobal_power_medium.size()-4)/2);
    resultsGlobal_power_large[0]=resultsGlobal_power_large[0]/((resultsGlobal_power_large.size()-4)/2);
    resultsGlobal_power_large[1]=resultsGlobal_power_large[1]/((resultsGlobal_power_large.size()-4)/2);
    resultsGlobal_power_large[2]=resultsGlobal_power_large[2]/((resultsGlobal_power_large.size()-4)/2);
    resultsGlobal_power_large[3]=resultsGlobal_power_large[3]/((resultsGlobal_power_large.size()-4)/2);
    resultsGlobal_power_extralarge[0]=resultsGlobal_power_extralarge[0]/((resultsGlobal_power_extralarge.size()-4)/2);
    resultsGlobal_power_extralarge[1]=resultsGlobal_power_extralarge[1]/((resultsGlobal_power_extralarge.size()-4)/2);
    resultsGlobal_power_extralarge[2]=resultsGlobal_power_extralarge[2]/((resultsGlobal_power_extralarge.size()-4)/2);
    resultsGlobal_power_extralarge[3]=resultsGlobal_power_extralarge[3]/((resultsGlobal_power_extralarge.size()-4)/2);

    printResults(fileWriter_logFile, fileWriter_global_powerFile, resultsGlobal_power_mini, "mini");
    printResults(fileWriter_logFile, fileWriter_global_powerFile, resultsGlobal_power_small, "small");
    printResults(fileWriter_logFile, fileWriter_global_powerFile, resultsGlobal_power_medium, "medium");
    printResults(fileWriter_logFile, fileWriter_global_powerFile, resultsGlobal_power_large, "large");
    printResults(fileWriter_logFile, fileWriter_global_powerFile, resultsGlobal_power_extralarge, "extralarge");

    if(jsonConfiguration.get_generate_global_PowerGraphics()){
        result = externConnec_global_powerGraphics.executeCommand(
            jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_powerFile());
        if(!result){
            fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_powerFile());
        }
        result = externConnec_global_powerTable.executeCommand(
            jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_powerFile());
        if(!result){
            fileWriter_logFile.writeln("ERROR..: Couldn't generate the image of " + jsonConfiguration.get_outDir()+ outFolderID + "/" + jsonConfiguration.get_global_powerFile());
        }
    }




    printFinalMessage(numFailures, fileWriter_logFile);

    return 0;
}
//*************************************
// MAIN FUNCTION - END
//*************************************


bool runExecution(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_performanceFile){

    bool result = false;
    if(exec.get_host().find("doitgen") != string::npos){
        result = DoitgenHost::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);

    }else if(exec.get_host().find("cholesky") != string::npos){
        result = CholeskyHost::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("gemmPer") != string::npos){
        result = GemmPerHost::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("gemm") != string::npos){
        result = GemmHost::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("jacobi2d") != string::npos){
        result = Jacobi2dHost::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("vectorAdd") != string::npos){
        result = VectorAddHost::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("studyCase1") != string::npos){
        result = StudyCase1Host::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("studyCase2") != string::npos){
        result = StudyCase2Host::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else if(exec.get_host().find("studyCase3") != string::npos){
        result = StudyCase3Host::exec(exec, resultsPerformance, resultsPower, fileWriter_logFile, fileWriter_performanceFile);   
    
    }else{
        fileWriter_logFile.writeln("ERROR..: Host name unknow.");
        return false;
    }
    
    return result;
}



void printFinalMessage(unsigned int numFailures, FileWriter_service fileWriter_logFile){

    if(numFailures==0){
        fileWriter_logFile.writeln("\033[1;32m**********************************************\033[0m\n", true);
        fileWriter_logFile.writeln("\033[1;32m* ALL EXECUTIONS HAVE FINALIZED SUCCESSFULLY *\033[0m\n", true);
        fileWriter_logFile.writeln("\033[1;32m**********************************************\033[0m\n", true);
    }else{
        fileWriter_logFile.writeln("\033[1;31m**********************************************\033[0m\n", true);
        fileWriter_logFile.writeln("\033[1;31m  " + to_string(numFailures) + " EXECUTION/S HAVE FAILED\033[0m\n", true);
        fileWriter_logFile.writeln("\033[1;31m**********************************************\033[0m\n", true);
    }

}



void printResults(FileWriter_service &fileLog, FileWriter_service &fileStats, vector<double> &resultList, string size){
    string tempString_toWrite=size+",";
    for (int i=0 ; i<resultList.size() ; i++){
        if(i==resultList.size()-1){
            tempString_toWrite += to_string(resultList[i]);
        }else{
            tempString_toWrite += to_string(resultList[i]) + ",";
        }
    }
    fileLog.writeln(tempString_toWrite, true);  
    fileStats.writeln(tempString_toWrite, false);
    return;
}