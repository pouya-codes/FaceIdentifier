#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include "sampleadder.h"
#include "SystemSetting.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_addNewPerson_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_runFaceIdentifier_clicked();

    void on_pushButton_runFaceTracker_clicked();

    void on_pushButton_trainClassifier_clicked();

    void on_pushButton_setting_clicked();

private:
    int RunIdentifierGraph() ;
    Ui::MainWindow *ui;
    std::shared_ptr<SampleAdder> sampleAdder ;
    std::shared_ptr<FaceIdentifierSystem::SystemSetting> settings ;
};

#endif // MAINWINDOW_H
