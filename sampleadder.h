#ifndef SAMPLEADDER_H
#define SAMPLEADDER_H

#include <QDialog>
#include <SystemSetting.h>
namespace Ui {
class SampleAdder;
}

class SampleAdder : public QDialog
{
    Q_OBJECT

public:
    void setSetting(FaceIdentifierSystem::SystemSetting * system_setting) ;
    explicit SampleAdder(QWidget *parent = 0);
    ~SampleAdder();

private slots:
    void on_pushButton_addSampleCancel_clicked();

    void on_pushButton_addSampleTakeSamples_clicked();

private:
    Ui::SampleAdder *ui;
    FaceIdentifierSystem::SystemSetting * settings ;

};

#endif // SAMPLEADDER_H
