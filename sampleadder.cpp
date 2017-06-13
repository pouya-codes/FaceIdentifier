#include "sampleadder.h"
#include "ui_sampleadder.h"
#include "GetSampels.h"
#include "QMessageBox"

SampleAdder::SampleAdder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SampleAdder)

{
    ui->setupUi(this);
}

SampleAdder::~SampleAdder()
{
    delete ui;
}

void SampleAdder::on_pushButton_addSampleCancel_clicked()
{

    close() ;
}

void SampleAdder::setSetting(FaceIdentifierSystem::SystemSetting * system_setting)  {
    this->settings = system_setting ;
    FaceIdentifierSystem::GetSampels getsampel(settings) ;
    int id = getsampel.GetLastID() ;
    ui->lineEdit_id->setText( QString::number(id));
}

void SampleAdder::on_pushButton_addSampleTakeSamples_clicked()
{
    FaceIdentifierSystem::GetSampels getsampel(settings) ;

    if(getsampel.AddSubject(getsampel.GetLastID(),ui->lineEdit_name->text().toStdString(),ui->lineEdit_2->text().toStdString(),true,true)){
        QMessageBox::information(this,"عملیات موفق","فرد جدید با موفقیت افزوده شد") ;
        ui->lineEdit_id->setText( QString::number(getsampel.GetLastID()));
        ui->lineEdit_name->setText("");
        ui->lineEdit_2->setText(""); ;
    }
    else {
        QMessageBox::critical(this,"عملیات ناموفق","نمونه برداری توسط کاربر متوقف شد.") ;
    }

}
