/*
 * GetSampels.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: pouya
 */

#include "GetSampels.h"


namespace FaceIdentifierSystem {


GetSampels::GetSampels(FaceIdentifierSystem::SystemSetting * system_setting) {
    this->settings = system_setting ;
    if(!boost::filesystem::exists(this->settings->getGetSamplesImageSamplePath())) {
        boost::filesystem::create_directory(this->settings->getGetSamplesImageSamplePath()) ;
    }

}

//void callbackButton2(int state, void *pointer){
//        exit(0);

//}

bool GetSampels::AddSubject(int sampel_id,std::string first_name,std::string last_name,bool equalize,bool save_images) {


    PoseEstimator poseEstimator(this->settings->getGetSamplesNetPosePath(), this->settings->getGetSamplesNetPoseWeights(), this->settings->getGetSamplesNetPoseMeanFile());
    cv::VideoCapture cap(0);
    cap.set(3,1280) ;
    cap.set(4,720);
    if(!cap.isOpened()){
    	std::cout << "could not open the camera source!" << std::endl ;
    	return false ;
    }
    cv::Mat frame,resized,gray_frame,resized_equalized,head_resized;
    dlib::array2d<unsigned char> img_dlib;

    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    cap >> frame;



    cv::Mat head_image = cv::imread(this->settings->getGetSamplesHeadPoseImage());
	cv::resize(head_image,head_resized,cv::Size(),0.35,0.35) ;
    cv::Rect dstRC = cv::Rect(0, 0, head_resized.cols, head_resized.rows);

    std::vector<bool> head_points_status ;
    for (uint i = 0 ; i< head_points_positions.size(); ++i) head_points_status.push_back(false) ;

    std::vector<int> head_points_sampels ;
    for (uint i = 0 ; i< head_points_positions.size(); ++i) head_points_sampels.push_back(0) ;

    bool samples_collected = false ;
    bool start_recording = false ;
    cv::Mat sample_img ;
    cv::namedWindow("Camera View") ;

//    cv::createButton("Camera View", callbackButton2, NULL, CV_PUSH_BUTTON, 0) ;
    for(;;)
    {
        cap >> frame;
        cv::putText(frame,"Sample ID : " + std::to_string(sampel_id) + " " + first_name +" "+ last_name,cv::Point(20,20),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,0,255),2 ) ;
        if(!start_recording) {

            cv::putText(frame,"Click 's' for start samples collection,Click 'q' for exit",cv::Point(20,frame.rows-20),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(255,0,0),2 ) ;
        	imshow("Camera View", frame);
            int k = cv::waitKey(30) ;
            if(k == 's') {
                start_recording = true ;
            }
            if(k == 'q') {
                cv::destroyAllWindows() ;
                break ;
            }
        	continue ;
        }


        cv::cvtColor(frame, gray_frame, CV_BGR2GRAY);
        cv::resize(gray_frame,resized,cv::Size((int) gray_frame.cols/this->settings->getGetSamplesResizeLevel(),(int) gray_frame.rows/this->settings->getGetSamplesResizeLevel())) ;
        cv::equalizeHist(resized,resized_equalized) ;

        dlib::assign_image(img_dlib, dlib::cv_image<unsigned char>(resized_equalized));
        std::vector<dlib::rectangle> dets = detector(img_dlib);

        if(dets.size()==1) {

        int x = dets[0].left() * this->settings->getGetSamplesResizeLevel() ;
        int y = dets[0].top() * this->settings->getGetSamplesResizeLevel() ;
        int width = (dets[0].right() -dets[0].left()) * this->settings->getGetSamplesResizeLevel() ;
        int pad_size = (int) width*this->settings->getGetSamplesImagePadPersent() ;
//            pad_size = 10 ;
        cv::Rect faceArea = cv::Rect(x-pad_size,y-pad_size,width+2*pad_size,width+2*pad_size) ;

        if(faceArea.x<=0 || faceArea.y<=0 || (faceArea.x+faceArea.width>frame.cols)||(faceArea.y+faceArea.height>frame.rows)){
        	imshow("Camera View", frame);
        	cv::waitKey(30) ;
        	continue ;
        }


        cv::Mat facePixels ;
        cv::resize(frame(faceArea),facePixels,cv::Size(this->settings->getGetSamplesNetPoseInputSize(),this->settings->getGetSamplesNetPoseInputSize()))  ;

        float* res =(float*) poseEstimator.Classify(facePixels);

        std::cout << (int) (res[0]*50) << " * " <<(int) (res[1]*50) << " * " << (int) (res[2]*50)   << std::endl ;

        cv::Point3i pose_restlt = cv::Point3i((int) (res[0]*50),(int) (res[1]*50),(int) (res[2]*50)) ;
        if(blurriness(facePixels)<=this->settings->getGetSamplesBlurrinessThreshold())  {
            for (uint idx = 0 ; idx< head_points_positions.size(); ++idx) {


    				if (!head_points_status[idx]) {
    					bool add = false;
                        if (idx < 7	&& pose_restlt.y <= (head_points_values[idx]	+ this->settings->getGetSamplesPositionDifferent())
                                && pose_restlt.y >= (head_points_values[idx] - this->settings->getGetSamplesPositionDifferent()) && (pose_restlt.x<= this->settings->getGetSamplesPositionTolerance()
                                        && pose_restlt.x >= -this->settings->getGetSamplesPositionTolerance() )&& (pose_restlt.z<= this->settings->getGetSamplesPositionTolerance()
                                                && pose_restlt.z >= -this->settings->getGetSamplesPositionTolerance() ))

    						add = true;

                        if ((idx >= 7 && idx <14 )	&& pose_restlt.x <= (head_points_values[idx]	+ this->settings->getGetSamplesPositionDifferent())
                                && pose_restlt.x >= (head_points_values[idx]- this->settings->getGetSamplesPositionDifferent())&& (pose_restlt.y<= this->settings->getGetSamplesPositionTolerance()
                                        && pose_restlt.y >= -this->settings->getGetSamplesPositionTolerance() )&& (pose_restlt.z<= this->settings->getGetSamplesPositionTolerance()
                                                && pose_restlt.z >= -this->settings->getGetSamplesPositionTolerance() ))

    						add = true;

                        if ((idx >= 14 )	&& pose_restlt.z <= (head_points_values[idx]	+ this->settings->getGetSamplesPositionDifferent())
                                && pose_restlt.z >= (head_points_values[idx]- this->settings->getGetSamplesPositionDifferent())&& (pose_restlt.y<= this->settings->getGetSamplesPositionTolerance()
                                        && pose_restlt.y >= -this->settings->getGetSamplesPositionTolerance() )&& (pose_restlt.x<= this->settings->getGetSamplesPositionTolerance()
                                                && pose_restlt.x >= -this->settings->getGetSamplesPositionTolerance() ))

    						add = true;

    					if (add) {
    						head_points_sampels[idx]++;
    						head_images.push_back(equalize ? equalizeIntensity(facePixels) : facePixels);
    						if(idx<7 && sample_img.cols==0) {
    							sample_img = equalizeIntensity(facePixels);
    						}
    						if (head_points_sampels[idx]
                                    == this->settings->getGetSamplesNumberOfEachPositionSampels())
    							head_points_status[idx] = true;
    						break ;
    					}
    				}

            }
        }
        else {
        	std::cout << "blur" << blurriness(facePixels)<< std::endl ;
        }


        cv::rectangle(frame,faceArea,cv::Scalar(0,255,0)) ;
        cv::putText(frame,"Face detected, Press 'q' to exit",cv::Point(20,frame.rows-20),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(255,0,0),2 ) ;

        }
        else if (dets.size()==0) {
        	cv::putText(frame,"No face detected, Press 'q' to exit",cv::Point(20,frame.rows-20),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(255,0,0),2 ) ;
        }
        else {
        	cv::putText(frame,"More than one face detected, Press 'q' to exit",cv::Point(20,frame.rows-20),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(255,0,0),2 ) ;
        }


        cv::Mat dstROI = frame(dstRC);
        head_resized.copyTo(dstROI);
        bool done = true ;
        for (uint idx = 0 ; idx< head_points_positions.size(); ++idx) {
        	done = head_points_status[idx] && done;
        	cv::circle(frame,head_points_positions[idx],5,head_points_status[idx] ? cv::Scalar(0,255,0) : cv::Scalar(0,0,255),-1);
        }
        if(done) {
        	samples_collected=true ;
        	break ;
        }



        imshow("Camera View", frame);
        int key = cv::waitKey(30) ;
        if(key == 'q'){
//        	samples_collected= true ;
        	break;
        }
        else if (key=='c') {
            samples_collected= true ;
            break;
        }
    }
    if(samples_collected){

    	cv::putText(frame,"All Samples Collected! Press any key to continue",cv::Point(20,frame.rows-50),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,255,0),2 ) ;
    	imshow("Camera View", frame);
    	cv::waitKey(0);
    	// save samples to disk
    	if(save_images) {
        	cv::putText(frame,"Saving Samples in disk",cv::Point(20,frame.rows-50),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,255,0),2 ) ;
        	imshow("Camera View", frame);
    		if(SaveSamples(sampel_id)) {
            	cv::putText(frame,"Samples successfully saved",cv::Point(20,frame.rows-80),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,255,0),2 ) ;
            	imshow("Camera View", frame);
    		}
    	}
    	if(ExtractFeatures(sampel_id)){
        	cv::putText(frame,"Features successfully extracted",cv::Point(20,frame.rows-110),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,255,0),2 ) ;
        	imshow("Camera View", frame);
    	}
    	else {
    		return false ;
    	}


        bool temp = AddLabel(sampel_id,first_name,last_name,sample_img) ;
        cv::destroyAllWindows() ;
        return true && temp  ;
    }

    cv::destroyAllWindows() ;
	return false ;
}

