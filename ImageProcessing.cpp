#include "ImageProcessing.h"


void ImageProcessing::processImages(std::string &imageDir) {
    int moleCounter = 0;
    double paddingFactor = 3.0;

    //    Load the Image and Preprocess
    cv::Mat image = cv::imread("skin_image.png");
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);

    //    Segmentation using Adaptive Thresholding
    cv::Mat thresh;
    cv::adaptiveThreshold(gray, thresh, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 11, 2);

    //    Morphological Operations
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(thresh, thresh, cv::MORPH_OPEN, kernel);

    //     Detect contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    //    Filter and Highlight Detected Moles
    for (const auto &contour: contours) {
        double area = cv::contourArea(contour);
        if (area > 500 && area < 1000) {  // These values can be adjusted based on your dataset
            cv::Point2f center;
            float radius;
            cv::minEnclosingCircle(contour, center, radius);
            cv::circle(image, center, static_cast<int>(radius), cv::Scalar(0, 255, 0), 2);

            // Adjust the cropping region with padding
            cv::Rect cropRect(center.x - paddingFactor * radius, center.y - paddingFactor * radius,
                              2 * paddingFactor * radius, 2 * paddingFactor * radius);

            // Check if cropRect goes out of image boundaries and adjust if needed
            cropRect &= cv::Rect(0, 0, image.cols, image.rows);

            cv::Mat croppedMole = image(cropRect);

            // Save or process the cropped image
            std::string croppedImageName = "mole_" + std::to_string(moleCounter) + ".png";
            cv::imwrite(croppedImageName, croppedMole);
            moleCounter++;
        }
    }

    // display results
    cv::imshow("Detected Moles", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
