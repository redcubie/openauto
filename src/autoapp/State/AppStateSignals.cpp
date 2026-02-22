#include <f1x/openauto/autoapp/State/AppStateSignals.hpp>
#include <f1x/openauto/Common/Log.hpp>

namespace f1x {
namespace openauto {
namespace autoapp {
namespace state {

  AppStateSignals::AppStateSignals(boost::asio::io_service &ioService, configuration::IConfiguration::Pointer configuration,
                                   QObject *parent)
    : ioService_(ioService), configuration_(configuration), controlsock_(QUdpSocket(parent)) {

    if (configuration_->getControlSocketEnabled()) {
      groupaddr_ = QHostAddress(QString::fromStdString(configuration_->getControlSocketAddress()));
      groupport_ = configuration_->getControlSocketPort();

      controlsock_.setSocketOption(QAbstractSocket::SocketOption::MulticastLoopbackOption, 1);
      controlsock_.bind(groupaddr_, groupport_, QAbstractSocket::BindFlag::ReuseAddressHint);
      controlsock_.joinMulticastGroup(groupaddr_);

      QObject::connect(&controlsock_, &QUdpSocket::readyRead, [this]() {
        char data[1024];
        size_t reallen = 0;
        reallen = controlsock_.readDatagram(data, 1024);
        OPENAUTO_LOG(debug) << "[AppStateSignals] received datagram";

        ioService_.dispatch([this, &reallen, &data]() {
          if (reallen < 1)
            return;

          switch (data[0]) {
            case VIDEO_FOCUS_RESPONSE:
              if (reallen < 2)
                return;
              changeVideoFocus(static_cast<bool>(data[1]));
              break;

            // ignore our own requests
            case VIDEO_FOCUS_REQUEST:
              break;

            default:
              OPENAUTO_LOG(error) << "[AppStateSignals] received unknown datagram";
              break;
          }
        });
      });
    }

    videoFocusRequest.connect([this](bool shown) { handle_videoFocusRequest(shown); });
  }

  void AppStateSignals::handle_videoFocusRequest(bool shown) {
    if (configuration_->getControlSocketEnabled()) {
      // send request to os menu handler
      ioService_.dispatch([this, &shown]() {
        char data[] = {VIDEO_FOCUS_REQUEST, shown};
        OPENAUTO_LOG(debug) << "[AppStateSignals] sending datagram";
        uint64_t res;
        res = controlsock_.writeDatagram(data, sizeof(data), groupaddr_, groupport_);
        OPENAUTO_LOG(debug) << "[AppStateSignals] datagram result " << res;
      });
    }

    if (configuration_->getControlSocketBypass()) {
      ioService_.dispatch([this, &shown]() { changeVideoFocus(shown); });
    }
  }

}
}
}
}
