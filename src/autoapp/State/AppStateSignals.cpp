#include <f1x/openauto/autoapp/State/AppStateSignals.hpp>
#include <f1x/openauto/Common/Log.hpp>

namespace f1x {
namespace openauto {
namespace autoapp {
namespace state {

  const QHostAddress AppStateSignals::groupaddr_ = QHostAddress(QString("224.7.7.7"));
  const qint16 AppStateSignals::groupport_ = 7777;

  AppStateSignals::AppStateSignals(boost::asio::io_service &ioService, QObject *parent)
    : ioService_(ioService), controlsock_(QUdpSocket(parent)) {
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
