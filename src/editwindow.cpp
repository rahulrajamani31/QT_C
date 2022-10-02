#include "editwindow.h"
#include "ui_editwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QFileSystemModel>

EditWindow::EditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
//    QPixmap pix("C:\redo1.png");
//   ui->label_7->setPixmap(pix);
     ui->stackedWidget->setCurrentIndex(0);
    reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    viewer = vtkSmartPointer<vtkImageViewer2>::New();
}

EditWindow::~EditWindow()
{
    delete ui;
}


void EditWindow::on_pushButton_clicked()
{
     currentDicomPath =  EditWindow::windowTitle();

    qDebug() <<"Hello9" << currentDicomPath;
    std::string fileDICOM = currentDicomPath.toUtf8().constData();

          reader->SetFileName(fileDICOM.c_str());
          reader->Update();

          QFile f(currentDicomPath);
          QFileInfo fileInfo(f.fileName());
          QString filename(fileInfo.fileName());
          int lastPoint = filename.lastIndexOf(".");
          QString fileNameNoExt = filename.left(lastPoint);

ui->label_12->setText( fileNameNoExt + " --  DICOM IMAGE");
ui->label_14->setText( fileNameNoExt + " --  DICOM IMAGE");
ui->label_15->setText( "NAME : "+ fileNameNoExt);
//abcd

          vtkSmartPointer<vtkImageViewer2> imageViewer =
            vtkSmartPointer<vtkImageViewer2>::New();

          imageViewer->SetInputConnection(reader->GetOutputPort());
              imageViewer->SetRenderWindow(ui->edit->GetRenderWindow());
//           imageViewer->SetRenderWindow(ui->original->GetRenderWindow());
          imageViewer->Render();
//          viewer->SetRenderWindow(ui->edit->GetRenderWindow());

          viewer->SetRenderWindow(ui->edit->GetRenderWindow());
          viewer->SetInputConnection(reader->GetOutputPort());
          viewer->SetRenderWindow(ui->edit2->GetRenderWindow());
          viewer->Render();

          minSlice = -100;
           maxSlice =viewer->GetColorLevel() + 200;

           // Actualiza labels de la GUI
           ui->horizontalSlider->setMinimum(minSlice);
           ui->horizontalSlider->setMaximum(maxSlice);

}

void EditWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->label_16->setText("ANATOMY : "+ arg1);
}

void EditWindow::on_horizontalSlider_sliderMoved(int position)
{
    viewer->SetColorLevel(position);
    viewer->Render();
}

void EditWindow::on_horizontalSlider_2_actionTriggered(int action)
{
    viewer->SetGlobalWarningDisplay(action);
    viewer->Render();
}



void EditWindow::on_rRotate_clicked()
{
    vtkNew<vtkNamedColors> colors;
        if(angle == 360){
            angle  = 0;
        }else;
      angle+=90;

      qDebug() <<angle<<"angle";

      // Read file
      vtkNew<vtkImageReader2Factory> readerFactory;
      std::string fileDICOM = currentDicomPath.toUtf8().constData();


     // reader.TakeReference(readerFactory->CreateImageReader2(fileDICOM.c_str()));
       reader->SetFileName(fileDICOM.c_str());
      reader->Update();
      double bounds[6];
      reader->GetOutput()->GetBounds(bounds);

      // Rotate about the center of the image
      vtkNew<vtkTransform> transform;

      // Compute the center of the image
      double center[3];
      center[0] = (bounds[1] + bounds[0]) / 2.0;
      center[1] = (bounds[3] + bounds[2]) / 2.0;
      center[2] = (bounds[5] + bounds[4]) / 2.0;

      // Rotate about the center
      transform->Translate(center[0], center[1], center[2]);
      transform->RotateWXYZ(angle, 0, 0, 1);
      transform->Translate(-center[0], -center[1], -center[2]);

      // Reslice does all of the work
      vtkNew<vtkImageReslice> reslice;
      reslice->SetInputConnection(reader->GetOutputPort());
      reslice->SetResliceTransform(transform);
      reslice->SetInterpolationModeToCubic();
      reslice->SetOutputSpacing(reader->GetOutput()->GetSpacing()[0],
                                reader->GetOutput()->GetSpacing()[1],
                                reader->GetOutput()->GetSpacing()[2]);
      reslice->SetOutputOrigin(reader->GetOutput()->GetOrigin()[0],
                               reader->GetOutput()->GetOrigin()[1],
                               reader->GetOutput()->GetOrigin()[2]);
      reslice->SetOutputExtent(
          reader->GetOutput()->GetExtent()); // Use a larger extent than the
                                             // original image's to prevent clipping
      viewer->SetInputConnection(reslice->GetOutputPort());
      vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
      viewer->SetupInteractor(renderWindowInteractor);
      viewer->GetRenderWindow()->SetWindowName("ImageRotate");
      viewer->Render();
      viewer->GetRenderer()->ResetCamera();
      viewer->Render();
      renderWindowInteractor->Start();
      viewer->Render();
}


