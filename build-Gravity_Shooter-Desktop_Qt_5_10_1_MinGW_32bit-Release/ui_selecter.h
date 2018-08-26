/********************************************************************************
** Form generated from reading UI file 'selecter.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTER_H
#define UI_SELECTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Selecter
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpinBox *playerSpinBox;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *minCntSpinBox;
    QSpinBox *maxCntSpinBox;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QDoubleSpinBox *minDstSpinBox;
    QLabel *label_6;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;

    void setupUi(QDialog *Selecter)
    {
        if (Selecter->objectName().isEmpty())
            Selecter->setObjectName(QStringLiteral("Selecter"));
        Selecter->resize(500, 350);
        buttonBox = new QDialogButtonBox(Selecter);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(260, 310, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(Selecter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 30, 411, 271));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 391, 231));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        playerSpinBox = new QSpinBox(gridLayoutWidget);
        playerSpinBox->setObjectName(QStringLiteral("playerSpinBox"));
        playerSpinBox->setMinimum(2);

        gridLayout->addWidget(playerSpinBox, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        minCntSpinBox = new QSpinBox(gridLayoutWidget);
        minCntSpinBox->setObjectName(QStringLiteral("minCntSpinBox"));
        minCntSpinBox->setMaximum(255);
        minCntSpinBox->setValue(5);

        gridLayout->addWidget(minCntSpinBox, 1, 1, 1, 1);

        maxCntSpinBox = new QSpinBox(gridLayoutWidget);
        maxCntSpinBox->setObjectName(QStringLiteral("maxCntSpinBox"));
        maxCntSpinBox->setMaximum(255);
        maxCntSpinBox->setValue(15);

        gridLayout->addWidget(maxCntSpinBox, 2, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        minDstSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        minDstSpinBox->setObjectName(QStringLiteral("minDstSpinBox"));
        minDstSpinBox->setMaximum(1000);
        minDstSpinBox->setSingleStep(10);
        minDstSpinBox->setValue(50);

        gridLayout->addWidget(minDstSpinBox, 3, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        widthSpinBox = new QSpinBox(gridLayoutWidget);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));
        widthSpinBox->setMaximum(8191);
        widthSpinBox->setValue(600);
        widthSpinBox->setDisplayIntegerBase(10);

        gridLayout->addWidget(widthSpinBox, 4, 1, 1, 1);

        heightSpinBox = new QSpinBox(gridLayoutWidget);
        heightSpinBox->setObjectName(QStringLiteral("heightSpinBox"));
        heightSpinBox->setMaximum(8191);
        heightSpinBox->setSingleStep(100);
        heightSpinBox->setValue(600);

        gridLayout->addWidget(heightSpinBox, 5, 1, 1, 1);


        retranslateUi(Selecter);
        QObject::connect(buttonBox, SIGNAL(accepted()), Selecter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Selecter, SLOT(reject()));

        QMetaObject::connectSlotsByName(Selecter);
    } // setupUi

    void retranslateUi(QDialog *Selecter)
    {
        Selecter->setWindowTitle(QApplication::translate("Selecter", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("Selecter", "Settings", nullptr));
        label->setText(QApplication::translate("Selecter", "Planet Count", nullptr));
        label_2->setText(QApplication::translate("Selecter", "Min Planet Count", nullptr));
        label_4->setText(QApplication::translate("Selecter", "Min Distance", nullptr));
        label_3->setText(QApplication::translate("Selecter", "Max Planet Count", nullptr));
        label_5->setText(QApplication::translate("Selecter", "Width", nullptr));
        label_6->setText(QApplication::translate("Selecter", "Height", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Selecter: public Ui_Selecter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTER_H
