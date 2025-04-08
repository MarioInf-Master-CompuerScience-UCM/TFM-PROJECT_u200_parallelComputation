#ifndef _STUDYCASE1HOST_HPP_
#define _STUDYCASE1HOST_HPP_

#include <iostream>
#include <vector>
#include <typeinfo>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "studyCase1Host_a/studyCase1Host_a.hpp"
#include "studyCase1Host_b/studyCase1Host_b.hpp"
#include "studyCase1Host_c/studyCase1Host_c.hpp"

class StudyCase1Host {


    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:



    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:

        //********************************
        //* CONSTRUCTORS AND DESTRUCTORS *
        //********************************
        StudyCase1Host();
        ~StudyCase1Host();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif