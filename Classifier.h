/*
 * Classifier.h
 *
 *  Created on: Feb 2, 2017
 *      Author: pouya
 */

#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include <caffe/caffe.hpp>
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
#include <SystemSetting.h>
using namespace caffe;
using std::string;


namespace FaceIdentifierSystem {
typedef std::pair<int, float> Prediction;
static bool PairCompare(const std::pair<float, int>& lhs,
        const std::pair<float, int>& rhs) {
    return lhs.first > rhs.first;
}

class Classifier {
public:
    int TrainClassifier(int number_of_samples) ;
	Classifier();
    int LoadModel (const string& model_file, const string& trained_file) ;
    Prediction Classify(const float* features);
private:
    FaceIdentifierSystem::SystemSetting * settings ;
    std::vector<int> Argmax(const std::vector<float>& v, int N) ;
    shared_ptr<Net<float> > net_;

};

} /* namespace FaceIdentifierSystem */

#endif /* CLASSIFIER_H_ */
