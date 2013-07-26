#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QSystemTrayIcon>

#include "notificationmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(pushButton_2_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButton_clicked()
{
    QMessageBox msg;

    QRect g = geometry();
    QString message = QString("l:%1 r:%2 w:%3 h:%4").arg(g.left()).arg(g.right()).arg(g.width()).arg(g.height());
    msg.setText(message);
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    msg.setGeometry(geometry());
    msg.exec();
}

void MainWindow::pushButton_2_clicked()
{
//    QMessageBox msg;
//    msg.setText("pushButton_2_clicked()");
//    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//    msg.exec();


//    QFileDialog fdlg;
//    fdlg.setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
//    fdlg.exec();

    NotificationManager nman;
    nman.notify(1, "Test 1", "Text 1");
    nman.notify(2, "Test 2", "Text 2");
    nman.notify(3, "Test 3", "Text 3");
}
