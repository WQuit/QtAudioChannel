#ifndef AUDIOCHANNEL_H
#define AUDIOCHANNEL_H

#include <QObject>
#include <QAudioBuffer>
#include <QBuffer>
#include <QByteArray>
#include <QVector>
#include <cmath>

class AudioChannel : public QObject
{
    Q_OBJECT
public:
    explicit AudioChannel(QObject *parent = nullptr);
    template<class T>
    void decode_channel(QVector<float>& channel1, QVector<float>& channel2, QAudioBuffer const& buffer)
    {
        T* data = (T*)(buffer.data());
        size_t len = buffer.sampleCount();

        for (size_t i=0; i < len; i+=2) {
            T left = data[i];
            T right = data[i+1];

            left = std::isnan(left) ? 0.0 : left;
            right = std::isnan(right) ? 0.0 : right;

            channel1.append(float(left) / std::numeric_limits<T>::max());
            channel2.append(float(right)/ std::numeric_limits<T>::max());
        }
    }

    template<class T>
    void encode_channel(QVector<float> const& channel1, QVector<float> const& channel2, QByteArray& bytes)
    {
        for(size_t i = 0; i < channel1.count() && i < channel2.count(); ++i){
            float left = channel1[i] > 1.0 ? 1.0 : channel1[i];
            float right = channel2[i] > 1.0 ? 1.0 : channel2[i];

            T lpcm = T(std::floor(left * std::numeric_limits<T>::max()));
            T rpcm = T(std::floor(right * std::numeric_limits<T>::max()));
            bytes.append((char*)&lpcm, sizeof(lpcm));
            bytes.append((char*)&rpcm, sizeof(rpcm));
        }
    }

    QBuffer* filter(QAudioBuffer const& buffer);
signals:

};

#endif // AUDIOCHANNEL_H