bool GetSampels::SaveSamples(int sampel_id) {
    if(!boost::filesystem::exists(this->settings->getGetSamplesSavePathTrainSamples() )) {
        boost::filesystem::create_directory(this->settings->getGetSamplesSavePathTrainSamples() ) ;
	}
    std::string folder_path = this->settings->getGetSamplesSavePathTrainSamples() + std::to_string(sampel_id) + "/" ;
	if(!boost::filesystem::exists(folder_path)) {
		boost::filesystem::create_directory(folder_path) ;
	}
    for (uint idx = 0 ; idx< head_images.size(); ++idx) {
    	std::string file_name = folder_path + std::to_string(idx) + ".jpg";
    	cv::imwrite(file_name,head_images[idx]) ;

    }
	return true ;
}

bool GetSampels::ExtractFeatures(int sampel_id) {
    FeatureExtractorVGG feature_extractor(this->settings->getFeaturesExtractorNetPathVgg(), this->settings->getFeaturesExtractorNetWeightsVgg()) ;
    if(!boost::filesystem::exists(this->settings->getGetSamplesDbPath())) {
        boost::filesystem::create_directory(this->settings->getGetSamplesDbPath()) ;
	}

	boost::shared_ptr<db::DB> db(db::GetDB("lmdb"));

    std::string db_name =this->settings->getGetSamplesDbPath()+"/"+this->settings->getGetSamplesFeaturesDbName() ;

	boost::filesystem::exists(db_name) ? db->Open(db_name, db::WRITE) : db->Open(db_name, db::NEW) ;

	boost::shared_ptr<db::Transaction> txn(db->NewTransaction());

    for (uint idx = 0 ; idx< head_images.size(); ++idx) {
        std::string features  = feature_extractor.GetFeaturesTrain(head_images[idx],sampel_id) ;
    	std::string key = std::to_string(sampel_id) + "_" + std::to_string(idx) ;
    	txn->Put(key , features);
    }

	txn->Commit();
	db->Close();


	return true ;
}

