#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QMediaResource>
#include <QMediaContent>
#include "audiodevicectrl.h"
#include "../globaldef.h"

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    static AudioPlayer* instance();
    void setAudioFile(FileInfo info);
    void setAudioFormat(QAudioFormat format);
    void play();
    void stop();
    void pause();
private:
    explicit AudioPlayer(QObject *parent = nullptr);
    QAudioOutput* _output;
    AudioDeviceCtrl* _ctrl;
    QMediaContent* _media;
    QAudioFormat _format;
    QAudioDecoder* _decoder;
    FileInfo _info;
signals:
    void sigPlayNext();
};

#endif // AUDIOPLAYER_H
