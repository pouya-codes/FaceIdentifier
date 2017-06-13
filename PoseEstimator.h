/*
 * Classifier.h
 *
 *  Created on: Dec 6, 2016
 *      Author: ubuntu
 */

#ifndef POSEESTIMATOR_H_
#define POSEESTIMATOR_H_
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace caffe;
using std::string;


class PoseEstimator {
 public:
 PoseEstimator(const string& model_file,
             const string& trained_file,
             const string& mean_file);

  const float* Classify(const cv::Mat& img);

 private:
  void SetMean(const string& mean_file);

  const float* Predict(const cv::Mat& img);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,
                  std::vector<cv::Mat>* input_channels);

 private:
  shared_ptr<Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
};

#endif /* POSEESTIMATOR_H_ */
