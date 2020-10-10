//
// Created by Alex on 24.09.2020.
//

#include "logger.h"
#include <ctime>

logger::logger():isOpened(false) {
}

logger::logger(const std::string& logFolder):isOpened(false) {
    open(logFolder);
}

bool logger::open(const std::string& logFolder) {

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [255];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,255," %d-%b-%Y %H.%M.%S",timeinfo);

    std::string filename = logFolder + "Log" + buffer + ".txt";

    of.open(filename);
    isOpened=of.is_open();
    return isOpened;
}

bool logger::put(const std::string& info) {
    if (!isOpened) return false;
    of << info;
    of.flush();
   return true;
}

void logger::close() {
    if (isOpened) {
        of.close();
        isOpened = false;
    }
}

logger::~logger() {
    close();
}

bool logger::operator<<(const std::string& msg) {
    return put(msg);
}

