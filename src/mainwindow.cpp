#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "audio/audiomanager.h"
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AudioManager::instance()->start();
    FileInfo info = {QString("我的一个道姑朋友"), QString("D:\\14-music\\我的一个道姑朋友.mp3")};
    QList<FileInfo> list; list.push_back(info);
    AudioManager::instance()->setPlayList(list);
    AudioManager::instance()->setPlayAudio(0);
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setCodec("audio/pcm");
    format.setSampleSize(32);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    AudioManager::instance()->setPlayFormat(format);
    AudioManager::instance()->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