double GetSampels::blurriness(cv::Mat area) {
	cv::Mat Gx, Gy;
	cv::Sobel(area, Gx, CV_32F, 1, 0);
	cv::Sobel(area, Gy, CV_32F, 0, 1);
	double normGx = norm(Gx);
	double normGy = norm(Gy);
	double sumSq = normGx * normGx + normGy * normGy;
	double blur = static_cast<float>(1.
			/ (sumSq / area.size().area() + 1e-6));
	return  blur*1000000 ;
}
cv::Mat GetSampels::equalizeIntensity(const cv::Mat& inputImage) {
			cv::Mat img_ycrcb;
			cv::cvtColor(inputImage, img_ycrcb, CV_BGR2YCrCb);
			vector<cv::Mat> channels;
			cv::split(img_ycrcb, channels);
			cv::equalizeHist(channels[0], channels[0]);
			cv::Mat result_equ;
			merge(channels, img_ycrcb);
			cv::cvtColor(img_ycrcb, result_equ, CV_YCrCb2BGR);

			return result_equ;

}

bool GetSampels::AddSamplesFormFile(std::string file_path) {
    FeatureExtractorVGG feature_extractor(this->settings->getFeaturesExtractorNetPathVgg(), this->settings->getFeaturesExtractorNetWeightsVgg()) ;
    if(!boost::filesystem::exists(this->settings->getGetSamplesDbPath())) {
        boost::filesystem::create_directory(this->settings->getGetSamplesDbPath()) ;
    }
    if(!boost::filesystem::exists("imgs")) {
        boost::filesystem::create_directory("imgs") ;
    }

	boost::shared_ptr<db::DB> db(db::GetDB("lmdb"));

    std::string db_name =this->settings->getGetSamplesDbPath()+"/"+this->settings->getGetSamplesFeaturesDbName() ;

	boost::filesystem::exists(db_name) ? db->Open(db_name, db::WRITE) : db->Open(db_name, db::NEW) ;

	boost::shared_ptr<db::Transaction> txn(db->NewTransaction());


	std::ifstream infile(file_path);
	string file_name, lable;
	int counter = 0 ;
	infile >> file_name >> lable;
	int lab= -1 ;
	do
    {
        std::string temp = "/home/pouya/Develop/caffe/data/final_test/train/" + file_name ;
		if(lab!=std::stoi(lable)) {
			std::cout <<lable << std::endl ;
            boost::filesystem::copy(temp,this->settings->getGetSamplesImageSamplePath()+lable+".jpg") ;
			lab = std::stoi(lable) ;
		}


        std::string features  = feature_extractor.GetFeaturesTrain(cv::imread(temp),std::stoi(lable)) ;

		std::string key = lable + "_" + std::to_string(counter) ;
		txn->Put(key , features);

		counter++ ;
		if (counter % 500 == 0) {
	        txn->Commit();
	        txn.reset(db->NewTransaction());
			std::cout << counter << " samples added" <<std::endl ;
		}


	}while(infile >> file_name >> lable);

	txn->Commit();
	db->Close();
	return true ;
}

