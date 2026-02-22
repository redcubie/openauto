#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include <f1x/openauto/autoapp/State/AppStateSignals.hpp>


namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace state
{

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
