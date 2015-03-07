#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;

    QAction * copiar_;
    QAction * seleccionarTodo_;
};

#endif // MAINWINDOW_H
