#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    //copiar_ = new QAction(this, "Copiar");
    //seleccionarTodo_ = new QAction(this, "Seleccionar todo");
}

MainWindow::~MainWindow()
{

}

//void MainWindow::contextMenuEvent(QContextMenuEvent *event)
//{
//    QMenu menu(this);
//    menu.addAction(copiar_);
//    menu.addAction(seleccionarTodo_);
//    menu.exec(event->globalPos());
//}
