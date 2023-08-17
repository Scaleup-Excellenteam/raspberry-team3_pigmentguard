#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <csignal>

#include "ImageProcessing.h"

class Controller {
public:
    Controller() = default;

    void run();

    void startTest();

    [[noreturn]] void takePictures(const std::string& string, int, int);

private:
    bool shouldRun = true;
};


