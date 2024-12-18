#include "stabilizer.h"

#include "utils.h"


Stabilizer::Stabilizer(cv::Mat3b&& referenceImage) : m_referenceImage(std::move(referenceImage)) {

    cv::Mat1b gray;
    cv::cvtColor(m_referenceImage, gray, cv::COLOR_BGR2GRAY);

    int minDistance = static_cast<int>(std::sqrt(gray.cols * gray.rows / 2000));

    cv::goodFeaturesToTrack(gray, m_features, 1000, 0.01, minDistance);
}


void Stabilizer::stabilize(const cv::Mat3b& srcImage, cv::Mat3b& dstImage) const {
    std::vector<cv::Point2f> points;
    std::vector<float> errors;
    std::vector<unsigned char> status;
    cv::calcOpticalFlowPyrLK(m_referenceImage, srcImage, m_features, points, status, errors);

    auto features = filter(m_features, status);
    points = filter(points, status);

    std::vector<unsigned char> inliers;
    auto affine = cv::estimateAffine2D(features, points, inliers, 8, 1.0);

    cv::warpAffine(srcImage, dstImage, affine, cv::Size(srcImage.cols, srcImage.rows), cv::WARP_INVERSE_MAP | cv::INTER_CUBIC);
}
