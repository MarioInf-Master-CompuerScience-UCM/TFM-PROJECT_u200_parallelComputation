#ifndef FILEWRITER_INTERFACE_H_
#define FILEWRITER_INTERFACE_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <mutex>
#include <map>
#include <filesystem>

using namespace std;

class FileWriter_service{

    private:
        string fileURL;
        bool verbose;
        static map<string, mutex> mutexes;

    public:
        FileWriter_service();
        FileWriter_service(string fileURL);
        FileWriter_service(string fileURL, bool verbose);
        ~FileWriter_service();

        //**********************************
        // DEFINICIÓN DE MÉTODOS FUNCIONALES
        //**********************************
        bool write(const string& data, bool verbose);
        bool write(const string& data);
        bool write(ostringstream& data, bool verbose);
        bool write(ostringstream& data);

        bool writeln(const string& data, bool verbose);
        bool writeln(const string& data);
        bool writeln(ostringstream& data, bool verbose);
        bool writeln(ostringstream& data);

        
        bool createFile_recursive(string url);


        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getFileURL() const;
        void setFileURL(string data);

        bool getVerbose() const;
        void setVerbose(bool data);


};
#endif