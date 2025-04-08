#include "dateAndTime.hpp"

using namespace std;

DateAndTime::DateAndTime() 
{}
DateAndTime::~DateAndTime()
{}


string DateAndTime::getCurrentDateTime() {
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H:%M:%S", localTime);
    return string(buffer);
}
