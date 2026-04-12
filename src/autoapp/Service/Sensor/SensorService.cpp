/*
*  This file is part of openauto project.
*  Copyright (C) 2018 f1x.studio (Michal Szwaj)
*
*  openauto is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.

*  openauto is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with openauto. If not, see <http://www.gnu.org/licenses/>.
*/


#include <f1x/openauto/Common/Log.hpp>
#include <f1x/openauto/autoapp/Service/Sensor/SensorService.hpp>

namespace f1x::openauto::autoapp::service::sensor {
  SensorService::SensorService(boost::asio::io_service &ioService, aasdk::messenger::IMessenger::Pointer messenger,
                               state::AppState::Pointer appstate)
    : strand_(ioService), timer_(ioService),
      channel_(std::make_shared<aasdk::channel::sensorsource::SensorSourceService>(strand_, std::move(messenger))),
      appstate_(std::move(appstate)), signalconns_(std::vector<boost::signals2::connection>()) {}

  void SensorService::start() {
    strand_.dispatch([this, self = this->shared_from_this()]() {
      OPENAUTO_LOG(info) << "[SensorService] start()";

      channel_->receive(this->shared_from_this());
    });

  }

  void SensorService::stop() {
    strand_.dispatch([this, self = this->shared_from_this()]() {
      OPENAUTO_LOG(info) << "[SensorService] stop()";

      for (auto &conn : signalconns_) {
        conn.disconnect();
      }
    });
  }

  void SensorService::pause() {
    strand_.dispatch([this, self = this->shared_from_this()]() {
      OPENAUTO_LOG(info) << "[SensorService] pause()";
    });
  }

  void SensorService::resume() {
    strand_.dispatch([this, self = this->shared_from_this()]() {
      OPENAUTO_LOG(info) << "[SensorService] resume()";
    });
  }

  void SensorService::fillFeatures(
      aap_protobuf::service::control::message::ServiceDiscoveryResponse &response) {
    OPENAUTO_LOG(info) << "[SensorService] fillFeatures()";

    auto *service = response.add_channels();
    service->set_id(static_cast<uint32_t>(channel_->getId()));

    auto *sensorChannel = service->mutable_sensor_source_service();
    sensorChannel->add_sensors()->set_sensor_type(
        aap_protobuf::service::sensorsource::message::SensorType::SENSOR_DRIVING_STATUS_DATA);
    sensorChannel->add_sensors()->set_sensor_type(
        aap_protobuf::service::sensorsource::message::SensorType::SENSOR_NIGHT_MODE);
  }

  void SensorService::onChannelOpenRequest(const aap_protobuf::service::control::message::ChannelOpenRequest &request) {
    OPENAUTO_LOG(info) << "[SensorService] onChannelOpenRequest()";
    OPENAUTO_LOG(debug) << "[SensorService] Channel Id: " << request.service_id() << ", Priority: "
                        << request.priority();

    aap_protobuf::service::control::message::ChannelOpenResponse response;
    const aap_protobuf::shared::MessageStatus status = aap_protobuf::shared::MessageStatus::STATUS_SUCCESS;
    response.set_status(status);

    auto promise = aasdk::channel::SendPromise::defer(strand_);
    promise->then([]() {},
                  std::bind(&SensorService::onChannelError, this->shared_from_this(), std::placeholders::_1));
    channel_->sendChannelOpenResponse(response, std::move(promise));

    channel_->receive(this->shared_from_this());
  }

  void SensorService::onSensorStartRequest(
      const aap_protobuf::service::sensorsource::message::SensorRequest &request) {
    OPENAUTO_LOG(info) << "[SensorService] onSensorStartRequest()";
    OPENAUTO_LOG(debug) << "[SensorService] Request Type: " << request.type();

    aap_protobuf::service::sensorsource::message::SensorStartResponseMessage response;
    response.set_status(aap_protobuf::shared::MessageStatus::STATUS_SUCCESS);

    auto promise = aasdk::channel::SendPromise::defer(strand_);

    if (request.type() == aap_protobuf::service::sensorsource::message::SENSOR_DRIVING_STATUS_DATA) {
      promise->then(std::bind(&SensorService::sendDrivingStatusUnrestricted, this->shared_from_this()),
                    std::bind(&SensorService::onChannelError, this->shared_from_this(), std::placeholders::_1));
    } else if (request.type() == aap_protobuf::service::sensorsource::message::SensorType::SENSOR_NIGHT_MODE) {
      promise->then(std::bind(&SensorService::sendNightData, this->shared_from_this()),
                    std::bind(&SensorService::onChannelError, this->shared_from_this(), std::placeholders::_1));
    } else {
      promise->then([]() {},
                    std::bind(&SensorService::onChannelError, this->shared_from_this(), std::placeholders::_1));
    }

    channel_->sendSensorStartResponse(response, std::move(promise));
    channel_->receive(this->shared_from_this());
  }

  void SensorService::sendDrivingStatusUnrestricted() {
    OPENAUTO_LOG(info) << "[SensorService] sendDrivingStatusUnrestricted()";
    aap_protobuf::service::sensorsource::message::SensorBatch indication;
    indication.add_driving_status_data()->set_status(
        aap_protobuf::service::sensorsource::message::DrivingStatus::DRIVE_STATUS_UNRESTRICTED);

    auto promise = aasdk::channel::SendPromise::defer(strand_);
    promise->then([]() {},
                  std::bind(&SensorService::onChannelError, this->shared_from_this(), std::placeholders::_1));
    channel_->sendSensorEventIndication(indication, std::move(promise));
  }

  void SensorService::sendNightData() {
    OPENAUTO_LOG(info) << "[SensorService] sendNightData()";
    aap_protobuf::service::sensorsource::message::SensorBatch indication;

    if (SensorService::isNight) {
      OPENAUTO_LOG(info) << "[SensorService] Night Mode Triggered";
      indication.add_night_mode_data()->set_night_mode(true);
    } else {
      OPENAUTO_LOG(info) << "[SensorService] Day Mode Triggered";
      indication.add_night_mode_data()->set_night_mode(false);
    }

    auto promise = aasdk::channel::SendPromise::defer(strand_);
    promise->then([]() {},
                  std::bind(&SensorService::onChannelError, this->shared_from_this(), std::placeholders::_1));
    channel_->sendSensorEventIndication(indication, std::move(promise));
    if (this->firstRun) {
      this->firstRun = false;
      this->previous = this->isNight;
    }
  }

  void SensorService::onChannelError(const aasdk::error::Error &e) {
    OPENAUTO_LOG(error) << "[SensorService] onChannelError(): " << e.what();
  }
}
