#ifndef _STUDYCASE2HOST_HPP_
#define _STUDYCASE2HOST_HPP_

#include <iostream>
#include <vector>
#include <typeinfo>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "studyCase2Host_a/studyCase2Host_a.hpp"
#include "studyCase2Host_b/studyCase2Host_b.hpp"
#include "studyCase2Host_c/studyCase2Host_c.hpp"
#include "studyCase2Host_d/studyCase2Host_d.hpp"

class StudyCase2Host {


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
        StudyCase2Host();
        ~StudyCase2Host();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif