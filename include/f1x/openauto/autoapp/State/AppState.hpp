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

private:
    boost::asio::io_service& ioService_;
};

class AppState
{

public:
    typedef std::shared_ptr<AppState> Pointer;
    explicit AppState(boost::asio::io_service& ioService);
    virtual ~AppState() = default;

    AppStateSignals appsignals;

protected:

private:
    boost::asio::io_service& ioService_;
};

}
}
}
}
