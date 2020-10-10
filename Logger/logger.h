//
// Created by Alex on 24.09.2020.
//

#ifndef LOGGER

#define LOGGER = 1

#include <fstream>

class logger {
private:
    std::ofstream of;
    bool isOpened;
public:
    logger();
    explicit logger(const std::string& logFolder);
    bool open(const std::string& logFolder);

    bool put(const std::string &info);

    bool operator<<(const std::string&);

    void close();
    ~logger();
};

#endif //LOGGER
