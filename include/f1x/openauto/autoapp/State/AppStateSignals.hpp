#pragma once

#include <QObject>
#include <QUdpSocket>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <f1x/openauto/autoapp/Configuration/Configuration.hpp>


namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace state
{

class AppStateSignals : public QObject
{
    Q_OBJECT

public:
    explicit AppStateSignals(boost::asio::io_service& ioService, configuration::IConfiguration::Pointer configuration, QObject* parent = nullptr);
    virtual ~AppStateSignals() = default;

    boost::signals2::signal<void (bool)> changeVideoFocus;
    boost::signals2::signal<void (bool)> videoFocusRequest;

private:
    boost::asio::io_service& ioService_;
    configuration::IConfiguration::Pointer configuration_;
    QHostAddress groupaddr_;
    qint16 groupport_;
    QUdpSocket controlsock_;
};

}
}
}
}
