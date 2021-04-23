#ifndef AUDIODEVICECTRL_H
#define AUDIODEVICECTRL_H

#include <QObject>
#include <QIODevice>
#include <QAudioBuffer>
#include <QAudioDecoder>
#include <QBuffer>
#include <QQueue>
#include "audiochannel.h"

class AudioDeviceCtrl : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioDeviceCtrl(QAudioDecoder *decoder, QObject *parent = nullptr);
    virtual bool atEnd() const override;
    virtual qint64 bytesAvailable() const override;

protected:
    virtual qint64 readData(char* data, qint64 size) override;
    virtual qint64 writeData(const char *data, qint64 maxSize);

private:
    QAudioDecoder* _decoder;
    QQueue<QBuffer*> _queue;
    QQueue<QAudioBuffer*> _abuffer_queue;
    bool _isFinished;
    AudioChannel* _channel;
public slots:
    void sltBufferReady();
    void sltFinished();
    void sltError(QAudioDecoder::Error error);
};

#endif // AUDIODEVICECTRL_H
