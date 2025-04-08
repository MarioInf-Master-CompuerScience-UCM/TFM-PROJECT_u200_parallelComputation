#ifndef _DATEANDTIME_H_
#define _DATEANDTIME_H_

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class DateAndTime {
    private:


    public:
        DateAndTime();
        ~DateAndTime();

        static string getCurrentDateTime();
};

#endif
