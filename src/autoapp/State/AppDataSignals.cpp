#include <f1x/openauto/autoapp/State/AppDataSignals.hpp>


namespace f1x {
namespace openauto {
namespace autoapp {
namespace state {

  AppDataSignals::AppDataSignals(boost::asio::io_service &ioService, configuration::IConfiguration::Pointer configuration,
                                 QObject *parent)
    : ioService_(ioService), configuration_(configuration) {}

}
}
}
}
