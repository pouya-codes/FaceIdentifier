/*
 * Classifier.h
 *
 *  Created on: Dec 6, 2016
 *      Author: ubuntu
 */

#ifndef FEATUREEXTRACTORTRAIN_H_
#define FEATUREEXTRACTORTRAIN_H_
#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/net.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/db.hpp"
#include "caffe/util/format.hpp"
#include "caffe/util/io.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace caffe;
using std::string;

class FeatureExtractorVGG {
public:
    FeatureExtractorVGG(const string& model_file, const string& trained_file);
    FeatureExtractorVGG() {}
    std::string GetFeaturesTrain(const cv::Mat& img, int sampel_id);
    const float* GetFeaturesDeploy(const cv::gpu::GpuMat& img);
    bool LoadModel(const string& model_file, const string& trained_file) ;

private:
	template<typename Dtype>
	std::string Predict(const cv::gpu::GpuMat& img, int sampel_id);

	void WrapInputLayer(std::vector<cv::gpu::GpuMat>* input_channels);

	void Preprocess(const cv::gpu::GpuMat& img,
			std::vector<cv::gpu::GpuMat>* input_channels);

private:
	shared_ptr<Net<float> > net_;
	cv::Size input_geometry_;
	int num_channels_;
	cv::gpu::GpuMat mean_;

};

#endif /* FEATUREEXTRACTORTRAIN_H_ */
