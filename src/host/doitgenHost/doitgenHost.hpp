#ifndef DOITGENHOST_HPP
#define DOITGENHOST_HPP

#include <iostream>
#include <vector>
#include "../../service/json_service/jsonConfiguration/execution/execution.hpp"
#include "../../service/fileWriter_service/fileWriter_service.hpp"
#include "../../utilities/helper/helper.hpp"
#include "doitgenHost_Opt0/doitgenHost_Opt0.hpp"
#include "doitgenHost_Opt1/doitgenHost_Opt1.hpp"
#include "doitgenHost_Opt2/doitgenHost_Opt2.hpp"
#include "doitgenHost_Opt3/doitgenHost_Opt3.hpp"
#include "doitgenHost_Opt4/doitgenHost_Opt4.hpp"

class DoitgenHost {


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
        DoitgenHost();
        ~DoitgenHost();

        static bool exec(Execution exec, vector<double>& resultsPerformance, vector<double>& resultsPower, FileWriter_service fileWriter_logFile, FileWriter_service fileWriter_statsFile);


    private:

};
#endif