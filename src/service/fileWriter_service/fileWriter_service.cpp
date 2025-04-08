#include <iostream>
#include <fstream>
#include <string>

#include "fileWriter_service.hpp"

using namespace std;


//***************************************************************
// DEFINICIÓN DE CONSTRUCORES, DESTRUCTORES Y VARIABLES ESTÁTICAS
//***************************************************************
map<string, mutex> FileWriter_service::mutexes;

FileWriter_service::FileWriter_service():
    fileURL("untitled"),
    verbose(false)
{}
FileWriter_service::FileWriter_service(string fileURL):
    fileURL(fileURL),
    verbose(false)
{
    createFile_recursive(getFileURL());
}
FileWriter_service::FileWriter_service(string fileURL, bool verbose):
    fileURL(fileURL),
    verbose(verbose)
{
    createFile_recursive(getFileURL());
}

FileWriter_service::~FileWriter_service(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************

// Método write
//********************************
bool FileWriter_service::write(const string& data) {
    lock_guard<mutex> lock(mutexes[fileURL]);
    ofstream archivo(fileURL, ios::app);

    if (archivo.is_open()) {
        archivo << data;
        archivo.close();
        if (getVerbose()) {
            cout << data;
        }
    } else {
        cerr << "El archivo de escritura no se abrió correctamente." << endl;
        return false;
    }

    return true;
}
bool FileWriter_service::write(const string& data, bool verbose) {
    lock_guard<mutex> lock(mutexes[fileURL]);
    ofstream archivo(fileURL, ios::app);

    if (archivo.is_open()) {
        archivo << data;
        archivo.close();
        if (verbose) {
            cout << data;
        }
    } else {
        cerr << "El archivo de escritura no se abrió correctamente." << endl;
        return false;
    }

    return true;
}
bool FileWriter_service::write(ostringstream& data) {
    return write(data.str());
}
bool FileWriter_service::write(ostringstream& data, bool verbose) {
    return write(data.str(), verbose);
}


// Método writeln
//********************************
bool FileWriter_service::writeln(const string& data) {
    lock_guard<mutex> lock(mutexes[fileURL]);
    ofstream archivo(fileURL, ios::app);

    if (archivo.is_open()) {
        archivo << data << endl;
        archivo.close();
        if (getVerbose()) {
            cout << data << endl;
        }
    } else {
        cerr << "El archivo de escritura no se abrió correctamente." << endl;
        return false;
    }
    return true;
}
bool FileWriter_service::writeln(const string& data, bool verbose) {
    lock_guard<mutex> lock(mutexes[fileURL]);
    ofstream archivo(fileURL, ios::app);

    if (archivo.is_open()) {
        archivo << data << endl;
        archivo.close();
        if (verbose) {
            cout << data << endl;
        }
    } else {
        cerr << "El archivo de escritura no se abrió correctamente." << endl;
        return false;
    }
    return true;
}
bool FileWriter_service::writeln(ostringstream& data) {
    return writeln(data.str());
}
bool FileWriter_service::writeln(ostringstream& data, bool verbose) {
    return writeln(data.str(), verbose);
}


// Método createFile_recursive
//********************************
bool FileWriter_service::createFile_recursive(string url) {
    try {
        filesystem::path filePath(url);
        filesystem::create_directories(filePath.parent_path());
        ofstream file(url);
        if (file) {
            return true;
        } else {
            cerr << "No se pudo crear el archivo: " << url << endl;
            return false;
        }
    } catch (const filesystem::filesystem_error& e) {
        cerr << "Error al crear el archivo: " << e.what() << endl;
        return false;
    }
}


//**********************************************
//* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
//**********************************************
string FileWriter_service::getFileURL() const{ return fileURL; }
void FileWriter_service::setFileURL(string data){ 
    fileURL = data; 
}

bool FileWriter_service::getVerbose() const{ return verbose;}
void FileWriter_service::setVerbose(bool data){ 
    verbose = data;
}