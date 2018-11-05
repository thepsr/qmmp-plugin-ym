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

/*
//
// DecoderYmFactory
//
bool DecoderYmFactory::supports(const QString &source) const
{
    foreach(QString filter, properties().filters)
    {
        QRegExp regexp(filter, Qt::CaseInsensitive, QRegExp::Wildcard);
        if (regexp.exactMatch(source))
            return true;
    }
    return false;
}
*/

bool DecoderYmFactory::canDecode(QIODevice *) const
{
    return false;
}

const DecoderProperties DecoderYmFactory::properties() const
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

QList<FileInfo *> DecoderYmFactory::createPlayList(const QString &fileName, bool useMetaData, QStringList *)
{
    QList <FileInfo *> list;
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
        list << new FileInfo(fileName);

  	    pMusic->getMusicInfo(&info);

        if (useMetaData)
        {
            char* title = strdup(info.pSongName);
            char* composer = strdup(info.pSongAuthor);
            char* comment = strdup(info.pSongComment);

            list.at(0)->setMetaData(Qmmp::TITLE, QString::fromUtf8(title).trimmed());
            list.at(0)->setMetaData(Qmmp::COMPOSER, QString::fromUtf8(composer).trimmed());
            list.at(0)->setMetaData(Qmmp::COMMENT, QString::fromUtf8(comment).trimmed());
        }

        list.at(0)->setLength(info.musicTimeInSec);
    }

    delete pMusic;

    return list;
}

MetaDataModel* DecoderYmFactory::createMetaDataModel(const QString&, QObject *)
{
    return 0;
}

void DecoderYmFactory::showSettings(QWidget *)
{
}

void DecoderYmFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About YM Audio Plugin"),
                        tr("Qmmp YM Audio Plugin")+" V 0.6\n"+
                        tr("Written by:")+" Georges Thill\n"+
                        "\n"+
                        tr("Based on:")+"\n"+
                        "ST-Sound, ATARI-ST Music Emulator V 1.43\n"+
                        "Copyright (c) 1995-1999 Arnaud Carre\n"+
                        "All rights reserved.\n"+
                        "http://leonard.oxg.free.fr");
}

QTranslator *DecoderYmFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/ym_plugin_") + locale);
    return translator;
}



