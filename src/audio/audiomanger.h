#ifndef AUDIOMANGER_H
#define AUDIOMANGER_H

#include <QObject>
#include <QAudioBuffer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>

class AudioManger : QObject
{
    Q_OBJECT
public:
    AudioManger();
};

#endif // AUDIOMANGER_H
