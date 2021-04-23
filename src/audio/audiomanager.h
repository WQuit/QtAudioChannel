#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include "audiodevicectrl.h"
#include "audiolist.h"

class AudioManager : public QObject
{
    Q_OBJECT
public:
    static AudioManager* instance();
    void init();
    void setPlayList(QList<FileInfo> list);
    void setPlayAudio(int index);
    void setPlayFormat(QAudioFormat format);
    void play();
    void start();
private:
    AudioManager();
signals:
    void sigPlayNext();
};

#endif // AUDIOMANAGER_H
