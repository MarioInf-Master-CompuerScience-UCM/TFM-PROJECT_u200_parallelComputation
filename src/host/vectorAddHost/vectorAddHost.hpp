#ifndef _VECTORADDHOST_HPP_
#define _VECTORADDHOST_HPP_

#include <iostream>
#include <vector>
#include <typeinfo>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "vectorAddHost_Opt0/vectorAddHost_Opt0.hpp"
#include "vectorAddHost_Opt1/vectorAddHost_Opt1.hpp"
#include "vectorAddHost_Opt2/vectorAddHost_Opt2.hpp"
#include "vectorAddHost_Opt3/vectorAddHost_Opt3.hpp"
#include "vectorAddHost_Opt4/vectorAddHost_Opt4.hpp"

class VectorAddHost {


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
        VectorAddHost();
        ~VectorAddHost();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif