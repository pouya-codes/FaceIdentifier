/*
 * Classifier.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: ubuntu
 */

#include "FeatureExtractorVGG.h"

FeatureExtractorVGG::FeatureExtractorVGG(const string& model_file,
		const string& trained_file) {

	Caffe::set_mode(Caffe::GPU);

	/* Load the network. */
	net_.reset(new Net<float>(model_file, TEST));
	net_->CopyTrainedLayersFrom(trained_file);

	CHECK_EQ(net_->num_inputs(), 1)<< "Network should have exactly one input.";
	CHECK_EQ(net_->num_outputs(), 1)<< "Network should have exactly one output.";

	Blob<float>* input_layer = net_->input_blobs()[0];
	num_channels_ = input_layer->channels();

	CHECK(num_channels_ == 3 || num_channels_ == 1)
																<< "Input layer should have 1 or 3 channels.";
	input_geometry_ = cv::Size(input_layer->width(), input_layer->height());

	cv::Scalar channel_mean(129, 105, 94, 0);
	mean_ = cv::gpu::GpuMat(input_geometry_, CV_32FC3, channel_mean);



}


const float* FeatureExtractorVGG::GetFeaturesDeploy(const cv::gpu::GpuMat& img){
    Blob<float>* input_layer = net_->input_blobs()[0];
    input_layer->Reshape(1, num_channels_, input_geometry_.height,
            input_geometry_.width);
    /* Forward dimension change to all layers. */
    net_->Reshape();

    std::vector<cv::gpu::GpuMat> input_channels;

    WrapInputLayer(&input_channels);

    Preprocess(img, &input_channels);

    net_->Forward();

    const boost::shared_ptr<caffe::Blob<float> > feature_blob =
            net_->blob_by_name("fc7");
    const float* feature_blob_data;

    feature_blob_data = feature_blob->gpu_data() + feature_blob->offset(0);

    return feature_blob_data;
}

std::string FeatureExtractorVGG::GetFeaturesTrain(const cv::Mat& img,
		int sampel_id) {
	cv::gpu::GpuMat gpu_img;
	gpu_img.upload(img);
	return Predict<float>(gpu_img, sampel_id);
}

template<typename Dtype>
std::string FeatureExtractorVGG::Predict(const cv::gpu::GpuMat& img,
		int sampel_id) {

	Blob<float>* input_layer = net_->input_blobs()[0];
	input_layer->Reshape(1, num_channels_, input_geometry_.height,
			input_geometry_.width);
	/* Forward dimension change to all layers. */
	net_->Reshape();

	std::vector<cv::gpu::GpuMat> input_channels;

	WrapInputLayer(&input_channels);

	Preprocess(img, &input_channels);

	net_->Forward();

	//*******************Features

	Datum datum;

	const boost::shared_ptr<caffe::Blob<Dtype> > feature_blob =
			net_->blob_by_name("fc7");

	int dim_features = feature_blob->count();
	const Dtype* feature_blob_data;

//    std::cout << "height = " << feature_blob->height() << " width = " << feature_blob->width()<< " channels = " << feature_blob->channels() << std::endl;
//    exit(-1);

	datum.set_height(feature_blob->height());
	datum.set_width(feature_blob->width());
	datum.set_channels(feature_blob->channels());
	datum.set_label(sampel_id);
	datum.clear_data();
	datum.clear_float_data();
	feature_blob_data = feature_blob->cpu_data() + feature_blob->offset(0);
	for (int d = 0; d < dim_features; ++d) {
		datum.add_float_data(feature_blob_data[d]);
	}

	//*******************Features

	return datum.SerializeAsString();
}

void FeatureExtractorVGG::WrapInputLayer(
		std::vector<cv::gpu::GpuMat>* input_channels) {
	Blob<float>* input_layer = net_->input_blobs()[0];

	int width = input_layer->width();
	int height = input_layer->height();
	float* input_data = input_layer->mutable_gpu_data();
	for (int i = 0; i < input_layer->channels(); ++i) {
		cv::gpu::GpuMat channel(height, width, CV_32FC1, input_data);
		input_channels->push_back(channel);
		input_data += width * height;
	}
}

void FeatureExtractorVGG::Preprocess(const cv::gpu::GpuMat& img,
		std::vector<cv::gpu::GpuMat>* input_channels) {
	/* Convert the input image to the input image format of the network. */
	cv::gpu::GpuMat sample;
	if (img.channels() == 3 && num_channels_ == 1)
		cv::gpu::cvtColor(img, sample, cv::COLOR_BGR2GRAY);
	else if (img.channels() == 4 && num_channels_ == 1)
		cv::gpu::cvtColor(img, sample, cv::COLOR_BGRA2GRAY);
	else if (img.channels() == 4 && num_channels_ == 3)
		cv::gpu::cvtColor(img, sample, cv::COLOR_BGRA2BGR);
	else if (img.channels() == 1 && num_channels_ == 3)
		cv::gpu::cvtColor(img, sample, cv::COLOR_GRAY2BGR);
	else
		sample = img;

	cv::gpu::GpuMat sample_resized;
	if (sample.size() != input_geometry_)
		cv::gpu::resize(sample, sample_resized, input_geometry_);
	else
		sample_resized = sample;

	cv::gpu::GpuMat sample_float;
	if (num_channels_ == 3)
		sample_resized.convertTo(sample_float, CV_32FC3);
	else
		sample_resized.convertTo(sample_float, CV_32FC1);

	cv::gpu::GpuMat sample_normalized;
	cv::gpu::subtract(sample_float, mean_, sample_normalized);

	cv::gpu::split(sample_normalized, *input_channels);

}
bool FeatureExtractorVGG::LoadModel(const string& model_file, const string& trained_file) {
    Caffe::set_mode(Caffe::GPU);

    /* Load the network. */
    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);

    CHECK_EQ(net_->num_inputs(), 1)<< "Network should have exactly one input.";
    CHECK_EQ(net_->num_outputs(), 1)<< "Network should have exactly one output.";

    Blob<float>* input_layer = net_->input_blobs()[0];
    num_channels_ = input_layer->channels();
    CHECK(num_channels_ == 3 || num_channels_ == 1)
                                                                << "Input layer should have 1 or 3 channels.";
    input_geometry_ = cv::Size(input_layer->width(), input_layer->height());


    cv::Scalar channel_mean(129, 105, 94, 0);
    mean_ = cv::gpu::GpuMat(input_geometry_, CV_32FC3, channel_mean);



    Blob<float>* output_layer = net_->output_blobs()[0];

    return true ;
}
