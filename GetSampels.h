/*
 * GetSampels.h

 *
 *  Created on: Jan 31, 2017
 *      Author: pouya
 */

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_transforms/draw_abstract.h>
#include <dlib/gui_widgets.h>
#include <dlib/opencv/to_open_cv.h>
#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <dlib/dnn/gpu_data.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "FeatureExtractorVGG.h"
#include "PoseEstimator.h"
#include "SystemSetting.h"

#ifndef GETSAMPELS_H_
#define GETSAMPELS_H_

namespace FaceIdentifierSystem {

class GetSampels {
public:
    GetSampels(FaceIdentifierSystem::SystemSetting * system_setting);
	bool AddSubject(int sampel_id,std::string first_name,std::string last_name,bool equalize,bool save_images) ;
	bool AddSamplesFormFile(std::string file_path) ;
	bool AddLabelsFormFile(std::string file_path) ;
	std::vector<std::string> GetAllLabels() ;
    int GetLastID() ;
	bool DeleteAllSampels() ;
	~GetSampels();
private:
    FaceIdentifierSystem::SystemSetting * settings ;
	bool AddLabel(int sampel_id,std::string first_name,std::string last_name,cv::Mat sample_img) ;
	cv::Mat equalizeIntensity(const cv::Mat& inputImage) ;
	double blurriness(cv::Mat area) ;
	bool SaveSamples(int sampel_id) ;
	bool ExtractFeatures(int sampel_id) ;


	std::vector<cv::Mat> head_images ;
    std::vector<cv::Point> head_points_positions = {
    									  cv::Point(25,140),
    									  cv::Point(52,140),
										  cv::Point(80,140),

										  cv::Point(112,140),

										  cv::Point(148,140),
										  cv::Point(177,140),
										  cv::Point(202,140),

										  cv::Point(112,13),
										  cv::Point(112,53),
										  cv::Point(112,95),

										  cv::Point(112,185),
										  cv::Point(112,224),
										  cv::Point(112,266),

										  cv::Point(148,95),
										  cv::Point(177,64),
										  cv::Point(202,28),

										  cv::Point(80,95),
										  cv::Point(52,64),
										  cv::Point(25,28),
    } ;
    std::vector<int> head_points_values = {
    		//right left
			  -30,  -20, -10,   0,   10,  20,  30,
			   // up down
			  -21, -14,-7,  10 , 17 , 25,
			   // rotate
			   10,  20 ,30 ,-10,  -20,  -30
    } ;
};

} /* namespace FaceIdentifierSystem */

#endif /* GETSAMPELS_H_ */
