#include <f1x/openauto/autoapp/State/AppState.hpp>

namespace f1x {
  namespace openauto {
    namespace autoapp {
      namespace state {

        AppState::AppState(boost::asio::io_service &ioService, QObject *parent)
          : appsignals(AppStateSignals(ioService, parent)), ioService_(ioService) {
          appsignals.videoFocusRequest.connect([this](bool show) { this->appsignals.changeVideoFocus(show); });
        }
      }
    }
  }
}
