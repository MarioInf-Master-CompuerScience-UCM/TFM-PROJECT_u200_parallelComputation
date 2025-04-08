#ifndef JSONCONFIGURATION_H_
#define JSONCONFIGURATION_H_

#include <string>
#include <vector>
#include "test/test.hpp"


using namespace std;

class JsonConfiguration{
    
    private:
        bool status;
        bool verbose;
        string outDir;
        string logFile;
        string global_performanceFile;
        string global_powerFile;
        bool generate_global_PerformanceGraphics;
        bool generate_global_PowerGraphics;
        vector<Test> testList;
    

    public:
        JsonConfiguration();
        JsonConfiguration(bool status, string outDir, string logFile, vector<Test> testList);
        ~JsonConfiguration();


        string displayInfo(string initLineString);


        bool get_status() const;
        void set_status(bool data);
        
        bool get_verbose() const;
        void set_verbose(bool data);

        string get_outDir() const;
        void set_outDir(string data);

        string get_logFile() const;
        void set_logFile(string data);

        string get_global_performanceFile() const;
        void set_global_performanceFile(string data);

        string get_global_powerFile() const;
        void set_global_powerFile(string data);

        bool get_generate_global_PerformanceGraphics() const;
        void set_generate_global_PerformanceGraphics(bool data);

        bool get_generate_global_PowerGraphics() const;
        void set_generate_global_PowerGraphics(bool data);

        vector<Test>& get_testList();
        void set_testList(vector<Test> newList);

};

#endif