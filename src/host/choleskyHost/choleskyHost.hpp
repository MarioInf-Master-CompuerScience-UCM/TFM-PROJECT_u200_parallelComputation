#ifndef _CHOLESKYHOST_HPP_
#define _CHOLESKYHOST_HPP_

#include <iostream>
#include <vector>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "choleskyHost_Opt0/choleskyHost_Opt0.hpp"
#include "choleskyHost_Opt1/choleskyHost_Opt1.hpp"
#include "choleskyHost_Opt2/choleskyHost_Opt2.hpp"
#include "choleskyHost_Opt3/choleskyHost_Opt3.hpp"
#include "choleskyHost_Opt4/choleskyHost_Opt4.hpp"

class CholeskyHost {


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
        CholeskyHost();
        ~CholeskyHost();
        
        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);



    private:

};
#endif