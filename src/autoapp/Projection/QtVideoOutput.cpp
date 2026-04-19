/*
*  This file is part of openauto project.
*  Copyright (C) 2018 f1x.studio (Michal Szwaj)
*
*  openauto is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.

*  openauto is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with openauto. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QQmlApplicationEngine>
#include <f1x/openauto/autoapp/Projection/QtVideoOutput.hpp>
#include <f1x/openauto/Common/Log.hpp>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace projection
{

QtVideoOutput::QtVideoOutput(configuration::IConfiguration::Pointer configuration)
    : VideoOutput(std::move(configuration))
{
    this->moveToThread(QApplication::instance()->thread());
    connect(this, &QtVideoOutput::startPlayback, this, &QtVideoOutput::onStartPlayback, Qt::QueuedConnection);
    connect(this, &QtVideoOutput::stopPlayback, this, &QtVideoOutput::onStopPlayback, Qt::QueuedConnection);
    connect(this, &QtVideoOutput::pausePlayback, this, &QtVideoOutput::onPausePlayback, Qt::QueuedConnection);
    connect(this, &QtVideoOutput::resumePlayback, this, &QtVideoOutput::onResumePlayback, Qt::QueuedConnection);
    QMetaObject::invokeMethod(this, "createVideoOutput", Qt::BlockingQueuedConnection);
}

void QtVideoOutput::createVideoOutput()
{
    OPENAUTO_LOG(info) << "[QtVideoOutput] createVideoOutput()";
    
    QQmlApplicationEngine *engine = new QQmlApplicationEngine();
    engine->load(QUrl("qrc:/videooutput.qml"));
    QObject *root = engine->rootObjects().first();
    window_ = qobject_cast<QWindow *>(root);

    QObject* ptr = window_->findChild<QObject *>(QString("player"));
    mediaPlayer_ = qvariant_cast<QMediaPlayer*>(ptr->property("mediaObject"));
}


bool QtVideoOutput::open()
{
    return videoBuffer_.open(QIODevice::ReadWrite);
}

bool QtVideoOutput::init()
{
    emit startPlayback();
    return true;
}

void QtVideoOutput::stop()
{
    emit stopPlayback();
}

void QtVideoOutput::pause()
{
    emit pausePlayback();
}

void QtVideoOutput::resume()
{
    emit resumePlayback();
}

void QtVideoOutput::write(uint64_t, const aasdk::common::DataConstBuffer& buffer)
{
    videoBuffer_.write(reinterpret_cast<const char*>(buffer.cdata), buffer.size);
}

void QtVideoOutput::onStartPlayback()
{
    mediaPlayer_->setMedia(QMediaContent(), &videoBuffer_);
    mediaPlayer_->setPlaybackRate(0);
    mediaPlayer_->play();

    // TODO: This only outputs a line if there's an error - FIXME - Output a proper status instead
    OPENAUTO_LOG(debug) << "Player error state -> " << mediaPlayer_->errorString().toStdString();
}

void QtVideoOutput::onStopPlayback()
{
    window_->hide();
    mediaPlayer_->stop();
    mediaPlayer_->setMedia(QMediaContent());
}

void QtVideoOutput::onPausePlayback()
{
    window_->hide();
}

void QtVideoOutput::onResumePlayback()
{
    window_->focusObject();
    window_->raise();
    window_->showFullScreen();
    window_->requestActivate();
}

}
}
}
}
