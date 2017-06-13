#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sampleadder.h"
#include "QMessageBox"
#include "GetSampels.h"
#include <iostream>
#include <TrainClassifier.h>
#include <GetSampels.h>
#include <SystemSetting.h>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = std::make_shared<FaceIdentifierSystem::SystemSetting>() ;

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_addNewPerson_clicked()
{
//    SampleAdder sampleAdder ;
//    sampleAdder.setModal(true);
//    sampleAdder.exec();

    sampleAdder = std::make_shared<SampleAdder>(this) ;
    sampleAdder->setSetting(this->settings.get());
    sampleAdder->show();

}

void MainWindow::on_pushButton_exit_clicked()
{
    QApplication::quit() ;
}

void MainWindow::on_pushButton_runFaceIdentifier_clicked()


{


    QProcess::execute("/home/pouya/Develop/workspace/Graph_Based/src/Identifier");


}

void MainWindow::on_pushButton_runFaceTracker_clicked()
{

    QProcess::execute("/home/pouya/Develop/workspace/Graph_Based/src/Tracker");


}

void MainWindow::on_pushButton_trainClassifier_clicked()
{
    ui->statusBar->showMessage("طبقه بند در حال آموزش است...");

    FaceIdentifierSystem::TrainClassifier trainClassifier(this->settings.get()) ;
    FaceIdentifierSystem::GetSampels sampels(settings.get()) ;

    trainClassifier.RunTrainClassifier(sampels.GetLastID())==0 ?
                QMessageBox::information(this ,"آموزش طبقه بند","طبقه بند با موفقیت آموزش داده شد.") :
                QMessageBox::critical(this ,"آموزش طبقه بند","خطایی در آموزش طبقه بند رخ داده است.") ;
    ui->statusBar->showMessage("");
}












void MainWindow::on_pushButton_setting_clicked()
{
    FaceIdentifierSystem::GetSampels sampels(settings.get()) ;
    sampels.DeleteAllSampels();
    sampels.AddSamplesFormFile("/home/pouya/Develop/caffe/data/final_test/train_49.txt") ;
    sampels.AddLabelsFormFile("/home/pouya/Develop/caffe/data/final_test/labels_49.txt") ;

}
