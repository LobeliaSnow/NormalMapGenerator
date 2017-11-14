/********************************************************************************
** Form generated from reading UI file 'Tool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOL_H
#define UI_TOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QRadioButton *alpha;
    QRadioButton *red;
    QRadioButton *luminance;
    QRadioButton *blue;
    QRadioButton *green;
    QRadioButton *default_radio;
    QProgressBar *progressBar;
    QGroupBox *groupBox_2;
    QCheckBox *mirror_u;
    QCheckBox *mirror_v;
    QGroupBox *groupBox_4;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label;
    QGroupBox *groupBox_3;
    QCheckBox *invert_vector;
    QCheckBox *compute_occlusion;
    QPushButton *pushButton;
    QOpenGLWidget *openGLWidget;
    QGroupBox *groupBox_5;
    QRadioButton *diffuse_change;
    QRadioButton *diffuse_change_2;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *ToolClass)
    {
        if (ToolClass->objectName().isEmpty())
            ToolClass->setObjectName(QStringLiteral("ToolClass"));
        ToolClass->setEnabled(true);
        ToolClass->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ToolClass->sizePolicy().hasHeightForWidth());
        ToolClass->setSizePolicy(sizePolicy);
        actionOpen = new QAction(ToolClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(ToolClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(ToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(9, 130, 419, 151));
        alpha = new QRadioButton(groupBox);
        alpha->setObjectName(QStringLiteral("alpha"));
        alpha->setGeometry(QRect(10, 100, 86, 16));
        red = new QRadioButton(groupBox);
        red->setObjectName(QStringLiteral("red"));
        red->setGeometry(QRect(10, 40, 86, 16));
        luminance = new QRadioButton(groupBox);
        luminance->setObjectName(QStringLiteral("luminance"));
        luminance->setGeometry(QRect(10, 120, 201, 16));
        blue = new QRadioButton(groupBox);
        blue->setObjectName(QStringLiteral("blue"));
        blue->setGeometry(QRect(10, 80, 86, 16));
        green = new QRadioButton(groupBox);
        green->setObjectName(QStringLiteral("green"));
        green->setGeometry(QRect(10, 60, 86, 16));
        default_radio = new QRadioButton(groupBox);
        default_radio->setObjectName(QStringLiteral("default_radio"));
        default_radio->setGeometry(QRect(10, 20, 86, 16));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 640, 1261, 20));
        progressBar->setValue(0);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 290, 419, 71));
        mirror_u = new QCheckBox(groupBox_2);
        mirror_u->setObjectName(QStringLiteral("mirror_u"));
        mirror_u->setGeometry(QRect(10, 20, 301, 16));
        mirror_v = new QCheckBox(groupBox_2);
        mirror_v->setObjectName(QStringLiteral("mirror_v"));
        mirror_v->setGeometry(QRect(10, 40, 301, 16));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(9, 9, 419, 115));
        doubleSpinBox = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(20, 30, 351, 20));
        doubleSpinBox->setMinimum(-999.99);
        doubleSpinBox->setMaximum(999.99);
        doubleSpinBox->setValue(-15);
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 60, 271, 41));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 370, 419, 81));
        invert_vector = new QCheckBox(groupBox_3);
        invert_vector->setObjectName(QStringLiteral("invert_vector"));
        invert_vector->setGeometry(QRect(10, 20, 331, 16));
        compute_occlusion = new QCheckBox(groupBox_3);
        compute_occlusion->setObjectName(QStringLiteral("compute_occlusion"));
        compute_occlusion->setGeometry(QRect(10, 40, 361, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(9, 581, 421, 51));
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setEnabled(true);
        openGLWidget->setGeometry(QRect(434, 9, 837, 621));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 460, 421, 61));
        diffuse_change = new QRadioButton(groupBox_5);
        buttonGroup = new QButtonGroup(ToolClass);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(diffuse_change);
        diffuse_change->setObjectName(QStringLiteral("diffuse_change"));
        diffuse_change->setGeometry(QRect(10, 20, 141, 16));
        diffuse_change_2 = new QRadioButton(groupBox_5);
        buttonGroup->addButton(diffuse_change_2);
        diffuse_change_2->setObjectName(QStringLiteral("diffuse_change_2"));
        diffuse_change_2->setGeometry(QRect(10, 40, 141, 16));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 530, 421, 41));
        ToolClass->setCentralWidget(centralWidget);
        groupBox_5->raise();
        groupBox_3->raise();
        pushButton->raise();
        progressBar->raise();
        groupBox_4->raise();
        groupBox->raise();
        groupBox_2->raise();
        openGLWidget->raise();
        pushButton_2->raise();
        menuBar = new QMenuBar(ToolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        ToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ToolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ToolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ToolClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionSave);

        retranslateUi(ToolClass);

        QMetaObject::connectSlotsByName(ToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *ToolClass)
    {
        ToolClass->setWindowTitle(QApplication::translate("ToolClass", "Tool", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("ToolClass", "&Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("ToolClass", "&Save", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ToolClass", "\346\263\225\347\267\232\343\203\236\343\203\203\343\203\227\350\250\210\347\256\227\350\211\262", Q_NULLPTR));
        alpha->setText(QApplication::translate("ToolClass", "\343\202\242\343\203\253\343\203\225\343\202\241", Q_NULLPTR));
        red->setText(QApplication::translate("ToolClass", "\350\265\244", Q_NULLPTR));
        luminance->setText(QApplication::translate("ToolClass", "\350\274\235\345\272\246(R\343\200\201G\343\200\201B\343\201\213\343\202\211\350\250\210\347\256\227\343\201\225\343\202\214\343\201\237\345\215\230\350\211\262\345\200\244)", Q_NULLPTR));
        blue->setText(QApplication::translate("ToolClass", "\351\235\222", Q_NULLPTR));
        green->setText(QApplication::translate("ToolClass", "\347\267\221", Q_NULLPTR));
        default_radio->setText(QApplication::translate("ToolClass", "\343\203\207\343\203\225\343\202\251\343\203\253\343\203\210", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("ToolClass", "\343\203\206\343\202\257\343\202\271\343\203\201\343\203\243\345\272\247\346\250\231\351\226\242\351\200\243(\344\270\215\346\230\216)", Q_NULLPTR));
        mirror_u->setText(QApplication::translate("ToolClass", "\343\203\206\343\202\257\343\202\271\343\203\201\343\203\243\343\201\256U\345\272\247\346\250\231\345\217\215\350\273\242", Q_NULLPTR));
        mirror_v->setText(QApplication::translate("ToolClass", "\343\203\206\343\202\257\343\202\271\343\203\201\343\203\243\343\201\256V\345\272\247\346\250\231\345\217\215\350\273\242", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("ToolClass", "\346\214\257\345\271\205(\346\263\225\347\267\232\343\201\256\343\202\271\343\202\261\343\203\274\343\203\252\343\203\263\343\202\260\344\277\202\346\225\260)", Q_NULLPTR));
        label->setText(QApplication::translate("ToolClass", "\347\254\246\345\217\267 \n"
"   + OpenGL\347\224\250\n"
"   - DirectX\347\224\250", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("ToolClass", "\343\201\235\343\201\256\344\273\226\345\207\246\347\220\206", Q_NULLPTR));
        invert_vector->setText(QApplication::translate("ToolClass", "\350\250\210\347\256\227\343\201\225\343\202\214\343\201\237\346\263\225\347\267\232\343\203\231\343\202\257\343\203\210\343\203\253\343\201\256\347\254\246\345\217\267\343\202\222\345\217\215\350\273\242", Q_NULLPTR));
        compute_occlusion->setText(QApplication::translate("ToolClass", "\343\202\252\343\202\257\343\203\253\343\203\274\343\202\270\343\203\247\343\203\263\350\250\210\347\256\227\n"
"(\346\234\252\345\207\246\347\220\206\343\201\256\343\202\252\343\202\257\343\203\253\343\203\274\343\202\270\343\203\247\343\203\263\343\202\222\350\250\210\347\256\227\343\201\227\343\200\201\347\265\220\346\236\234\343\202\222\343\202\242\343\203\253\343\203\225\343\202\241\343\203\201\343\203\243\343\203\215\343\203\253\343\201\253\346\240\274\347\264\215\343\201\227\343\201\276\343\201\231\343\200\202)", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ToolClass", "compute (ctrl+b)", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("ToolClass", "\343\203\227\343\203\254\343\203\223\343\203\245\343\203\274\347\224\273\345\203\217", Q_NULLPTR));
        diffuse_change->setText(QApplication::translate("ToolClass", "\343\203\207\343\202\243\343\203\225\343\203\245\343\203\274\343\202\272\343\203\236\343\203\203\343\203\227", Q_NULLPTR));
        diffuse_change_2->setText(QApplication::translate("ToolClass", "\343\203\216\343\203\274\343\203\236\343\203\253\343\203\236\343\203\203\343\203\227", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ToolClass", "\345\210\235\346\234\237\350\250\255\345\256\232\343\201\253\346\210\273\343\201\231 (ctrl+r)", Q_NULLPTR));
        menu->setTitle(QApplication::translate("ToolClass", "&File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ToolClass: public Ui_ToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOL_H
