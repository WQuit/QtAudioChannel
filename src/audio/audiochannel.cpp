#include "audiochannel.h"

AudioChannel::AudioChannel(QObject *parent) : QObject(parent)
{

}

QBuffer *AudioChannel::filter(const QAudioBuffer &buffer)
{
    QVector<float> channel1;
    QVector<float> channel2;
    decode_channel<qint32>(channel1, channel2, buffer);
    QVector<float> filtered_channel1;
    QVector<float> filtered_channel2;

    for (auto i = 0; i < channel1.count() && i < channel2.count(); ++i){
        float left = 1;
        float right = 1;

        filtered_channel1.append(left);
        filtered_channel2.append(right);
    }

    QByteArray array;
    encode_channel<qint32>(filtered_channel1, filtered_channel2, array);
    auto qb = new QBuffer();
    qb->setData(array);
    return qb;
}
