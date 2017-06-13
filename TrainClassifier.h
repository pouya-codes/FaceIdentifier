/*
 * TrainClassifier.h
 *
 *  Created on: Feb 2, 2017
 *      Author: pouya
 */

#ifndef TRAINCLASSIFIER_H_
#define TRAINCLASSIFIER_H_

#include "SystemSetting.h"

#include <gflags/gflags.h>
#include <glog/logging.h>

#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "boost/algorithm/string.hpp"
#include "caffe/caffe.hpp"
#include "caffe/util/signal_handler.h"
using caffe::Caffe;
using caffe::shared_ptr;

namespace FaceIdentifierSystem {

class TrainClassifier {
public:
    TrainClassifier(FaceIdentifierSystem::SystemSetting * system_setting);
    int RunTrainClassifier(int number_of_samples) ;
	virtual ~TrainClassifier();
private:
    FaceIdentifierSystem::SystemSetting * settings ;
	int MakeSolverFile();
	int MakeTrainNetFile(int number_of_samples) ;
	int MakeDeployNetFile(int number_of_samples) ;
    int TrainNetwork();
};

} /* namespace FaceIdentifierSystem */

#endif /* TRAINCLASSIFIER_H_ */
