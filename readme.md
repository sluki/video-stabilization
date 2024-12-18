# Video Stabilization

## Description

This project provides a video stabilization tool using OpenCV in C++. It reads an input video, stabilizes it frame by frame, and writes the stabilized video to an output file.

## Features

- **Video Stabilization**: Stabilizes video frames with respect to the first frame using a sparse optical flow and an estimation of the affine transformation using the RANSAC algorithm.
- **Command Line Interface**: Uses OpenCV's `CommandLineParser` for easy command-line usage.
- **Real-time Preview**: Displays a preview of the stabilized video during processing.

## Usage

To stabilize a video, run the following command:
```sh
./video-stabilization <input_video_path> <output_video_path>
```

## Detailed Code Overview

### main Function (main.cpp)

The main function parses command-line arguments for input and output video paths and calls the `stabilizeVideo` function.

### stabilizeVideo function (main.cpp)

This function reads the input video, initializes the `Stabilizer` class with the first frame of the video, and processes each frame to produce a stabilized output.

### Stabilizer class (`stabilizer.h` and `stabilizer.cpp`)

The `Stabilizer` class is responsible for stabilizing each frame using optical flow and affine transformations. It extracts features from the reference image and tracks these features in the subsequent frames to perform stabilization.

#### constructor

1. Extracts good points to track using the `cv::goodFeaturesToTrack` function. These points will be used as inputs for optical flow.

#### stabilize method

1. Computes the optical flow between the first frame and the current frame.
2. Estimates an affine transformation between the features in the reference image and the current frame using RANSAC algorithm to avoid using actually moving objects for stabilization.
3. Applies the affine transformation to the current frame to produce the stabilized frame.