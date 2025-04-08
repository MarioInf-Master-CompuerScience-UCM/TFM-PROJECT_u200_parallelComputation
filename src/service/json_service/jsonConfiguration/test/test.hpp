#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <string>
#include <vector>
#include "../execution/execution.hpp"

using namespace std;

class Test{

    //*****************************
    //* DEFINITION ZONE ATRIBUTES *
    //*****************************
    private:
        string name;
        string performanceFile;
        string powerFile;
        bool generate_performanceGraphics;
        bool generate_powerGraphics;
        vector<Execution> executionList;


    //*****************************
    //* DEFINITION ZONE FUNCTIONS *
    //*****************************
    public:
        Test();
        Test(string mame, string performanceFile, string powerFile, bool generate_performanceGraphics, bool generate_powerGraphics, vector<Execution> executionList);
        ~Test();


        string displayInfo(string initLineString);



        //*************************
        //* GET AND SET FUNCTIONS *
        //*************************
        string get_name() const;
        void set_name(string data);

        string get_performanceFile() const;
        void set_performanceFile(string data);

        string get_powerFile() const;
        void set_powerFile(string data);

        bool get_generate_performanceGraphics() const;
        void set_generate_performanceGraphics(bool data);

        bool get_generate_powerGraphics() const;
        void set_generate_powerGraphics(bool data);
        
        vector<Execution>& get_executionList();
        Execution getElement_executionList_byIndex(unsigned int index);
        void set_executionList(vector<Execution> newList);
        void setElement_executionList_byIndex(unsigned int index, Execution value);






};

#endif