#ifndef _STUDYCASE3HOST_HPP_
#define _STUDYCASE3HOST_HPP_

#include <iostream>
#include <vector>
#include <typeinfo>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "studyCase3Host_a/studyCase3Host_a.hpp"
#include "studyCase3Host_b/studyCase3Host_b.hpp"
#include "studyCase3Host_c/studyCase3Host_c.hpp"
#include "studyCase3Host_d/studyCase3Host_d.hpp"

class StudyCase3Host {


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
        StudyCase3Host();
        ~StudyCase3Host();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif