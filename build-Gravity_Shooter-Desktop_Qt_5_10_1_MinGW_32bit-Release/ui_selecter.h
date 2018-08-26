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
    QLabel *label_5;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_8;
    QDoubleSpinBox *maxRadiusSpinBox;
    QDoubleSpinBox *minRadiusSpinBox;
    QLabel *label_9;
    QDoubleSpinBox *minBetweenSpinBox;
    QDoubleSpinBox *epsSpinBox;
    QDoubleSpinBox *shipRadiusSpinBox;
    QDoubleSpinBox *maxPowPerSecSpinBox;
    QLabel *label_7;
    QLabel *label_11;
    QLabel *label_10;
    QSpinBox *minCntSpinBox;
    QSpinBox *maxCntSpinBox;
    QLabel *label_2;
    QSpinBox *playerSpinBox;
    QLabel *label;
    QLabel *label_3;
    QDoubleSpinBox *minDstSpinBox;
    QLabel *label_13;
    QDoubleSpinBox *rangeSpinBox;

    void setupUi(QDialog *Selecter)
    {
        if (Selecter->objectName().isEmpty())
            Selecter->setObjectName(QStringLiteral("Selecter"));
        Selecter->resize(500, 650);
        buttonBox = new QDialogButtonBox(Selecter);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(260, 600, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(Selecter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 20, 411, 571));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 391, 511));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

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

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 11, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        maxRadiusSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        maxRadiusSpinBox->setObjectName(QStringLiteral("maxRadiusSpinBox"));
        maxRadiusSpinBox->setMaximum(8192);
        maxRadiusSpinBox->setValue(30);

        gridLayout->addWidget(maxRadiusSpinBox, 7, 1, 1, 1);

        minRadiusSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        minRadiusSpinBox->setObjectName(QStringLiteral("minRadiusSpinBox"));
        minRadiusSpinBox->setMaximum(8192);
        minRadiusSpinBox->setValue(2);

        gridLayout->addWidget(minRadiusSpinBox, 6, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        minBetweenSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        minBetweenSpinBox->setObjectName(QStringLiteral("minBetweenSpinBox"));
        minBetweenSpinBox->setMaximum(8192);
        minBetweenSpinBox->setSingleStep(0.1);
        minBetweenSpinBox->setValue(0.5);

        gridLayout->addWidget(minBetweenSpinBox, 8, 1, 1, 1);

        epsSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        epsSpinBox->setObjectName(QStringLiteral("epsSpinBox"));
        epsSpinBox->setMaximum(8192);
        epsSpinBox->setValue(1);

        gridLayout->addWidget(epsSpinBox, 9, 1, 1, 1);

        shipRadiusSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        shipRadiusSpinBox->setObjectName(QStringLiteral("shipRadiusSpinBox"));
        shipRadiusSpinBox->setMaximum(8192);
        shipRadiusSpinBox->setValue(10);

        gridLayout->addWidget(shipRadiusSpinBox, 11, 1, 1, 1);

        maxPowPerSecSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        maxPowPerSecSpinBox->setObjectName(QStringLiteral("maxPowPerSecSpinBox"));
        maxPowPerSecSpinBox->setMaximum(8192);
        maxPowPerSecSpinBox->setValue(2);

        gridLayout->addWidget(maxPowPerSecSpinBox, 10, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 10, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 1);

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

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        playerSpinBox = new QSpinBox(gridLayoutWidget);
        playerSpinBox->setObjectName(QStringLiteral("playerSpinBox"));
        playerSpinBox->setMinimum(2);

        gridLayout->addWidget(playerSpinBox, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        minDstSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        minDstSpinBox->setObjectName(QStringLiteral("minDstSpinBox"));
        minDstSpinBox->setMaximum(1000);
        minDstSpinBox->setSingleStep(10);
        minDstSpinBox->setValue(50);

        gridLayout->addWidget(minDstSpinBox, 3, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 12, 0, 1, 1);

        rangeSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        rangeSpinBox->setObjectName(QStringLiteral("rangeSpinBox"));
        rangeSpinBox->setMaximum(1);
        rangeSpinBox->setSingleStep(0.1);
        rangeSpinBox->setValue(0.5);

        gridLayout->addWidget(rangeSpinBox, 12, 1, 1, 1);


        retranslateUi(Selecter);
        QObject::connect(buttonBox, SIGNAL(accepted()), Selecter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Selecter, SLOT(reject()));

        QMetaObject::connectSlotsByName(Selecter);
    } // setupUi

    void retranslateUi(QDialog *Selecter)
    {
        Selecter->setWindowTitle(QApplication::translate("Selecter", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("Selecter", "Settings", nullptr));
        label_5->setText(QApplication::translate("Selecter", "Width", nullptr));
        label_4->setText(QApplication::translate("Selecter", "Min Distance", nullptr));
        label_6->setText(QApplication::translate("Selecter", "Height", nullptr));
        label_12->setText(QApplication::translate("Selecter", "Ship Radius", nullptr));
        label_8->setText(QApplication::translate("Selecter", "Max Radius", nullptr));
        label_9->setText(QApplication::translate("Selecter", "Min Between Percent", nullptr));
        label_7->setText(QApplication::translate("Selecter", "Min Radius", nullptr));
        label_11->setText(QApplication::translate("Selecter", "Max Power/Frame", nullptr));
        label_10->setText(QApplication::translate("Selecter", "EPS", nullptr));
        label_2->setText(QApplication::translate("Selecter", "Min Planet Count", nullptr));
        label->setText(QApplication::translate("Selecter", "Planet Count", nullptr));
        label_3->setText(QApplication::translate("Selecter", "Max Planet Count", nullptr));
        label_13->setText(QApplication::translate("Selecter", "Range", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Selecter: public Ui_Selecter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTER_H
