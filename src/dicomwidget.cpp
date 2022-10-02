#include "dicomwidget.h"
#include "ui_dicomwidget.h"



DicomWidget::DicomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DicomWidget)
{
    ui->setupUi(this);

}

void DicomWidget::setImage(const QString &text , const QString label , const bool isTrue) {
   // ui->diWidget->setImage(text);
     std::string fileDICOM = text.toUtf8().constData();
    if(isTrue){
        ui->diLabel->setText("Single view - " +label);
    }
    else{
        ui->diLabel->setText("Multi view - " +label);
    }


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

void DicomWidget::mouseDoubleClickEvent(QMouseEvent *event){
    qDebug() << ui->diWidget->whatsThis();
    QString path = ui->diWidget->whatsThis();
    EditWindow * editWindow = new EditWindow(this);
    editWindow->setWindowTitle(path);
    editWindow->setWhatsThis(path);
    editWindow->show();
}

DicomWidget::~DicomWidget()
{
    delete ui;
}



