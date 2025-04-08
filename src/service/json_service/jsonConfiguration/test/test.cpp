#include "test.hpp"


//*******************************
// CONSTRUCTORS DEFINITION ZONE *
//*******************************
Test::Test():
    name(""),
    performanceFile(""),
    powerFile(""),
    generate_performanceGraphics(false),
    generate_powerGraphics(false),
    executionList(vector<Execution>()
){}
Test::Test(string mame, string performanceFile, string powerFile, bool generate_performanceGraphics, bool generate_powerGraphics, vector<Execution> executionList):
    name(name),
    performanceFile(performanceFile),
    powerFile(powerFile),
    generate_performanceGraphics(generate_performanceGraphics),
    generate_powerGraphics(generate_powerGraphics),
    executionList(vector<Execution>()
){
    set_executionList(executionList);
}
Test::~Test(){}



//************************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES *
//************************************
string Test::displayInfo(string initLineString){
    string info = initLineString + "{\n";
    info += initLineString + "Name: " + get_name() + "\n";
    info += initLineString + "Performance File: " + get_performanceFile() + "\n";
    info += initLineString + "Power File: " + get_powerFile() + "\n";
    info += initLineString + "Generate performance graphics?: " + (get_generate_performanceGraphics()? "true" : "false") + "\n";
    info += initLineString + "Generate power graphics?: " + (get_generate_powerGraphics()? "true" : "false") + "\n";
    info += initLineString + "Execution List:\n";
    for (size_t i = 0; i < get_executionList().size(); ++i) {
        info += get_executionList()[i].displayInfo(initLineString + "\t");
    }

    info += initLineString + "}\n";
    return info;
}


//*************************
//* GET AND SET FUNCTIONS *
//*************************
string Test::get_name() const{ return name; }
void Test::set_name(string data){ name=data; }

string Test::get_performanceFile() const{ return performanceFile; }
void Test::set_performanceFile(string data){ performanceFile=data; }

string Test::get_powerFile() const{ return powerFile; }
void Test::set_powerFile(string data){ powerFile=data; }

bool Test::get_generate_performanceGraphics() const{ return generate_performanceGraphics;}
void Test::set_generate_performanceGraphics(bool data){ generate_performanceGraphics=data;}

bool Test::get_generate_powerGraphics() const{ return generate_powerGraphics; }
void Test::set_generate_powerGraphics(bool data){ generate_powerGraphics=data; }

vector<Execution>& Test::get_executionList(){ return executionList; }
Execution Test::getElement_executionList_byIndex(unsigned int index){
    return get_executionList()[index];
}
void Test::set_executionList(vector<Execution> newList){
    get_executionList().clear();
    for (int i=0 ; i<newList.size() ; i++) {
        get_executionList().push_back(newList[i]);
    }
}
void Test::setElement_executionList_byIndex(unsigned int index, Execution value){
    get_executionList()[index] = value;
}