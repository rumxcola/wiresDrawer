#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , panel__(this)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->painterArea->addWidget(&panel__);
    connect(ui->dbgOutBtn,&QPushButton::clicked,&panel__,&GraphPanel::onDbgOut);
    connect(ui->genRandomBtn,&QPushButton::clicked,this,&MainWindow::onGenNewSession);
    connect(ui->drawConnBtn,&QPushButton::clicked,this,&MainWindow::onDrawConnOnOff);
    onGenNewSession();
    onDrawConnOnOff();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onGenNewSession(){
    panel__.genNewSession(ui->cablesCount->value(),ui->pinsMax->value(), static_cast<double>(ui->connectedPercent->value())/100);
    auto panelSize=panel__.sizeHint();
    auto btnsSize=ui->headerArea->sizeHint();
    QSize size(std::max(panelSize.width(),btnsSize.width()),btnsSize.height()+panelSize.height());
    resize( size);
}
void MainWindow::onDrawConnOnOff()
{
    panel__.setDrawConnFlag(!panel__.hasDrawConnFlag());
    ui->drawConnBtn->setText(panel__.hasDrawConnFlag()?"don't conn":"conn");
    repaint();

}

