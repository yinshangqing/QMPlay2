/*
    QMPlay2 is a video and audio player.
    Copyright (C) 2010-2021  Błażej Szczygieł

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <Writer.hpp>

#include <PortAudioCommon.hpp>
#include <portaudio.h>

#include <QCoreApplication>

#ifdef Q_OS_MACOS
class AudioDevice;
#endif

class PortAudioWriter final : public Writer
{
    Q_DECLARE_TR_FUNCTIONS(PortAudioWriter)

public:
    PortAudioWriter(Module &);
private:
    ~PortAudioWriter();

    bool set() override;

    bool readyWrite() const override;

    bool processParams(bool *paramsCorrected) override;
    qint64 write(const QByteArray &) override;
    void pause() override;

    QString name() const override;

    bool open() override;

private:
    int getRequiredDeviceChn(int chn);

    bool openStream();
    bool startStream();
    bool writeStream(const QByteArray &arr);
    void playbackError();

#ifdef Q_OS_WIN
    bool isDeviceInvalidated() const;
    bool reopenStream();
#endif

    void drain();

    void close();

private:
    QString m_outputDevice;
    PaStreamParameters m_outputParameters = {};
    PaStream *m_stream = nullptr;
    int m_sampleRate = 0;
    double m_outputLatency = 0.0;
    bool m_initialized = false;
    bool m_err = false;
    bool m_dontShowError = false;
#ifdef Q_OS_MACOS
    bool m_bitPerfect = false;
    AudioDevice *m_coreAudioDevice = nullptr;
#endif
};

#define PortAudioWriterName "PortAudio"
