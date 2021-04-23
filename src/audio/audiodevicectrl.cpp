#include "audiodevicectrl.h"
#include <QDebug>
#include <QByteArray>

AudioDeviceCtrl::AudioDeviceCtrl(QAudioDecoder *decoder, QObject *parent):
    QIODevice(parent),
    _decoder(decoder),
    _isFinished(false),
    _channel(nullptr)
{
    connect(_decoder, &QAudioDecoder::bufferReady, this, &AudioDeviceCtrl::sltBufferReady);
    connect(_decoder, &QAudioDecoder::finished, this, &AudioDeviceCtrl::sltFinished);
    connect(_decoder, SIGNAL(error(QAudioDecoder::Error)), this, SLOT(sltError(QAudioDecoder::Error)));
    _decoder->start();
    _channel = new AudioChannel();
}

bool AudioDeviceCtrl::atEnd() const
{
    return _isFinished && _queue.empty();
}

qint64 AudioDeviceCtrl::bytesAvailable() const
{
    if (_queue.empty()){
        return 0;
    }else{
        return _queue.first()->bytesAvailable();
    }
}

qint64 AudioDeviceCtrl::readData(char *data, qint64 size)
{
    if(_queue.empty() && _abuffer_queue.empty()){
        return 0;
    }

    if (_queue.empty()){
        QAudioBuffer* buffer = _abuffer_queue.first();
        QBuffer* qb = _channel->filter(*buffer);
        _queue.push_back(qb);
        _abuffer_queue.removeFirst();
        delete buffer;
    }

    QBuffer* buffer = _queue.first();
    if (!buffer->isOpen()){
        buffer->open(QIODevice::ReadOnly);
    }

    qint64 n = buffer->read(data, size);
    if (buffer->atEnd()){
        _queue.removeFirst();
        delete buffer;
    }

    return n;
}

qint64 AudioDeviceCtrl::writeData(const char *data, qint64 maxSize)
{
    Q_UNUSED(data);
    Q_UNUSED(maxSize);
    return 0;
}

void AudioDeviceCtrl::sltBufferReady()
{
    QAudioBuffer buffer = _decoder->read();
    if (buffer.isValid()){
        _abuffer_queue.push_back(new QAudioBuffer(buffer));
    }
}

void AudioDeviceCtrl::sltFinished()
{
    _isFinished = true;
}

void AudioDeviceCtrl::sltError(QAudioDecoder::Error error)
{
    qDebug() << error;
}
