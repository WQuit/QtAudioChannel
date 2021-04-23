#ifndef AUDIOLIST_H
#define AUDIOLIST_H

#include <QObject>
#include <QFile>
#include <QList>
#include "../globaldef.h"

enum PlayMode
{
    Order = 0,  //顺序播放
    Loop,       //循环播放
    One,        //单曲播放
    OneLoop,    //单曲循环
    Random      //随机播放
};

class AudioList : public QObject
{
    Q_OBJECT
public:
    explicit AudioList(QObject *parent = nullptr);
    void addAudioFile(FileInfo file);
    void delAudioFile(FileInfo file);
    void delAudioFile(int index);
    int count();
    FileInfo playFile();
    int playIndex();
    QList<FileInfo> playList();
    void setPlayIndex(int index);
    void setPlayMode(PlayMode mode);
    static AudioList* instance();
private:
    QList<FileInfo> _fileList;
    int _index;
    PlayMode _mode;
signals:
    void sigPlayFile(FileInfo);
private slots:
    void sltNextAudio();
};

#endif // AUDIOSOURCE_H
