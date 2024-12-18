#include <iostream>
#include <algorithm>
#include <numeric>

#include <opencv2/opencv.hpp>

#include "stabilizer.h"


// Reads an input video from `inputPath` and writes the stabilized video to the `outputPath`
int stabilizeVideo(const std::string& inputPath, const std::string& outputPath) {
    cv::VideoCapture cap(inputPath);

    if (!cap.isOpened()) {
        std::cerr << "Failed to open input video." << std::endl;
        return -1;
    }

    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);
    int codec = static_cast<int>(cap.get(cv::CAP_PROP_FOURCC));

    cv::VideoWriter writer(outputPath, codec, fps, cv::Size(frame_width, frame_height));

    cv::Mat3b image, stabilized;
    cap >> image;

    Stabilizer stabilizer{ std::move(image) };

    std::chrono::duration<double> t = std::chrono::seconds::zero();
    int frameIndex = 0;

    for (; frameIndex < 1000; frameIndex++) {
        cap >> image;

        if (image.empty())
            break;

        auto t0 = std::chrono::high_resolution_clock::now();
        stabilizer.stabilize(image, stabilized);
        t += std::chrono::high_resolution_clock::now() - t0;

        cv::imshow("preview", stabilized);
        cv::waitKey(1);
        writer << stabilized;
    }

    std::cout << "Total frames: " << frameIndex << std::endl;
    std::cout << "Time: " << t << std::endl;
    std::cout << "Frames/s: " << frameIndex / t.count() << std::endl;
    return 0;
}


int main(int argc, char** argv) {
    const std::string keys =
        "{help h usage ? |      | Print this help message }"
        "{@input         |      | Path to the input video }"
        "{@output        |      | Path to the output video }";

    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    auto inputPath = parser.get<std::string>("@input");
    auto outputPath = parser.get<std::string>("@output");

    if (!parser.check()) {
        parser.printErrors();
        return -1;
    }

    return stabilizeVideo(inputPath, outputPath);
}
