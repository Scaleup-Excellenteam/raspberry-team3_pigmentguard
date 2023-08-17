#include "Controller.h"

void Controller::run() {
    startTest();
}


void Controller::startTest() {
    const std::string saveDirectory = "testSnapshots";
    const std::string inp;
    const int intervalSeconds = 5; // Capture interval in seconds
    const int videoDuration = 30;   // Video duration in seconds

    // Create the directory if it doesn't exist
    mkdir(saveDirectory.c_str(), 0777);

    takePictures(saveDirectory, videoDuration, intervalSeconds);
}


[[noreturn]] void Controller::takePictures(const std::string& saveDirectory, const int videoDuration, const int intervalSeconds) {

    while (true) {
        // Generate a unique filename based on the current time
        std::time_t currentTime = std::time(nullptr);
        std::string videoFilename = saveDirectory + "/video_" + std::to_string(currentTime) + ".h264";

        // Capture a video using raspivid command
        std::string captureVideoCommand =
                "raspivid -o " + videoFilename + " -t " + std::to_string(videoDuration * 1000);
        int result = std::system(captureVideoCommand.c_str());

        if (result != 0) {
            std::cerr << "Error capturing video." << std::endl;
            continue;
        }

        // Use FFmpeg to extract image frames from the video
        std::string framesDirectory = saveDirectory + "/frames_" + std::to_string(currentTime);
        mkdir(framesDirectory.c_str(), 0777);

        std::string extractFramesCommand = "ffmpeg -i " + videoFilename + " -vf fps=1 " + framesDirectory + "/frame_%d.jpg";
        result = std::system(extractFramesCommand.c_str());

        // Wait for the command to commit before capturing the next video
        sleep(intervalSeconds);

        if (result != 0) {
            std::cerr << "Error extracting frames." << std::endl;
        }

        ImageProcessing imgProc;
        imgProc.processImages(framesDirectory);
    }
}
