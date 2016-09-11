/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout_4;

    void setupUi(QWidget *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QStringLiteral("GUIClass"));
        GUIClass->resize(856, 731);
        verticalLayout_4 = new QVBoxLayout(GUIClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox = new QGroupBox(GUIClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        horizontalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setChecked(true);

        horizontalLayout->addWidget(radioButton_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_6->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_6->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        horizontalLayout_5->addWidget(groupBox);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(GUIClass);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        verticalLayout_3->addWidget(label);

        pushButton_4 = new QPushButton(GUIClass);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_3->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(GUIClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);


        horizontalLayout_5->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_5);

        groupBox_2 = new QGroupBox(GUIClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        horizontalLayout_3->addWidget(radioButton_5);

        radioButton_6 = new QRadioButton(groupBox_2);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setChecked(false);

        horizontalLayout_3->addWidget(radioButton_6);

        radioButton_7 = new QRadioButton(groupBox_2);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));

        horizontalLayout_3->addWidget(radioButton_7);


        verticalLayout_2->addLayout(horizontalLayout_3);

        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        verticalLayout_2->addWidget(lineEdit_4);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        textBrowser_2 = new QTextBrowser(groupBox_2);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));

        verticalLayout_2->addWidget(textBrowser_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(groupBox_2);


        retranslateUi(GUIClass);
        QObject::connect(pushButton_3, SIGNAL(clicked()), GUIClass, SLOT(close()));

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QWidget *GUIClass)
    {
        GUIClass->setWindowTitle(QApplication::translate("GUIClass", "GUI", 0));
        groupBox->setTitle(QApplication::translate("GUIClass", "Generator", 0));
        radioButton->setText(QApplication::translate("GUIClass", "Built-in", 0));
        radioButton_2->setText(QApplication::translate("GUIClass", "LFSR", 0));
        radioButton_3->setText(QApplication::translate("GUIClass", "Table", 0));
        lineEdit_2->setText(QApplication::translate("GUIClass", "11", 0));
        lineEdit_2->setPlaceholderText(QApplication::translate("GUIClass", "Register(s) size", 0));
        lineEdit_3->setText(QApplication::translate("GUIClass", "15", 0));
        lineEdit_3->setPlaceholderText(QApplication::translate("GUIClass", "The number of Registers", 0));
        lineEdit->setText(QApplication::translate("GUIClass", "20000", 0));
        lineEdit->setPlaceholderText(QApplication::translate("GUIClass", "Size of output", 0));
        pushButton->setText(QApplication::translate("GUIClass", "Generate", 0));
        label->setText(QApplication::translate("GUIClass", "<html><head/><body><p>Theory of Probability </p><p>Laboratory #1</p><p>by <br/>student of IO-53</p><p>Krisak I. M.</p></body></html>", 0));
        pushButton_4->setText(QApplication::translate("GUIClass", "Clear", 0));
        pushButton_3->setText(QApplication::translate("GUIClass", "Close", 0));
        groupBox_2->setTitle(QApplication::translate("GUIClass", "Tester", 0));
        radioButton_4->setText(QApplication::translate("GUIClass", "Frequency", 0));
        radioButton_5->setText(QApplication::translate("GUIClass", "Differential", 0));
        radioButton_6->setText(QApplication::translate("GUIClass", "Range", 0));
        radioButton_7->setText(QApplication::translate("GUIClass", "NonLinear", 0));
        lineEdit_4->setText(QApplication::translate("GUIClass", "4", 0));
        lineEdit_4->setPlaceholderText(QApplication::translate("GUIClass", "Range", 0));
        pushButton_2->setText(QApplication::translate("GUIClass", "Test", 0));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
