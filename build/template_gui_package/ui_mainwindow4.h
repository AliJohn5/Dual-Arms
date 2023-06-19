/********************************************************************************
** Form generated from reading UI file 'mainwindow4.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW4_H
#define UI_MAINWINDOW4_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainwindow4.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow4
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    MainWindow4::CustomLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_7;
    QFrame *line_2;
    QLabel *label_4;
    QLineEdit *time_for_all;
    QFrame *line;
    QSplitter *splitter;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *take_first;
    QPushButton *take_second;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPlainTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow4)
    {
        if (MainWindow4->objectName().isEmpty())
            MainWindow4->setObjectName(QString::fromUtf8("MainWindow4"));
        MainWindow4->resize(897, 602);
        MainWindow4->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 74, 135);"));
        centralwidget = new QWidget(MainWindow4);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setHandleWidth(14);
        label = new MainWindow4::CustomLabel(splitter_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"}\n"
""));
        splitter_2->addWidget(label);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"}"));
        splitter_2->addWidget(label_2);
        splitter_3->addWidget(splitter_2);
        layoutWidget = new QWidget(splitter_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_6->addWidget(label_3);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_6->addWidget(lineEdit);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_2);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_7->addWidget(label_4);

        time_for_all = new QLineEdit(layoutWidget);
        time_for_all->setObjectName(QString::fromUtf8("time_for_all"));

        horizontalLayout_7->addWidget(time_for_all);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout_2->addLayout(horizontalLayout_8);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);


        verticalLayout_3->addLayout(verticalLayout_2);

        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_5->addWidget(label_9);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_5->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_4->addWidget(label_11);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_4->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_3->addWidget(label_10);

        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));

        horizontalLayout_3->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        take_first = new QPushButton(layoutWidget1);
        take_first->setObjectName(QString::fromUtf8("take_first"));
        take_first->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-width: 2px;\n"
"border-style: outset;\n"
"border-color:#8E3B35;\n"
"    background-color: #EFF1F0; /* Cornflower blue */\n"
"    color: #000000; /* White */\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;}\n"
"\n"
"QPushButton:hover {\n"
"    background-color:#c74209;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_2->addWidget(take_first);

        take_second = new QPushButton(layoutWidget1);
        take_second->setObjectName(QString::fromUtf8("take_second"));
        take_second->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-width: 2px;\n"
"border-style: outset;\n"
"border-color:#8E3B35;\n"
"    background-color: #EFF1F0; /* Cornflower blue */\n"
"    color: #000000; /* White */\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;}\n"
"\n"
"QPushButton:hover {\n"
"    background-color:#c74209;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_2->addWidget(take_second);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-width: 2px;\n"
"border-style: outset;\n"
"border-color:#8E3B35;\n"
"    background-color: #EFF1F0; /* Cornflower blue */\n"
"    color: #000000; /* White */\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;}\n"
"\n"
"QPushButton:hover {\n"
"    background-color:#c74209;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-width: 2px;\n"
"border-style: outset;\n"
"border-color:#8E3B35;\n"
"    background-color: #EFF1F0; /* Cornflower blue */\n"
"    color: #000000; /* White */\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;}\n"
"\n"
"QPushButton:hover {\n"
"    background-color:#c74209;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-width: 2px;\n"
"border-style: outset;\n"
"border-color:#8E3B35;\n"
"    background-color: #EFF1F0; /* Cornflower blue */\n"
"    color: #000000; /* White */\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;}\n"
"\n"
"QPushButton:hover {\n"
"    background-color:#c74209;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-width: 2px;\n"
"border-style: outset;\n"
"border-color:#8E3B35;\n"
"    background-color: #EFF1F0; /* Cornflower blue */\n"
"    color: #000000; /* White */\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 10px;}\n"
"\n"
"QPushButton:hover {\n"
"    background-color:#c74209;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget1);
        textEdit = new QPlainTextEdit(splitter);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setStyleSheet(QString::fromUtf8("QPlainTextEdit{\n"
"background-color: #EFF1F0;\n"
"color: rgb(0, 0, 0);\n"
"border-width: 2px;\n"
"border-radius: 5px;\n"
"padding: 10px;\n"
"}"));
        splitter->addWidget(textEdit);

        verticalLayout_3->addWidget(splitter);

        splitter_3->addWidget(layoutWidget);

        verticalLayout_4->addWidget(splitter_3);

        MainWindow4->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow4);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 897, 22));
        MainWindow4->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow4);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow4->setStatusBar(statusbar);

        retranslateUi(MainWindow4);

        QMetaObject::connectSlotsByName(MainWindow4);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow4)
    {
        MainWindow4->setWindowTitle(QApplication::translate("MainWindow4", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QApplication::translate("MainWindow4", "command line :", nullptr));
        label_4->setText(QApplication::translate("MainWindow4", "time for all :", nullptr));
        label_9->setText(QApplication::translate("MainWindow4", "X1: ", nullptr));
        label_6->setText(QString());
        label_11->setText(QApplication::translate("MainWindow4", "Y1: ", nullptr));
        label_7->setText(QString());
        label_10->setText(QApplication::translate("MainWindow4", "Z1: ", nullptr));
        label_8->setText(QString());
        take_first->setText(QApplication::translate("MainWindow4", "take first position", nullptr));
        take_second->setText(QApplication::translate("MainWindow4", "take second position", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow4", "inverse", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow4", "jacobian", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow4", "switch kinect on", nullptr));
        pushButton->setText(QApplication::translate("MainWindow4", "switch zero on", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow4: public Ui_MainWindow4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW4_H
