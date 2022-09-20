/********************************************************************************
** Form generated from reading UI file 'dicomwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICOMWIDGET_H
#define UI_DICOMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <qvtkwidget.h>

QT_BEGIN_NAMESPACE

class Ui_DicomWidget
{
public:
    QLabel *diLabel;
    QVTKWidget *diWidget;

    void setupUi(QWidget *DicomWidget)
    {
        if (DicomWidget->objectName().isEmpty())
            DicomWidget->setObjectName(QString::fromUtf8("DicomWidget"));
        DicomWidget->resize(259, 214);
        diLabel = new QLabel(DicomWidget);
        diLabel->setObjectName(QString::fromUtf8("diLabel"));
        diLabel->setGeometry(QRect(50, 170, 49, 16));
        diWidget = new QVTKWidget(DicomWidget);
        diWidget->setObjectName(QString::fromUtf8("diWidget"));
        diWidget->setGeometry(QRect(20, 10, 211, 141));

        retranslateUi(DicomWidget);

        QMetaObject::connectSlotsByName(DicomWidget);
    } // setupUi

    void retranslateUi(QWidget *DicomWidget)
    {
        DicomWidget->setWindowTitle(QCoreApplication::translate("DicomWidget", "Form", nullptr));
        diLabel->setText(QCoreApplication::translate("DicomWidget", "imageLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DicomWidget: public Ui_DicomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICOMWIDGET_H