bool GetSampels::AddLabelsFormFile(std::string file_path) {

    if(!boost::filesystem::exists(this->settings->getGetSamplesDbPath())) {
        boost::filesystem::create_directory(this->settings->getGetSamplesDbPath()) ;
	}

	boost::shared_ptr<db::DB> db(db::GetDB("lmdb"));

    std::string db_name =this->settings->getGetSamplesDbPath()+"/"+this->settings->getGetSamplesLabelsDbName() ;

	int counter = 0 ;
	if(boost::filesystem::exists(db_name)){
		counter = GetLastID();
		db->Open(db_name, db::WRITE) ;

	} else {
		 db->Open(db_name, db::NEW) ;
	}

	boost::shared_ptr<db::Transaction> txn(db->NewTransaction());


	std::ifstream infile(file_path);
	string first_name, last_name;

	while (infile >> first_name  >> last_name)
	{

		std::string key = std::to_string(counter) ;
		txn->Put(key , first_name + " " +last_name);
		counter++ ;

	}
	std::cout << counter << " samples added" <<std::endl ;
	txn->Commit();
	db->Close();
	return true ;
}

bool GetSampels::AddLabel(int sampel_id,std::string first_name,std::string last_name,cv::Mat sample_img)  {

    cv::imwrite(this->settings->getGetSamplesImageSamplePath()+std::to_string(sampel_id)+".jpg",sample_img) ;
    if(!boost::filesystem::exists(this->settings->getGetSamplesDbPath())) {
        boost::filesystem::create_directory(this->settings->getGetSamplesDbPath()) ;
	}

	boost::shared_ptr<db::DB> db(db::GetDB("lmdb"));

    std::string db_name =this->settings->getGetSamplesDbPath()+"/"+this->settings->getGetSamplesLabelsDbName() ;

	boost::filesystem::exists(db_name) ? db->Open(db_name, db::WRITE) :  db->Open(db_name, db::NEW) ;

	boost::shared_ptr<db::Transaction> txn(db->NewTransaction());

	txn->Put(std::to_string(sampel_id) , first_name + " " +last_name);

	txn->Commit();

	db->Close();

	return true ;
}

