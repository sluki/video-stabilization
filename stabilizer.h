#pragma once
#include <opencv2/opencv.hpp>

// The `Stabilizer` class stabilizes input images with respect to 
// a reference image provided at construction.
class Stabilizer {
public:
	// Constructs a Stabilizer object with a reference image. The reference
	// image is used as the basis for stabilization.
	explicit Stabilizer(cv::Mat3b&& referenceImage);

	// Stabilizes the input image (`srcImage`) using the reference
	// image and outputs the stabilized image to `dstImage`.
	void stabilize(const cv::Mat3b& srcImage, cv::Mat3b& dstImage) const;

private:
	cv::Mat3b m_referenceImage;           // The reference image used for stabilization.
	std::vector<cv::Point2f> m_features;  // Tracked features extracted from the reference image.
};
