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
        OPENAUTO_LOG(debug) << "[AppStateSignals] received datagram";
      });
    }
  }

}
}
}
}