int GetSampels::GetLastID() {

    if(!boost::filesystem::exists(this->settings->getGetSamplesDbPath())) return 0 ;
    std::string db_name =this->settings->getGetSamplesDbPath()+"/"+this->settings->getGetSamplesLabelsDbName() ;
	if(!boost::filesystem::exists(db_name)) return 0;

	boost::shared_ptr<db::DB> db(db::GetDB("lmdb"));

	int counter = 0 ;
	db->Open(db_name, db::READ) ;
    boost::shared_ptr<db::Cursor> cursor_read(db->NewCursor());

	while(cursor_read->valid()) {
//		std::cout << cursor_read->key() << " - "<<cursor_read->value() << std::endl ;
		cursor_read->Next() ;
		counter++ ;
	}
	cursor_read->~Cursor() ;
	db->Close();
	return counter ;
}

std::vector<std::string> GetSampels::GetAllLabels() {

	std::vector<std::string> Labels ;
    if(!boost::filesystem::exists(this->settings->getGetSamplesDbPath())) return Labels ;
    std::string db_name =this->settings->getGetSamplesDbPath()+"/"+this->settings->getGetSamplesLabelsDbName() ;
	if(!boost::filesystem::exists(db_name)) return Labels;
	int last_id = GetLastID() ;
	std::string myArray[last_id];

	boost::shared_ptr<db::DB> db(db::GetDB("lmdb"));


	db->Open(db_name, db::READ) ;
	boost::shared_ptr<db::Cursor> cursor_read(db->NewCursor());

	while(cursor_read->valid()) {
		myArray[std::stoi(cursor_read->key())] = cursor_read->value() ;
		cursor_read->Next() ;

	}
	cursor_read->~Cursor() ;
	db->Close();
	for (int idx = 0; idx < last_id; ++idx) {
		Labels.push_back(myArray[idx]) ;
	}
	return Labels ;

}
bool GetSampels::DeleteAllSampels() {
    if(boost::filesystem::exists(this->settings->getGetSamplesDbPath())) boost::filesystem::remove_all(this->settings->getGetSamplesDbPath());
    if(boost::filesystem::exists(this->settings->getGetSamplesImageSamplePath())) boost::filesystem::remove_all(this->settings->getGetSamplesImageSamplePath());

	return true ;
}

GetSampels::~GetSampels() {
	// TODO Auto-generated destructor stub
}

} /* namespace FaceIdentifierSystem */
