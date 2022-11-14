#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <random>
#include <set>
#include "session.h"
#include "graphpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE






class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onDrawConnOnOff();
    void onGenNewSession();

private:
    GraphPanel panel__;
    Session* session__=nullptr;
    bool drawConn__=true;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
