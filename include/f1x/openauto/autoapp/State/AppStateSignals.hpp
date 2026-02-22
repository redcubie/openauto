#pragma once

#include <QObject>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>


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
    explicit AppStateSignals(boost::asio::io_service& ioService);
    virtual ~AppStateSignals() = default;

    boost::signals2::signal<void (bool)> changeVideoFocus;
    boost::signals2::signal<void (bool)> videoFocusRequest;

private:
    boost::asio::io_service& ioService_;
};

}
}
}
}
