/*
 * TrainClassifier.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: pouya
 */

#include "TrainClassifier.h"

namespace FaceIdentifierSystem {


int TrainClassifier::RunTrainClassifier(int number_of_samples) {
	FLAGS_alsologtostderr = 1;
//	caffe::GlobalInit(&argc, &argv);
	MakeSolverFile();
    MakeTrainNetFile(number_of_samples) ;
    MakeDeployNetFile(number_of_samples) ;
    return TrainNetwork();

}

int TrainClassifier::TrainNetwork() {

    caffe::SolverParameter solver_param;
    caffe::ReadSolverParamsFromTextFileOrDie(
            this->settings->getClassifierModelPath() + this->settings->getClassifierSolverFilePath(),
            &solver_param);

    solver_param.set_device_id(0);
    Caffe::SetDevice(0);
    Caffe::set_mode(Caffe::GPU);

    shared_ptr<caffe::Solver<float> > solver(
            caffe::SolverRegistry<float>::CreateSolver(solver_param));

    std::cout << "Starting Optimization" << std::endl;
    solver->Solve();
    std::cout << "Optimization Done." << std::endl;
    return 0;
}
int TrainClassifier::MakeSolverFile() {
    std::ofstream solver_file(this->settings->getClassifierModelPath() + this->settings->getClassifierSolverFilePath());

    solver_file << "net: \""+this->settings->getClassifierModelPath() + this->settings->getClassifierTrainFilePath()+"\"\n"
            "base_lr: 0.0002\n"
			"lr_policy: \"step\"\n"
			"gamma: 0.1\n"
			"stepsize: 25\n"
			"display: 5\n"
			"max_iter:100\n"
			"snapshot: 200\n"
            "snapshot_prefix: \"" +this->settings->getClassifierModelPath()+"classifier_layer\"\n"
			"momentum: 0.9\n"
			"weight_decay: 0.0005\n"
			"solver_mode: GPU" << std::endl;

	return 0 ;


}
int TrainClassifier::MakeTrainNetFile(int number_of_samples) {
    std::ofstream train_file(this->settings->getClassifierModelPath() + this->settings->getClassifierTrainFilePath());
	train_file<< "layer {\n"
			"  name: \"data\"\n"
			"  type: \"Data\"\n"
			"  top: \"data\"\n"
			"  top: \"label\"\n"
			"  include {\n"
			"    phase: TRAIN\n"
			"  }\n"
			"  data_param {\n"
            "    source: \"/home/pouya/Develop/qt/build-FaceIdentifier-Desktop-Release/databases/features_db\"\n"
			"    batch_size: 4000\n"
			"    backend: LMDB\n"
			"  }\n"
			"}\n"
			"layer {\n"
			"  name: \"fc2\"\n"
			"  type: \"InnerProduct\"\n"
			"  bottom: \"data\"\n"
			"  top: \"fc2\"\n"
			"  inner_product_param {\n"
			"    num_output: " + std::to_string(number_of_samples)+"\n"
			"  }\n"
			"}\n"
			"layer {\n"
			"  name: \"loss\"\n"
			"  type: \"SoftmaxWithLoss\"\n"
			"  bottom: \"fc2\"\n"
			"  bottom: \"label\"\n"
			"  top: \"loss\"\n"
			"}\n"
			"layer {\n"
			"  name: \"accuracy\"\n"
			"  type: \"Accuracy\"\n"
			"  bottom: \"fc2\"\n"
			"  bottom: \"label\"\n"
			"  top: \"accuracy\"\n"
			"}" << std::endl;

	return 0 ;

}
int TrainClassifier::MakeDeployNetFile(int number_of_samples) {
    std::ofstream train_file(this->settings->getClassifierModelPath() + this->settings->getClassifierDeployFilePath());
	train_file<< "name: \"SIMPLE_XOR_NET\"\n"
			"layer {\n"
			"  name: \"data\"\n"
			"  type: \"Input\"\n"
			"  top: \"data\"\n"
			"  input_param { shape: { dim: 1 dim: 4096 } }\n"
			"}\n"
			"layer {\n"
			"  name: \"fc2\"\n"
			"  type: \"InnerProduct\"\n"
			"  bottom: \"data\"\n"
			"  top: \"fc2\"\n"
			"  inner_product_param {\n"
			"    num_output: "+ std::to_string(number_of_samples)+"\n"
			"  }\n"
			"}\n"
			"layer {\n"
			"  name: \"prob\"\n"
			"  type: \"Softmax\"\n"
			"  bottom: \"fc2\"\n"
			"  top: \"prob\"\n"
			"}" << std::endl;

	return 0 ;

}

TrainClassifier::TrainClassifier(FaceIdentifierSystem::SystemSetting * system_setting) {
	// TODO Auto-generated constructor stub
    this->settings=system_setting ;
    if(!boost::filesystem::exists(this->settings->getClassifierModelPath())) {
        boost::filesystem::create_directory(this->settings->getClassifierModelPath()) ;
	}


}

TrainClassifier::~TrainClassifier() {
	// TODO Auto-generated destructor stub
}

} /* namespace FaceIdentifierSystem */
