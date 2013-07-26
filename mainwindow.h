#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void pushButton_clicked();
    void pushButton_2_clicked();
signals:
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
