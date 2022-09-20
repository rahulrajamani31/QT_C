#include "dicomwidget.h"
#include "ui_dicomwidget.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeWidgetItem>
#include <QMimeDatabase>


DicomWidget::DicomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DicomWidget)
{
    ui->setupUi(this);

}

void DicomWidget::setImage(const QString &text , const QString label) {
   // ui->diWidget->setImage(text);
    std::string fileDICOM = text.toUtf8().constData();
      ui->diLabel->setText(label);
      ui->diWidget->setWhatsThis(text);
    qDebug()<<"My path"<< text;
    vtkSmartPointer<vtkDICOMImageReader> reader =
        vtkSmartPointer<vtkDICOMImageReader>::New();
      reader->SetFileName(fileDICOM.c_str());
      reader->Update();

      vtkSmartPointer<vtkImageViewer2> imageViewer =
        vtkSmartPointer<vtkImageViewer2>::New();
      imageViewer->SetInputConnection(reader->GetOutputPort());
      imageViewer->SetRenderWindow(ui->diWidget->GetRenderWindow());
      imageViewer->Render();
}

QString DicomWidget::getText() {
    return ui->diWidget->whatsThis();
}

DicomWidget::~DicomWidget()
{
    delete ui;
}
