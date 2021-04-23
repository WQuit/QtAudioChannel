#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audio/audiomanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
signals:
    void sigAddFile(FileInfo);
    void sigRemoveFile(int index);
    void sigPlay(int index);
    void sigStop();
    void sigPause();
    void sigLeftChannle();
    void sigRightChannle();
    void sigDoubleChannle();
};
#endif // MAINWINDOW_H
