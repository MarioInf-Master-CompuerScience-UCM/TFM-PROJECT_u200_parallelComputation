#include <iostream>
#include <fstream>
#include <cstdlib>
#include "externProgramsConnection_service.hpp"

using namespace std;

ExternProgramsConnection_service::ExternProgramsConnection_service(string generatePicture_URL):
    generatePyctures_URL(generatePicture_URL)
{}
ExternProgramsConnection_service::~ExternProgramsConnection_service(){}



bool ExternProgramsConnection_service::executeCommand(string entryParam){

    string command = "python3 " + get_generatePyctures_URL() + " " + entryParam;
    int result = system(command.c_str());
    if (result == 0) {
        return true;
    } else {
        return false;
    }
}


bool ExternProgramsConnection_service::executeCommand(){
    
    string command = "python3 " + get_generatePyctures_URL();
    for (const auto& filePath : get_generatePyctures_entryParams()) {
        command += " " + filePath;
    }

    int result = system(command.c_str());
    if (result == 0) {
        return true;
    } else {
        return false;
    }
}

//********************************************************
// ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
//********************************************************
string ExternProgramsConnection_service::get_generatePyctures_URL(){ return generatePyctures_URL; }
void ExternProgramsConnection_service::set_generatePyctures_URL(string data){ generatePyctures_URL = data; }


vector<string>& ExternProgramsConnection_service::get_generatePyctures_entryParams(){ return generatePyctures_entryParams;}
void ExternProgramsConnection_service::set_generatePyctures_entryParams(vector<string>& data){
    get_generatePyctures_entryParams().clear();
    for(int i=0 ; i<get_generatePyctures_entryParams().size() ; i++){
        get_generatePyctures_entryParams().push_back(data[i]);
    }
    return;
}