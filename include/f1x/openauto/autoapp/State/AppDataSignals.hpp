#pragma once

#include <QObject>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <f1x/openauto/Common/Log.hpp>
#include <f1x/openauto/autoapp/Configuration/Configuration.hpp>


namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace state
{

class AppDataSignals : public QObject
{
    Q_OBJECT

public:
    explicit AppDataSignals(boost::asio::io_service &ioService, configuration::IConfiguration::Pointer configuration, QObject *parent = nullptr);
    virtual ~AppDataSignals() = default;

private:
    boost::asio::io_service& ioService_;
    configuration::IConfiguration::Pointer configuration_;
};

}
}
}
}
