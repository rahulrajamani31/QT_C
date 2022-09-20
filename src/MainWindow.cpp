#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeWidgetItem>
#include <QMimeDatabase>
#include <QDebug>
#include "dicomwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    viewer = vtkSmartPointer<vtkImageViewer2>::New();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openDICOMFolder() {
    QString folderNameDICOM = QFileDialog::getExistingDirectory(this, tr("Open DICOM Folder"), QDir::currentPath(), QFileDialog::ShowDirsOnly);
    drawDICOMSeries(folderNameDICOM.toUtf8().constData());
    qDebug() << "Starts here" << "\n";
}

void MainWindow::drawDICOMSeries(std::string folderDICOM) {
      ui->listWidget->clear();
    currentFolder = QString::fromStdString(folderDICOM);
    QDir directory(currentFolder);
    QFileInfoList images = directory.entryInfoList(QStringList() << "*.dcm" << "*.DCM",QDir::Files);
    foreach(QFileInfo filename, images) {
      qDebug() << filename.filePath() << "\n";
      auto item = new QListWidgetItem();

      auto widget = new DicomWidget(this);

      widget->setImage(filename.filePath() , filename.fileName() );
     ui->listWidget->setFlow(QListView::Flow::LeftToRight);
//      item->set SizeHint(widget->sizeHint());
      item->setSizeHint(QSize(300, widget->sizeHint().height()));
      ui->listWidget->addItem(item);
      ui->listWidget->setSizeIncrement(200, 200);
      ui->listWidget->setItemWidget(item, widget);
    }

    QFileSystemModel *dirModel = new QFileSystemModel(); //Create new model
    dirModel->setRootPath(currentFolder); //Set model path

    ui->treeView->setModel(dirModel); //Add model to QTreeView
    QModelIndex idx = dirModel->index(currentFolder); //Set the root item
    ui->treeView->setRootIndex(idx);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);

    ui->treeView->hideColumn(3);
    currentFileDI = dirModel->filePath(idx);
    reader->SetDirectoryName(folderDICOM.c_str());
    reader->Update();
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &MainWindow::currentChanged);
}



void MainWindow::drawDICOMImg(std::string fileDICOM)
{
    vtkSmartPointer<vtkDICOMImageReader> reader =
        vtkSmartPointer<vtkDICOMImageReader>::New();
      reader->SetFileName(fileDICOM.c_str());
      reader->Update();

      vtkSmartPointer<vtkImageViewer2> imageViewer =
        vtkSmartPointer<vtkImageViewer2>::New();
      imageViewer->SetInputConnection(reader->GetOutputPort());
      imageViewer->SetRenderWindow(ui->qvtkWidget->GetRenderWindow());
      imageViewer->Render();
}

void MainWindow::currentChanged(const QModelIndex &index)
{

    QFileSystemModel* fileSystem = new QFileSystemModel();
    QFileInfo myPath = fileSystem->fileInfo(index);

    std::string fileDICOM = myPath.filePath().toUtf8().constData();

    qDebug()<<"My path"<< myPath;
    vtkSmartPointer<vtkDICOMImageReader> reader =
        vtkSmartPointer<vtkDICOMImageReader>::New();
      reader->SetFileName(fileDICOM.c_str());
      reader->Update();

      vtkSmartPointer<vtkImageViewer2> imageViewer =
        vtkSmartPointer<vtkImageViewer2>::New();
      imageViewer->SetInputConnection(reader->GetOutputPort());
      imageViewer->SetRenderWindow(ui->qvtkWidget->GetRenderWindow());

      imageViewer->Render();

}

void MainWindow::on_pushButton_clicked()
{
       openDICOMFolder();
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    auto item = ui->listWidget->currentItem();
    auto itemWidget = dynamic_cast<DicomWidget*>(ui->listWidget->itemWidget(item));
    qDebug() << itemWidget->getText() ;
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

