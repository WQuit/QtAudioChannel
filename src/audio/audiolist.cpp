#include "audiolist.h"
#include "audiomanager.h"

AudioList::AudioList(QObject *parent) : QObject(parent),
    _fileList({}),
    _mode(PlayMode::Order)
{
   connect(AudioManager::instance(), &AudioManager::sigPlayNext, this, &AudioList::sltNextAudio);
}

void AudioList::addAudioFile(FileInfo file)
{
    _fileList.push_back(file);
}

void AudioList::delAudioFile(FileInfo file)
{
    for(auto it = _fileList.begin(); it != _fileList.end(); it++)
    {
        if(it->fileName == file.fileName && it->filePath == file.filePath)
        {
            it = _fileList.erase(it);
            break;
        }
    }
}

void AudioList::delAudioFile(int index)
{
    _fileList.removeAt(index);
}

int AudioList::count()
{
    return _fileList.count();
}

FileInfo AudioList::playFile()
{
    return _fileList[_index];
}

int AudioList::playIndex()
{
    return _index;
}

QList<FileInfo> AudioList::playList()
{
    return _fileList;
}

void AudioList::setPlayIndex(int index)
{
    if(index == _index)
        return;
    _index = index;
    emit sigPlayFile(_fileList[index]);
}

void AudioList::setPlayMode(PlayMode mode)
{
    _mode = mode;
}

AudioList *AudioList::instance()
{
    static AudioList source;
    return &source;
}

void AudioList::sltNextAudio()
{
    switch (_mode) {
        case PlayMode::Order:
        if(_index == _fileList.count() - 1)
        {
            return;
        }
        _index++;
        break;
    case PlayMode::Loop:
        _index = (_index == _fileList.count() - 1) ? 0 : _index+1;
        break;
    case PlayMode::One:
        return;
        break;
    case PlayMode::OneLoop:
        break;
    case PlayMode::Random:

        break;
    }
    emit sigPlayFile(_fileList[_index]);
}
