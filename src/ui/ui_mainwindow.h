/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "src/attributes_view.h"
#include "src/containers_view.h"
#include "src/contents_view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWhat;
    QAction *actionSecond;
    QAction *actionSomething;
    QAction *actionHere;
    QAction *menubar_view_advancedView;
    QWidget *centralwidget;
    QSplitter *splitter;
    ContainersView *containers_view;
    ContentsView *contents_view;
    AttributesView *attributes_view;
    QMenuBar *menubar;
    QMenu *menuhello;
    QMenu *menuEdit;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1307, 637);
        actionWhat = new QAction(MainWindow);
        actionWhat->setObjectName(QString::fromUtf8("actionWhat"));
        actionSecond = new QAction(MainWindow);
        actionSecond->setObjectName(QString::fromUtf8("actionSecond"));
        actionSomething = new QAction(MainWindow);
        actionSomething->setObjectName(QString::fromUtf8("actionSomething"));
        actionHere = new QAction(MainWindow);
        actionHere->setObjectName(QString::fromUtf8("actionHere"));
        menubar_view_advancedView = new QAction(MainWindow);
        menubar_view_advancedView->setObjectName(QString::fromUtf8("menubar_view_advancedView"));
        menubar_view_advancedView->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(0, 0, 1301, 591));
        splitter->setOrientation(Qt::Horizontal);
        containers_view = new ContainersView(splitter);
        containers_view->setObjectName(QString::fromUtf8("containers_view"));
        containers_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        containers_view->setRootIsDecorated(true);
        containers_view->setItemsExpandable(true);
        containers_view->setExpandsOnDoubleClick(true);
        splitter->addWidget(containers_view);
        containers_view->header()->setVisible(true);
        contents_view = new ContentsView(splitter);
        contents_view->setObjectName(QString::fromUtf8("contents_view"));
        contents_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        contents_view->setSelectionMode(QAbstractItemView::SingleSelection);
        contents_view->setRootIsDecorated(false);
        contents_view->setItemsExpandable(false);
        contents_view->setExpandsOnDoubleClick(false);
        splitter->addWidget(contents_view);
        contents_view->header()->setVisible(true);
        attributes_view = new AttributesView(splitter);
        attributes_view->setObjectName(QString::fromUtf8("attributes_view"));
        attributes_view->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        attributes_view->setSelectionMode(QAbstractItemView::NoSelection);
        attributes_view->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter->addWidget(attributes_view);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1307, 27));
        menuhello = new QMenu(menubar);
        menuhello->setObjectName(QString::fromUtf8("menuhello"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuhello->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menuhello->addAction(actionWhat);
        menuhello->addAction(actionSecond);
        menuEdit->addAction(actionSomething);
        menuEdit->addAction(actionHere);
        menuView->addAction(menubar_view_advancedView);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionWhat->setText(QApplication::translate("MainWindow", "What", nullptr));
        actionSecond->setText(QApplication::translate("MainWindow", "Second", nullptr));
        actionSomething->setText(QApplication::translate("MainWindow", "Something", nullptr));
        actionHere->setText(QApplication::translate("MainWindow", "Here", nullptr));
        menubar_view_advancedView->setText(QApplication::translate("MainWindow", "Advanced view", nullptr));
        menuhello->setTitle(QApplication::translate("MainWindow", "New", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H