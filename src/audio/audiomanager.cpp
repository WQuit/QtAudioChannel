#include "audiomanager.h"
#include "audioplayer.h"

AudioManager::AudioManager()
{

}

AudioManager* AudioManager::instance()
{
    static AudioManager manager;
    return &manager;
}

void AudioManager::init()
{

}

void AudioManager::setPlayList(QList<FileInfo> list)
{
    for(auto it : list)
    {
        AudioList::instance()->addAudioFile(it);
    }
}

void AudioManager::setPlayAudio(int index)
{
    AudioList::instance()->setPlayIndex(index);
}

void AudioManager::setPlayFormat(QAudioFormat format)
{
    AudioPlayer::instance()->setAudioFormat(format);
}

void AudioManager::play()
{
    AudioPlayer::instance()->play();
}

void AudioManager::start()
{
    connect(AudioPlayer::instance(), &AudioPlayer::sigPlayNext, [=]{emit sigPlayNext();});
    connect(AudioList::instance(), &AudioList::sigPlayFile, this, [=](FileInfo info){AudioPlayer::instance()->setAudioFile(info);});
}
