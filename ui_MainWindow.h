/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QGroupBox *s_transformGB;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *m_followCount;
    QSpinBox *m_hairLOD;
    QSpinBox *m_guideCount;
    QSpinBox *m_hairLength;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QGroupBox *s_drawGB;
    QGridLayout *gridLayout_3;
    QComboBox *m_drawSelection;
    QCheckBox *m_wireFrame;
    QPushButton *m_reset;
    QPushButton *m_toggleFocus;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QStringLiteral("s_mainWindowGridLayout"));
        s_transformGB = new QGroupBox(centralwidget);
        s_transformGB->setObjectName(QStringLiteral("s_transformGB"));
        gridLayout_2 = new QGridLayout(s_transformGB);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(s_transformGB);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        m_followCount = new QSpinBox(s_transformGB);
        m_followCount->setObjectName(QStringLiteral("m_followCount"));
        m_followCount->setValue(1);

        gridLayout_2->addWidget(m_followCount, 2, 1, 1, 1);

        m_hairLOD = new QSpinBox(s_transformGB);
        m_hairLOD->setObjectName(QStringLiteral("m_hairLOD"));
        m_hairLOD->setValue(10);

        gridLayout_2->addWidget(m_hairLOD, 4, 1, 1, 1);

        m_guideCount = new QSpinBox(s_transformGB);
        m_guideCount->setObjectName(QStringLiteral("m_guideCount"));
        m_guideCount->setMaximum(100000);
        m_guideCount->setValue(500);

        gridLayout_2->addWidget(m_guideCount, 1, 1, 1, 1);

        m_hairLength = new QSpinBox(s_transformGB);
        m_hairLength->setObjectName(QStringLiteral("m_hairLength"));
        m_hairLength->setValue(6);

        gridLayout_2->addWidget(m_hairLength, 3, 1, 1, 1);

        label_2 = new QLabel(s_transformGB);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        label_3 = new QLabel(s_transformGB);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(s_transformGB);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(s_transformGB);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(s_transformGB, 2, 1, 1, 1);

        s_drawGB = new QGroupBox(centralwidget);
        s_drawGB->setObjectName(QStringLiteral("s_drawGB"));
        gridLayout_3 = new QGridLayout(s_drawGB);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_drawSelection = new QComboBox(s_drawGB);
        m_drawSelection->setObjectName(QStringLiteral("m_drawSelection"));

        gridLayout_3->addWidget(m_drawSelection, 0, 0, 1, 1);

        m_wireFrame = new QCheckBox(s_drawGB);
        m_wireFrame->setObjectName(QStringLiteral("m_wireFrame"));

        gridLayout_3->addWidget(m_wireFrame, 1, 0, 1, 1);

        m_reset = new QPushButton(s_drawGB);
        m_reset->setObjectName(QStringLiteral("m_reset"));

        gridLayout_3->addWidget(m_reset, 6, 0, 1, 1);

        m_toggleFocus = new QPushButton(s_drawGB);
        m_toggleFocus->setObjectName(QStringLiteral("m_toggleFocus"));

        gridLayout_3->addWidget(m_toggleFocus, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 5, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(s_drawGB, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        s_mainWindowGridLayout->addWidget(label_6, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Leu Hair Demo", Q_NULLPTR));
        s_transformGB->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Hair Length", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Follow Hairs per Guide", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Guide Hairs", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Hair LOD", Q_NULLPTR));
        s_drawGB->setTitle(QApplication::translate("MainWindow", "Draw", Q_NULLPTR));
        m_drawSelection->clear();
        m_drawSelection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Springs", Q_NULLPTR)
         << QApplication::translate("MainWindow", "NGL Bez Curve (not recommended)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Custom Bez Curve", Q_NULLPTR)
        );
        m_wireFrame->setText(QApplication::translate("MainWindow", "WireFrame", Q_NULLPTR));
        m_reset->setText(QApplication::translate("MainWindow", "Reset Sim", Q_NULLPTR));
        m_toggleFocus->setText(QApplication::translate("MainWindow", "Toggle Focus", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "The controls for this demos are set initially set to the openGL window, which allows you to move the head. Hit \"alt\" to swtich the controls to the main window, and edit the setting. Hit \"toggle focus\" to switch back. ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