void EditWindow::on_lRotate_clicked()
{
    vtkNew<vtkNamedColors> colors;
        if(angle == 0){
            angle  = 360;
        }else;
      angle-=90;

      qDebug() <<angle<<"angle";

      // Read file
      vtkNew<vtkImageReader2Factory> readerFactory;
      std::string fileDICOM = currentDicomPath.toUtf8().constData();


     // reader.TakeReference(readerFactory->CreateImageReader2(fileDICOM.c_str()));
       reader->SetFileName(fileDICOM.c_str());
      reader->Update();
      double bounds[6];
      reader->GetOutput()->GetBounds(bounds);

      // Rotate about the center of the image
      vtkNew<vtkTransform> transform;

      // Compute the center of the image
      double center[3];
      center[0] = (bounds[1] + bounds[0]) / 2.0;
      center[1] = (bounds[3] + bounds[2]) / 2.0;
      center[2] = (bounds[5] + bounds[4]) / 2.0;

      // Rotate about the center
      transform->Translate(center[0], center[1], center[2]);
      transform->RotateWXYZ(angle, 0, 0, 1);
      transform->Translate(-center[0], -center[1], -center[2]);

      // Reslice does all of the work
      vtkNew<vtkImageReslice> reslice;
      reslice->SetInputConnection(reader->GetOutputPort());
      reslice->SetResliceTransform(transform);
      reslice->SetInterpolationModeToCubic();
      reslice->SetOutputSpacing(reader->GetOutput()->GetSpacing()[0],
                                reader->GetOutput()->GetSpacing()[1],
                                reader->GetOutput()->GetSpacing()[2]);
      reslice->SetOutputOrigin(reader->GetOutput()->GetOrigin()[0],
                               reader->GetOutput()->GetOrigin()[1],
                               reader->GetOutput()->GetOrigin()[2]);
      reslice->SetOutputExtent(
          reader->GetOutput()->GetExtent()); // Use a larger extent than the
                                             // original image's to prevent clipping

      viewer->SetInputConnection(reslice->GetOutputPort());
      vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
      viewer->SetupInteractor(renderWindowInteractor);

      viewer->GetRenderWindow()->SetWindowName("ImageRotate");
      viewer->Render();
      viewer->GetRenderer()->ResetCamera();
      viewer->Render();

      renderWindowInteractor->Start();

      viewer->Render();
}




//void EditWindow::on_pushButton_4_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(0);
//    viewer->SetRenderWindow(ui->edit->GetRenderWindow());
//    viewer->SetRenderWindow(ui->edit2->GetRenderWindow());
//    viewer->Render();

//}



//void EditWindow::on_pushButton_5_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//    viewer->SetRenderWindow(ui->edit2->GetRenderWindow());
//    viewer->Render();
//}


void EditWindow::on_radioButton_toggled(bool checked)
{
    if(checked){
        ui->stackedWidget->setCurrentIndex(1);
        vtkSmartPointer<vtkImageViewer2> img =
          vtkSmartPointer<vtkImageViewer2>::New();

        img->SetInputConnection(reader->GetOutputPort());
       img->SetRenderWindow(ui->original->GetRenderWindow());
       img->Render();
        viewer->SetRenderWindow(ui->edit2->GetRenderWindow());
        viewer->Render();
    }
    else{
        ui->stackedWidget->setCurrentIndex(0);
        viewer->SetRenderWindow(ui->edit->GetRenderWindow());
    //    viewer->SetRenderWindow(ui->edit2->GetRenderWindow());
        viewer->Render();
    }
}


//void EditWindow::on_pushButton_2_clicked()
//{
//    vtkSmartPointer<vtkTIFFWriter> writer = vtkTIFFWriter::New();
//    vtkRenderWindow *renWin = ui->edit2->GetRenderWindow();
//    vtkWindowToImageFilter *w2img = vtkWindowToImageFilter::New();
//    w2img->SetInput(renWin);
//    writer->SetFileName(qPrintable("filename"));
//    w2img->SetMagnification(10);
//    writer->SetInputConnection(w2img->GetOutputPort());
//    w2img->Modified();
//    writer->Write();
//}






