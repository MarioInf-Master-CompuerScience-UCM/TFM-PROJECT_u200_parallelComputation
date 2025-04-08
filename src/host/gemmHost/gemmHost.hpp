#ifndef _GEMMHOST_HPP_
#define _GEMMHOST_HPP_

#include <iostream>
#include <vector>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "gemmHost_Opt0/gemmHost_Opt0.hpp"
#include "gemmHost_Opt1/gemmHost_Opt1.hpp"
#include "gemmHost_Opt2/gemmHost_Opt2.hpp"
#include "gemmHost_Opt3/gemmHost_Opt3.hpp"
#include "gemmHost_Opt4/gemmHost_Opt4.hpp"


class GemmHost {


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
        GemmHost();
        ~GemmHost();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif