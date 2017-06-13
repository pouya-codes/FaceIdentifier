/*
 * SystemSetting.h
 *
 *  Created on: Feb 2, 2017
 *      Author: pouya
 */

#ifndef SYSTEMSETTING_H_
#define SYSTEMSETTING_H_
#include <iostream>
namespace FaceIdentifierSystem {

class SystemSetting {
public:
	SystemSetting(){

	}

	const std::string& getClassifierDeployFilePath() const {
		return CLASSIFIER_DEPLOY_FILE_PATH;
	}

	const std::string& getClassifierModelPath() const {
		return CLASSIFIER_MODEL_PATH;
	}

	const std::string& getClassifierSolverFilePath() const {
		return CLASSIFIER_SOLVER_FILE_PATH;
	}

	const std::string& getClassifierTrainFilePath() const {
		return CLASSIFIER_TRAIN_FILE_PATH;
	}

	const std::string& getFaceIdentifierCascadeFilePath() const {
		return Face_Identifier_CASCADE_FILE_PATH;
	}

	void setFaceIdentifierCascadeFilePath(
			const std::string& faceIdentifierCascadeFilePath =
					"model/haarcascade_frontalface_alt2.xml") {
		Face_Identifier_CASCADE_FILE_PATH = faceIdentifierCascadeFilePath;
	}

	double getFaceIdentifierImagePadPersentDeploy() const {
		return Face_Identifier_IMAGE_PAD_PERSENT_DEPLOY;
	}

	void setFaceIdentifierImagePadPersentDeploy(
			double faceIdentifierImagePadPersentDeploy = 0.05) {
		Face_Identifier_IMAGE_PAD_PERSENT_DEPLOY =
				faceIdentifierImagePadPersentDeploy;
	}

	int getFaceIdentifierMaxFaceDetect() const {
		return Face_Identifier_MAX_FACE_DETECT;
	}

	void setFaceIdentifierMaxFaceDetect(int faceIdentifierMaxFaceDetect = 10) {
		Face_Identifier_MAX_FACE_DETECT = faceIdentifierMaxFaceDetect;
	}

	const std::string& getFaceIdentifierMlpPath() const {
		return Face_Identifier_MLP_PATH;
	}

	void setFaceIdentifierMlpPath(const std::string& faceIdentifierMlpPath =
			"model/mlp_weights.xmls") {
		Face_Identifier_MLP_PATH = faceIdentifierMlpPath;
	}

	const std::string& getFaceIdentifierNetPathClassifier() const {
		return Face_Identifier_NET_PATH_CLASSIFIER;
	}

	const std::string& getFaceIdentifierNetWeightsClassifier() const {
		return Face_Identifier_NET_WEIGHTS_CLASSIFIER;
	}

	void setFaceIdentifierNetWeightsClassifier(
			const std::string& faceIdentifierNetWeightsClassifier =
					"model/classifier/classifier_layer_iter_100.caffemodel") {
		Face_Identifier_NET_WEIGHTS_CLASSIFIER =
				faceIdentifierNetWeightsClassifier;
	}

	int getFaceIdentifierResizeLevelDeploy() const {
		return Face_Identifier_RESIZE_LEVEL_DEPLOY;
	}

	void setFaceIdentifierResizeLevelDeploy(
			int faceIdentifierResizeLevelDeploy = 3) {
		Face_Identifier_RESIZE_LEVEL_DEPLOY = faceIdentifierResizeLevelDeploy;
	}

	int getFaceIdentifierRoiEndX() const {
		return Face_Identifier_ROI_END_X;
	}

	void setFaceIdentifierRoiEndX(int faceIdentifierRoiEndX = 1280) {
		Face_Identifier_ROI_END_X = faceIdentifierRoiEndX;
	}

	int getFaceIdentifierRoiEndY() const {
		return Face_Identifier_ROI_END_Y;
	}

	void setFaceIdentifierRoiEndY(int faceIdentifierRoiEndY = 720) {
		Face_Identifier_ROI_END_Y = faceIdentifierRoiEndY;
	}

	int getFaceIdentifierRoiX() const {
		return Face_Identifier_ROI_X;
	}

	void setFaceIdentifierRoiX(int faceIdentifierRoiX = 0) {
		Face_Identifier_ROI_X = faceIdentifierRoiX;
	}

	int getFaceIdentifierRoiY() const {
		return Face_Identifier_ROI_Y;
	}

	void setFaceIdentifierRoiY(int faceIdentifierRoiY = 0) {
		Face_Identifier_ROI_Y = faceIdentifierRoiY;
	}

	const std::string& getFaceTrackerCascadeFilePath() const {
		return Face_Tracker_CASCADE_FILE_PATH;
	}

	void setFaceTrackerCascadeFilePath(
			const std::string& faceTrackerCascadeFilePath =
					"model/haarcascade_frontalface_alt2.xml") {
		Face_Tracker_CASCADE_FILE_PATH = faceTrackerCascadeFilePath;
	}

	int getFaceTrackerFaceIdentifierRoiEndX() const {
		return Face_Tracker_Face_Identifier_ROI_END_X;
	}

	void setFaceTrackerFaceIdentifierRoiEndX(
			int faceTrackerFaceIdentifierRoiEndX = 1280) {
		Face_Tracker_Face_Identifier_ROI_END_X =
				faceTrackerFaceIdentifierRoiEndX;
	}

	int getFaceTrackerFaceIdentifierRoiEndY() const {
		return Face_Tracker_Face_Identifier_ROI_END_Y;
	}

	void setFaceTrackerFaceIdentifierRoiEndY(
			int faceTrackerFaceIdentifierRoiEndY = 720) {
		Face_Tracker_Face_Identifier_ROI_END_Y =
				faceTrackerFaceIdentifierRoiEndY;
	}

	int getFaceTrackerFaceIdentifierRoiX() const {
		return Face_Tracker_Face_Identifier_ROI_X;
	}

	void setFaceTrackerFaceIdentifierRoiX(
			int faceTrackerFaceIdentifierRoiX = 0) {
		Face_Tracker_Face_Identifier_ROI_X = faceTrackerFaceIdentifierRoiX;
	}

	int getFaceTrackerFaceIdentifierRoiY() const {
		return Face_Tracker_Face_Identifier_ROI_Y;
	}

	void setFaceTrackerFaceIdentifierRoiY(
			int faceTrackerFaceIdentifierRoiY = 0) {
		Face_Tracker_Face_Identifier_ROI_Y = faceTrackerFaceIdentifierRoiY;
	}

	double getFaceTrackerImagePadPersentDeploy() const {
		return Face_Tracker_IMAGE_PAD_PERSENT_DEPLOY;
	}

	void setFaceTrackerImagePadPersentDeploy(
			double faceTrackerImagePadPersentDeploy = 0.05) {
		Face_Tracker_IMAGE_PAD_PERSENT_DEPLOY =
				faceTrackerImagePadPersentDeploy;
	}

	int getFaceTrackerMaxFaceDetect() const {
		return Face_Tracker_MAX_FACE_DETECT;
	}

	void setFaceTrackerMaxFaceDetect(int faceTrackerMaxFaceDetect = 10) {
		Face_Tracker_MAX_FACE_DETECT = faceTrackerMaxFaceDetect;
	}

	const std::string& getFaceTrackerNetPathClassifier() const {
		return Face_Tracker_NET_PATH_CLASSIFIER;
	}

	const std::string& getFaceTrackerNetWeightsClassifier() const {
		return Face_Tracker_NET_WEIGHTS_CLASSIFIER;
	}

	void setFaceTrackerNetWeightsClassifier(
			const std::string& faceTrackerNetWeightsClassifier =
					"model/classifier/classifier_layer_iter_100.caffemodel") {
		Face_Tracker_NET_WEIGHTS_CLASSIFIER = faceTrackerNetWeightsClassifier;
	}

	int getFaceTrackerResizeLevelDeploy() const {
		return Face_Tracker_RESIZE_LEVEL_DEPLOY;
	}

	void setFaceTrackerResizeLevelDeploy(int faceTrackerResizeLevelDeploy = 3) {
		Face_Tracker_RESIZE_LEVEL_DEPLOY = faceTrackerResizeLevelDeploy;
	}

	const std::string& getFaceTrackerFaceIdentifierMlpPath() const {
		return Face_TrackerFace_Identifier_MLP_PATH;
	}

	void setFaceTrackerFaceIdentifierMlpPath(
			const std::string& faceTrackerFaceIdentifierMlpPath =
					"model/mlp_weights.xmls") {
		Face_TrackerFace_Identifier_MLP_PATH = faceTrackerFaceIdentifierMlpPath;
	}

	const std::string& getFeaturesExtractorNetPathVgg() const {
		return FEATURES_EXTRACTOR_NET_PATH_VGG;
	}

	const std::string& getFeaturesExtractorNetWeightsVgg() const {
		return FEATURES_EXTRACTOR_NET_WEIGHTS_VGG;
	}

	int getGetSamplesBlurrinessThreshold() const {
		return GET_SAMPLES_BLURRINESS_THRESHOLD;
	}

	void setGetSamplesBlurrinessThreshold(int getSamplesBlurrinessThreshold =
			300) {
		GET_SAMPLES_BLURRINESS_THRESHOLD = getSamplesBlurrinessThreshold;
	}

	const std::string& getGetSamplesDbPath() const {
		return GET_SAMPLES_DB_PATH;
	}

	const std::string& getGetSamplesFeaturesDbName() const {
		return GET_SAMPLES_FEATURES_DB_NAME;
	}

    const std::string& getGetSamplesHeadPoseImage() const {
		return GET_SAMPLES_HEAD_POSE_IMAGE;
	}

	int getGetSamplesImagePadPersent() const {
		return GET_SAMPLES_IMAGE_PAD_PERSENT;
	}

	void setGetSamplesImagePadPersent(int getSamplesImagePadPersent = 0.05) {
		GET_SAMPLES_IMAGE_PAD_PERSENT = getSamplesImagePadPersent;
	}

	const std::string& getGetSamplesImageSamplePath() const {
		return GET_SAMPLES_IMAGE_SAMPLE_PATH;
	}

	const std::string& getGetSamplesLabelsDbName() const {
		return GET_SAMPLES_LABELS_DB_NAME;
	}

	const int getGetSamplesNetPoseInputSize() const {
		return GET_SAMPLES_NET_POSE_INPUT_SIZE;
	}

	const std::string& getGetSamplesNetPoseMeanFile() const {
		return GET_SAMPLES_NET_POSE_MEAN_FILE;
	}

	const std::string& getGetSamplesNetPosePath() const {
		return GET_SAMPLES_NET_POSE_PATH;
	}

	const std::string& getGetSamplesNetPoseWeights() const {
		return GET_SAMPLES_NET_POSE_WEIGHTS;
	}

	int getGetSamplesNumberOfEachPositionSampels() const {
		return GET_SAMPLES_NUMBER_OF_EACH_POSITION_SAMPELS;
	}

	void setGetSamplesNumberOfEachPositionSampels(
			int getSamplesNumberOfEachPositionSampels = 7) {
		GET_SAMPLES_NUMBER_OF_EACH_POSITION_SAMPELS =
				getSamplesNumberOfEachPositionSampels;
	}

	int getGetSamplesPositionDifferent() const {
		return GET_SAMPLES_POSITION_DIFFERENT;
	}

	void setGetSamplesPositionDifferent(int getSamplesPositionDifferent = 3) {
		GET_SAMPLES_POSITION_DIFFERENT = getSamplesPositionDifferent;
	}

	int getGetSamplesPositionTolerance() const {
		return GET_SAMPLES_POSITION_TOLERANCE;
	}

	void setGetSamplesPositionTolerance(int getSamplesPositionTolerance = 10) {
		GET_SAMPLES_POSITION_TOLERANCE = getSamplesPositionTolerance;
	}

	int getGetSamplesResizeLevel() const {
		return GET_SAMPLES_RESIZE_LEVEL;
	}

	void setGetSamplesResizeLevel(int getSamplesResizeLevel = 2) {
		GET_SAMPLES_RESIZE_LEVEL = getSamplesResizeLevel;
	}

	const std::string& getGetSamplesSavePathTrainSamples() const {
		return GET_SAMPLES_SAVE_PATH_TRAIN_SAMPLES;
	}

private:
// Get_Sample Setting
int GET_SAMPLES_RESIZE_LEVEL = 2 ;
int GET_SAMPLES_IMAGE_PAD_PERSENT = 0.05 ;
const std::string GET_SAMPLES_NET_POSE_PATH = "model/pose/deploy.prototxt" ;
const std::string GET_SAMPLES_NET_POSE_WEIGHTS = "model/pose/68point_dlib_with_pose.caffemodel";
const std::string GET_SAMPLES_NET_POSE_MEAN_FILE =  "model/pose/VGG_mean.binaryproto";
const std::string GET_SAMPLES_HEAD_POSE_IMAGE = "heads.jpg";
const std::string GET_SAMPLES_SAVE_PATH_TRAIN_SAMPLES = "imgs/sampels/" ;
const int GET_SAMPLES_NET_POSE_INPUT_SIZE = 224 ;

int GET_SAMPLES_NUMBER_OF_EACH_POSITION_SAMPELS  = 7 ;
int GET_SAMPLES_POSITION_DIFFERENT =  3 ;
int GET_SAMPLES_POSITION_TOLERANCE = 10 ;
int GET_SAMPLES_BLURRINESS_THRESHOLD = 300 ;
const std::string GET_SAMPLES_DB_PATH = "databases" ;
const std::string GET_SAMPLES_IMAGE_SAMPLE_PATH = "imgs/" ;
const std::string GET_SAMPLES_FEATURES_DB_NAME = "features_db" ;
const std::string GET_SAMPLES_LABELS_DB_NAME = "labels_db" ;

// Features Extracot Setting
const std::string FEATURES_EXTRACTOR_NET_PATH_VGG = "model/vgg/deploy.prototxt" ;
const std::string FEATURES_EXTRACTOR_NET_WEIGHTS_VGG ="model/vgg/VGG_FACE.caffemodel" ;


// TrainNetwork Setting
const std::string CLASSIFIER_MODEL_PATH = "model/classifier/" ;
const std::string CLASSIFIER_SOLVER_FILE_PATH =  "solver.prototxt" ;
const std::string CLASSIFIER_TRAIN_FILE_PATH = "train.prototxt" ;
const std::string CLASSIFIER_DEPLOY_FILE_PATH = "deploy.prototxt" ;

// FaceIdentifier Setting
int Face_Identifier_MAX_FACE_DETECT = 10 ;
int Face_Identifier_RESIZE_LEVEL_DEPLOY = 3 ;
double Face_Identifier_IMAGE_PAD_PERSENT_DEPLOY = 0.05 ;

std::string Face_Identifier_CASCADE_FILE_PATH = "model/haarcascade_frontalface_alt2.xml" ;

const std::string Face_Identifier_NET_PATH_CLASSIFIER = "model/classifier/deploy.prototxt" ;
std::string Face_Identifier_NET_WEIGHTS_CLASSIFIER =	"model/classifier/classifier_layer_iter_100.caffemodel" ;

std::string Face_Identifier_MLP_PATH = "model/mlp_weights.xmls" ;

int Face_Identifier_ROI_X = 0 ;
int Face_Identifier_ROI_Y = 0 ;
int Face_Identifier_ROI_END_X = 1280 ;
int Face_Identifier_ROI_END_Y = 720 ;

// FaceTracker Setting
int Face_Tracker_MAX_FACE_DETECT = 10 ;
int Face_Tracker_RESIZE_LEVEL_DEPLOY = 3 ;
double Face_Tracker_IMAGE_PAD_PERSENT_DEPLOY = 0.05 ;

std::string Face_Tracker_CASCADE_FILE_PATH = "model/haarcascade_frontalface_alt2.xml" ;

const std::string Face_Tracker_NET_PATH_CLASSIFIER = "model/classifier/deploy.prototxt" ;
std::string Face_Tracker_NET_WEIGHTS_CLASSIFIER =	"model/classifier/classifier_layer_iter_100.caffemodel" ;

std::string Face_TrackerFace_Identifier_MLP_PATH = "model/mlp_weights.xmls" ;

int Face_Tracker_Face_Identifier_ROI_X = 0 ;
int Face_Tracker_Face_Identifier_ROI_Y = 0 ;
int Face_Tracker_Face_Identifier_ROI_END_X = 1280 ;
int Face_Tracker_Face_Identifier_ROI_END_Y = 720 ;

};

} /* namespace FaceIdentifierSystem */

#endif /* SYSTEMSETTING_H_ */
