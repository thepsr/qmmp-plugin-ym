/******************************************************************************
 * Copyright (c) 2015-2016, Georges Thill
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <QMessageBox>
#include <QtGui>
#include <QRegExp>

#include "decoder_ym.h"
#include "decoderymfactory.h"


bool DecoderYmFactory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderYmFactory::properties() const
{
    DecoderProperties properties;

    properties.name = tr("YM Plugin");
    properties.filters << "*.ym";
    properties.description = tr("YM Files");
    properties.shortName = "ym";
    properties.hasAbout = true;
    properties.hasSettings = false;
    properties.noInput = true;
    properties.protocols << "file";

    return properties;
}

Decoder *DecoderYmFactory::create(const QString &path, QIODevice *)
{
    return new DecoderYm(path);
}

QList<TrackInfo *> DecoderYmFactory::createPlayList(const QString &fileName, TrackInfo::Parts parts, QStringList *)
{
    QList <TrackInfo *> list;
    CYmMusic *pMusic;
	ymMusicInfo_t info;

    pMusic = new CYmMusic;
    if (pMusic == NULL)
    {
        qWarning("DecoderYmFactory: failed to create CYmMusic");
        return list;
    }

	if (pMusic->load(fileName.toLocal8Bit()))
	{
        list << new TrackInfo(fileName);

  	    pMusic->getMusicInfo(&info);

        if(parts & TrackInfo::MetaData)
        {
            char* title = strdup(info.pSongName);
            char* composer = strdup(info.pSongAuthor);
            char* comment = strdup(info.pSongComment);

            list.at(0)->setValue(Qmmp::TITLE, QString::fromUtf8(title).trimmed());
            list.at(0)->setValue(Qmmp::COMPOSER, QString::fromUtf8(composer).trimmed());
            list.at(0)->setValue(Qmmp::COMMENT, QString::fromUtf8(comment).trimmed());
        }

        if(parts & TrackInfo::MetaData)
        {
            char* type = strdup(info.pSongType);

            list.at(0)->setValue(Qmmp::BITRATE, ((QFileInfo(fileName).size () * 8.0) / info.musicTimeInSec) + 0.5);
            list.at(0)->setValue(Qmmp::SAMPLERATE, 44100);
            list.at(0)->setValue(Qmmp::CHANNELS, 2);
            list.at(0)->setValue(Qmmp::BITS_PER_SAMPLE, 16);
            list.at(0)->setValue(Qmmp::FORMAT_NAME, QString::fromUtf8(type).trimmed());
            list.at(0)->setDuration(info.musicTimeInMs);
        }
    }

    delete pMusic;

    return list;
}

MetaDataModel* DecoderYmFactory::createMetaDataModel(const QString&, bool)
{
    return nullptr;
}

void DecoderYmFactory::showSettings(QWidget *)
{
}

void DecoderYmFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About YM Audio Plugin"),
                        tr("Qmmp YM Audio Plugin")+" V 0.8\n"+
                        tr("Written by:")+" Georges Thill\n"+
                        "\n"+
                        tr("Based on:")+"\n"+
                        "ST-Sound, ATARI-ST Music Emulator V 1.43\n"+
                        "Copyright (c) 1995-1999 Arnaud Carre\n"+
                        "All rights reserved.\n"+
                        "http://leonard.oxg.free.fr");
}

QString DecoderYmFactory::translation() const
{
    return QLatin1String(":/ym_plugin_");
}
