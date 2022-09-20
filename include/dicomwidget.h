#ifndef DICOMWIDGET_H
#define DICOMWIDGET_H

#include <QWidget>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

namespace Ui {
class DicomWidget;
}

class DicomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DicomWidget(QWidget *parent = nullptr);
    ~DicomWidget();
    void setImage(const QString &text ,const QString label);
     QString getImage();
    QString getText();

private:
    Ui::DicomWidget *ui;

};

#endif // DICOMWIDGET_H
