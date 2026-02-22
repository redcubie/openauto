#include <f1x/openauto/autoapp/State/AppState.hpp>

namespace f1x {
  namespace openauto {
    namespace autoapp {
      namespace state {

        AppState::AppState(boost::asio::io_service &ioService, configuration::IConfiguration::Pointer configuration, QObject *parent)
          : appsignals(AppStateSignals(ioService, configuration, parent)), configuration(configuration), ioService_(ioService) {}
      }
    }
  }
}
