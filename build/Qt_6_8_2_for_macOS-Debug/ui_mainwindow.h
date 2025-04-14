/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *imageLabel;
    QVBoxLayout *verticalLayout;
    QPushButton *play;
    QPushButton *Tutorial;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(180, 50, 421, 411));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        imageLabel = new QLabel(widget);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setScaledContents(true);

        verticalLayout_2->addWidget(imageLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        play = new QPushButton(widget);
        play->setObjectName("play");
        QFont font;
        font.setFamilies({QString::fromUtf8("SF Pro Display")});
        font.setBold(true);
        font.setKerning(false);
        play->setFont(font);
        play->setAutoFillBackground(false);
        play->setStyleSheet(QString::fromUtf8(""));
        play->setIconSize(QSize(10, 16));

        verticalLayout->addWidget(play);

        Tutorial = new QPushButton(widget);
        Tutorial->setObjectName("Tutorial");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("SF Pro Rounded")});
        font1.setBold(true);
        Tutorial->setFont(font1);

        verticalLayout->addWidget(Tutorial);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 43));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        imageLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        play->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        Tutorial->setText(QCoreApplication::translate("MainWindow", "Tutorial", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
