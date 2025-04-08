#ifndef _GEMMPERHOST_HPP_
#define _GEMMPERHOST_HPP_

#include <iostream>
#include <vector>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "gemmPerHost_Opt0/gemmPerHost_Opt0.hpp"
#include "gemmPerHost_Opt1/gemmPerHost_Opt1.hpp"
#include "gemmPerHost_Opt2/gemmPerHost_Opt2.hpp"
#include "gemmPerHost_Opt3/gemmPerHost_Opt3.hpp"
#include "gemmPerHost_Opt4/gemmPerHost_Opt4.hpp"


class GemmPerHost {


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
        GemmPerHost();
        ~GemmPerHost();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif