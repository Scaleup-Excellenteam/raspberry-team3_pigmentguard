
#ifndef PIGMENTGUARD_CONTROLLER_H
#define PIGMENTGUARD_CONTROLLER_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <csignal>


class Controller {
public:
    Controller() = default;

    void run();

    void startTest();

private:
    bool shouldRun = true;
};


#endif //PIGMENTGUARD_CONTROLLER_H
