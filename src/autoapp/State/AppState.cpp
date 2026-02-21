#include <f1x/openauto/autoapp/State/AppState.hpp>

namespace f1x {
  namespace openauto {
    namespace autoapp {
      namespace state {

        AppStateSignals::AppStateSignals(boost::asio::io_service &ioService) : ioService_(ioService) {}

        AppState::AppState(boost::asio::io_service &ioService) : appsignals(AppStateSignals(ioService)), ioService_(ioService) {}
      }
    }
  }
}
