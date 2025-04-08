#include <iostream>
#include <string>
#include <typeinfo>
#include <cctype>

#include "helper.hpp"



using namespace std;

string Helper::getNameOfType(const char* mangledName) {
    while (isdigit(*mangledName)) {
        ++mangledName;
    }

    string toLowerCaseName = mangledName;
    for (char& c : toLowerCaseName) {
        c = tolower(c);
    }

    return toLowerCaseName;
}