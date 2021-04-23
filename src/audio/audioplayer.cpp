#include "audioplayer.h"
#include "audiomanager.h"

AudioPlayer::AudioPlayer(QObject *parent) : QObject(parent),
    _output(nullptr),
    _ctrl(nullptr),
    _media(nullptr),
    _format({}),
    _decoder(nullptr),
    _info({})
{

}

AudioPlayer *AudioPlayer::instance()
{
    static AudioPlayer player;
    return &player;
}

void AudioPlayer::setAudioFile(FileInfo info)
{
    _info = info;
}

void AudioPlayer::setAudioFormat(QAudioFormat format)
{
    _format = format;
}

void AudioPlayer::play()
{
    _decoder = new QAudioDecoder(this);
    _decoder->setAudioFormat(_format);
    _decoder->setSourceFilename(_info.filePath);

    _output = new QAudioOutput(_format, this);
    _ctrl = new AudioDeviceCtrl(_decoder, this);
    _ctrl->open(QIODevice::ReadOnly);
    _output->start(_ctrl);
}

void AudioPlayer::stop()
{
    _output->stop();
}

void AudioPlayer::pause()
{

}
