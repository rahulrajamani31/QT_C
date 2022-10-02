#ifndef DICOMWIDGET_H
#define DICOMWIDGET_H


#include <QWidget>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <QDebug>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeWidgetItem>
#include <QMimeDatabase>
#include "editwindow.h"

namespace Ui {
class DicomWidget;
}

class DicomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DicomWidget(QWidget *parent = nullptr);
    ~DicomWidget();
    void setImage(const QString &text ,const QString label,const bool isTrue);
     QString getImage();
      void mouseDoubleClickEvent(QMouseEvent *event);
    QString getText();

private slots:


private:
    Ui::DicomWidget *ui;
  EditWindow * editWindow();

};

#endif // DICOMWIDGET_H
