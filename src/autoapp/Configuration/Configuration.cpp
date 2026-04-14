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

#include <f1x/openauto/autoapp/Configuration/Configuration.hpp>
#include <f1x/openauto/Common/Log.hpp>
#include <QTouchDevice>




namespace f1x::openauto::autoapp::configuration
{

const std::string Configuration::cGeneralShowClockKey = "General.ShowClock";

const std::string Configuration::cGeneralShowBigClockKey = "General.ShowBigClock";
const std::string Configuration::cGeneralOldGUIKey = "General.OldGUI";
const std::string Configuration::cGeneralAlphaTransKey = "General.AlphaTrans";
const std::string Configuration::cGeneralHideMenuToggleKey = "General.HideMenuToggle";
const std::string Configuration::cGeneralHideAlphaKey = "General.HideAlpha";
const std::string Configuration::cGeneralShowLuxKey = "General.ShowLux";
const std::string Configuration::cGeneralShowCursorKey = "General.ShowCursor";
const std::string Configuration::cGeneralHideBrightnessControlKey = "General.HideBrightnessControl";
const std::string Configuration::cGeneralShowNetworkinfoKey = "General.ShowNetworkinfo";
const std::string Configuration::cGeneralHideWarningKey = "General.HideWarning";

const std::string Configuration::cGeneralDriverPositionKey = "General.DriverPosition";
const std::string Configuration::cMetadataDisplayNameKey = "Metadata.DisplayName";
const std::string Configuration::cMetadataVehicleMakeKey = "Metadata.VehicleMake";
const std::string Configuration::cMetadataVehicleModelKey = "Metadata.VehicleModel";
const std::string Configuration::cMetadataVehicleYearKey = "Metadata.VehicleYear";
const std::string Configuration::cMetadataVehicleIDKey = "Metadata.VehicleID";
const std::string Configuration::cMetadataHeadUnitMakeKey = "Metadata.HeadUnitMake";
const std::string Configuration::cMetadataHeadUnitModelKey = "Metadata.HeadUnitModel";
const std::string Configuration::cMetadataHeadUnitSoftwareVersionKey = "Metadata.HeadUnitSoftwareVersion";
const std::string Configuration::cMetadataHeadUnitSoftwareBuildKey = "Metadata.HeadUnitSoftwareBuild";

const std::string Configuration::cControlSocketEnabledKey = "ControlSocket.Enabled";
const std::string Configuration::cControlSocketAddressKey = "ControlSocket.Address";
const std::string Configuration::cControlSocketPortKey = "ControlSocket.Port";
const std::string Configuration::cControlSocketBypassKey = "ControlSocket.Bypass";

const std::string Configuration::cVideoFPSKey = "Video.FPS";
const std::string Configuration::cVideoResolutionKey = "Video.Resolution";
const std::string Configuration::cVideoScreenDPIKey = "Video.ScreenDPI";
const std::string Configuration::cVideoOMXLayerIndexKey = "Video.OMXLayerIndex";
const std::string Configuration::cVideoMarginWidth = "Video.MarginWidth";
const std::string Configuration::cVideoMarginHeight = "Video.MarginHeight";

const std::string Configuration::cAudioChannelMediaEnabled = "AudioChannel.MediaEnabled";
const std::string Configuration::cAudioChannelGuidanceEnabled = "AudioChannel.GuidanceEnabled";
const std::string Configuration::cAudioChannelSystemEnabled = "AudioChannel.SystemEnabled";
const std::string Configuration::cAudioChannelTelephonyEnabled = "AudioChannel.TelephonyEnabled";

const std::string Configuration::cAudioOutputBackendType = "Audio.OutputBackendType";

const std::string Configuration::cBluetoothAdapterTypeKey = "Bluetooth.AdapterType";
const std::string Configuration::cBluetoothAdapterAddressKey = "Bluetooth.AdapterAddress";
const std::string Configuration::cBluetoothWirelessProjectionEnabledKey = "Bluetooth.WirelessProjectionEnabled";

const std::string Configuration::cInputEnableTouchscreenKey = "Input.EnableTouchscreen";
const std::string Configuration::cInputEnablePlayerControlKey = "Input.EnablePlayerControl";
const std::string Configuration::cInputPlayButtonKey = "Input.PlayButton";
const std::string Configuration::cInputPauseButtonKey = "Input.PauseButton";
const std::string Configuration::cInputTogglePlayButtonKey = "Input.TogglePlayButton";
const std::string Configuration::cInputNextTrackButtonKey = "Input.NextTrackButton";
const std::string Configuration::cInputPreviousTrackButtonKey = "Input.PreviousTrackButton";
const std::string Configuration::cInputHomeButtonKey = "Input.HomeButton";
const std::string Configuration::cInputPhoneButtonKey = "Input.PhoneButton";
const std::string Configuration::cInputCallEndButtonKey = "Input.CallEndButton";
const std::string Configuration::cInputVoiceCommandButtonKey = "Input.VoiceCommandButton";
const std::string Configuration::cInputLeftButtonKey = "Input.LeftButton";
const std::string Configuration::cInputRightButtonKey = "Input.RightButton";
const std::string Configuration::cInputUpButtonKey = "Input.UpButton";
const std::string Configuration::cInputDownButtonKey = "Input.DownButton";
const std::string Configuration::cInputScrollWheelButtonKey = "Input.ScrollWheelButton";
const std::string Configuration::cInputBackButtonKey = "Input.BackButton";
const std::string Configuration::cInputEnterButtonKey = "Input.EnterButton";
const std::string Configuration::cInputNavButtonKey = "Input.NavButton";

Configuration::Configuration(std::string filename)
{
    this->ConfigFileName_ = filename;
    this->load();
}

void Configuration::load()
{
    boost::property_tree::ptree iniConfig;

    try
    {
        boost::property_tree::ini_parser::read_ini(ConfigFileName_, iniConfig);

        driverPosition_ = static_cast<aap_protobuf::service::control::message::DriverPosition>(iniConfig.get<uint32_t>(
            cGeneralDriverPositionKey, aap_protobuf::service::control::message::DriverPosition::DRIVER_POSITION_LEFT));

        showClock_ = iniConfig.get<bool>(cGeneralShowClockKey, true);
        showBigClock_ = iniConfig.get<bool>(cGeneralShowBigClockKey, false);
        oldGUI_ = iniConfig.get<bool>(cGeneralOldGUIKey, false);
        alphaTrans_ = iniConfig.get<size_t>(cGeneralAlphaTransKey, 50);
        hideMenuToggle_ = iniConfig.get<bool>(cGeneralHideMenuToggleKey, false);
        hideAlpha_ = iniConfig.get<bool>(cGeneralHideAlphaKey, false);
        showLux_ = iniConfig.get<bool>(cGeneralShowLuxKey, false);
        showCursor_ = iniConfig.get<bool>(cGeneralShowCursorKey, false);
        hideBrightnessControl_ = iniConfig.get<bool>(cGeneralHideBrightnessControlKey, false);
        hideWarning_ = iniConfig.get<bool>(cGeneralHideWarningKey, false);
        showNetworkinfo_ = iniConfig.get<bool>(cGeneralShowNetworkinfoKey, false);
        displayName_ = iniConfig.get<std::string>(cMetadataDisplayNameKey, "Openauto");
        vehicleMake_ = iniConfig.get<std::string>(cMetadataVehicleMakeKey, "Openauto");
        vehicleModel_ = iniConfig.get<std::string>(cMetadataVehicleModelKey, "Openauto");
        vehicleYear_ = iniConfig.get<std::string>(cMetadataVehicleYearKey, "2026");
        vehicleID_ = iniConfig.get<std::string>(cMetadataVehicleIDKey, "");
        headUnitMake_ = iniConfig.get<std::string>(cMetadataHeadUnitMakeKey, "f1x");
        headUnitModel_ = iniConfig.get<std::string>(cMetadataHeadUnitModelKey, "Crankshaft-NG Autoapp");
        headUnitSoftwareVersion_ = iniConfig.get<std::string>(cMetadataHeadUnitSoftwareVersionKey, "1.0");
        headUnitSoftwareBuild_ = iniConfig.get<std::string>(cMetadataHeadUnitSoftwareBuildKey, "1");

        controlSocketEnabled_ = iniConfig.get<bool>(cControlSocketEnabledKey, false);
        controlSocketAddress_ = iniConfig.get<std::string>(cControlSocketAddressKey, "");
        controlSocketPort_ = iniConfig.get<uint16_t>(cControlSocketPortKey, 0);
        controlSocketBypass_ = iniConfig.get<bool>(cControlSocketBypassKey, true);

        videoFPS_ = static_cast<aap_protobuf::service::media::sink::message::VideoFrameRateType>(iniConfig.get<uint32_t>(cVideoFPSKey,
                                                                                             aap_protobuf::service::media::sink::message::VideoFrameRateType::VIDEO_FPS_30));

        videoResolution_ = static_cast<aap_protobuf::service::media::sink::message::VideoCodecResolutionType>(iniConfig.get<uint32_t>(cVideoResolutionKey,
                                                                                                           aap_protobuf::service::media::sink::message::VideoCodecResolutionType::VIDEO_800x480));
        screenDPI_ = iniConfig.get<size_t>(cVideoScreenDPIKey, 140);

        omxLayerIndex_ = iniConfig.get<int32_t>(cVideoOMXLayerIndexKey, 1);
        videoMargins_ = QRect(0, 0, iniConfig.get<int32_t>(cVideoMarginWidth, 0), iniConfig.get<int32_t>(cVideoMarginHeight, 0));

        enableTouchscreen_ = iniConfig.get<bool>(cInputEnableTouchscreenKey, true);
        enablePlayerControl_ = iniConfig.get<bool>(cInputEnablePlayerControlKey, false);
        this->readButtonCodes(iniConfig);

        bluetoothAdapterType_ = static_cast<BluetoothAdapterType>(iniConfig.get<uint32_t>(cBluetoothAdapterTypeKey,
                                                                                          static_cast<uint32_t>(BluetoothAdapterType::NONE)));

        wirelessProjectionEnabled_ = iniConfig.get<bool>(cBluetoothWirelessProjectionEnabledKey, true);

        bluetoothAdapterAddress_ = iniConfig.get<std::string>(cBluetoothAdapterAddressKey, "");

        _audioChannelEnabledMedia = iniConfig.get<bool>(cAudioChannelMediaEnabled, true);
        _audioChannelEnabledGuidance = iniConfig.get<bool>(cAudioChannelGuidanceEnabled, true);
        _audioChannelEnabledSystem = iniConfig.get<bool>(cAudioChannelSystemEnabled, true);
        _audioChannelEnabledTelephony = iniConfig.get<bool>(cAudioChannelTelephonyEnabled, true);

         audioOutputBackendType_ = static_cast<AudioOutputBackendType>(iniConfig.get<uint32_t>(cAudioOutputBackendType, static_cast<uint32_t>(AudioOutputBackendType::RTAUDIO)));
    }
    catch(const boost::property_tree::ini_parser_error& e)
    {
        OPENAUTO_LOG(warning) << "[Configuration] failed to read configuration file: " << ConfigFileName_
                            << ", error: " << e.what()
                            << ". Using default configuration.";
        this->reset();
    }
}

void Configuration::reset()
{
    driverPosition_ = aap_protobuf::service::control::message::DriverPosition::DRIVER_POSITION_LEFT;
    showClock_ = true;
    showBigClock_ = false;
    oldGUI_ = false;
    alphaTrans_ = 50;
    hideMenuToggle_ = false;
    hideAlpha_ = false;
    showLux_ = false;
    showCursor_ = false;
    hideBrightnessControl_ = false;
    hideWarning_ = false;
    displayName_ = "Openauto";
    vehicleMake_ = "Openauto";
    vehicleModel_ = "Openauto";
    vehicleYear_ = "2026";
    vehicleID_ = "";
    headUnitMake_ = "f1x";
    headUnitModel_ = "Crankshaft-NG Autoapp";
    headUnitSoftwareVersion_ = "1.0";
    headUnitSoftwareBuild_ = "1";
    controlSocketEnabled_ = false;
    controlSocketAddress_ = "";
    controlSocketPort_ = 0;
    controlSocketBypass_ = true;
    showNetworkinfo_ = false;
    videoFPS_ = aap_protobuf::service::media::sink::message::VideoFrameRateType::VIDEO_FPS_30;
    videoResolution_ = aap_protobuf::service::media::sink::message::VideoCodecResolutionType::VIDEO_800x480;
    screenDPI_ = 140;
    omxLayerIndex_ = 1;
    videoMargins_ = QRect(0, 0, 0, 0);
    enableTouchscreen_ = true;
    enablePlayerControl_ = false;
    buttonCodes_.clear();
    bluetoothAdapterType_ = BluetoothAdapterType::NONE;
    bluetoothAdapterAddress_ = "";

   _audioChannelEnabledMedia = true;
   _audioChannelEnabledGuidance = true;
   _audioChannelEnabledSystem = true;
   _audioChannelEnabledTelephony = true;

    audioOutputBackendType_ = AudioOutputBackendType::QT;
    wirelessProjectionEnabled_ = true;
}

void Configuration::save()
{
    boost::property_tree::ptree iniConfig;
    iniConfig.put<uint32_t>(cGeneralDriverPositionKey, static_cast<uint32_t>(driverPosition_));

    iniConfig.put<bool>(cGeneralShowClockKey, showClock_);
    iniConfig.put<bool>(cGeneralShowBigClockKey, showBigClock_);
    iniConfig.put<bool>(cGeneralOldGUIKey, oldGUI_);
    iniConfig.put<size_t>(cGeneralAlphaTransKey, alphaTrans_);
    iniConfig.put<bool>(cGeneralHideMenuToggleKey, hideMenuToggle_);
    iniConfig.put<bool>(cGeneralHideAlphaKey, hideAlpha_);
    iniConfig.put<bool>(cGeneralShowLuxKey, showLux_);
    iniConfig.put<bool>(cGeneralShowCursorKey, showCursor_);
    iniConfig.put<bool>(cGeneralHideBrightnessControlKey, hideBrightnessControl_);
    iniConfig.put<bool>(cGeneralHideWarningKey, hideWarning_);
    iniConfig.put<bool>(cGeneralShowNetworkinfoKey, showNetworkinfo_);
    iniConfig.put<std::string>(cMetadataDisplayNameKey, displayName_);
    iniConfig.put<std::string>(cMetadataVehicleMakeKey, vehicleMake_);
    iniConfig.put<std::string>(cMetadataVehicleModelKey, vehicleModel_);
    iniConfig.put<std::string>(cMetadataVehicleYearKey, vehicleYear_);
    iniConfig.put<std::string>(cMetadataVehicleIDKey, vehicleID_);
    iniConfig.put<std::string>(cMetadataHeadUnitMakeKey, headUnitMake_);
    iniConfig.put<std::string>(cMetadataHeadUnitModelKey, headUnitModel_);
    iniConfig.put<std::string>(cMetadataHeadUnitSoftwareVersionKey, headUnitSoftwareVersion_);
    iniConfig.put<std::string>(cMetadataHeadUnitSoftwareBuildKey, headUnitSoftwareBuild_);

    iniConfig.put<bool>(cControlSocketEnabledKey, controlSocketEnabled_);
    iniConfig.put<std::string>(cControlSocketAddressKey, controlSocketAddress_);
    iniConfig.put<uint16_t>(cControlSocketPortKey, controlSocketPort_);
    iniConfig.put<bool>(cControlSocketBypassKey, controlSocketBypass_);


    iniConfig.put<uint32_t>(cVideoFPSKey, static_cast<uint32_t>(videoFPS_));
    iniConfig.put<uint32_t>(cVideoResolutionKey, static_cast<uint32_t>(videoResolution_));
    iniConfig.put<size_t>(cVideoScreenDPIKey, screenDPI_);
    iniConfig.put<int32_t>(cVideoOMXLayerIndexKey, omxLayerIndex_);
    iniConfig.put<uint32_t>(cVideoMarginWidth, videoMargins_.width());
    iniConfig.put<uint32_t>(cVideoMarginHeight, videoMargins_.height());

    iniConfig.put<bool>(cInputEnableTouchscreenKey, enableTouchscreen_);
    iniConfig.put<bool>(cInputEnablePlayerControlKey, enablePlayerControl_);
    this->writeButtonCodes(iniConfig);

    iniConfig.put<uint32_t>(cBluetoothAdapterTypeKey, static_cast<uint32_t>(bluetoothAdapterType_));
    iniConfig.put<std::string>(cBluetoothAdapterAddressKey, bluetoothAdapterAddress_);
    iniConfig.put<bool>(cBluetoothWirelessProjectionEnabledKey, wirelessProjectionEnabled_);

    iniConfig.put<bool>(cAudioChannelMediaEnabled, _audioChannelEnabledMedia);
    iniConfig.put<bool>(cAudioChannelGuidanceEnabled, _audioChannelEnabledGuidance);
    iniConfig.put<bool>(cAudioChannelSystemEnabled, _audioChannelEnabledSystem);
    iniConfig.put<bool>(cAudioChannelTelephonyEnabled, _audioChannelEnabledTelephony);

  iniConfig.put<uint32_t>(cAudioOutputBackendType, static_cast<uint32_t>(audioOutputBackendType_));
    boost::property_tree::ini_parser::write_ini(ConfigFileName_, iniConfig);
}

bool Configuration::hasTouchScreen() const
{
    auto touchdevs = QTouchDevice::devices();

    OPENAUTO_LOG(info) << "[Touchdev] " <<
                          "Querying available touch devices [" <<
                          touchdevs.length() << " available]";

    for (int i = 0; i < touchdevs.length(); i++) {
        if (touchdevs[i]->type() == QTouchDevice::TouchScreen) {
            OPENAUTO_LOG(info) << "[Touchdev] Device " << i <<
                                  ": " << touchdevs[i]->name().toStdString() <<
                                  ", type " << touchdevs[i]->type();
            return true;
        }
    }
    return false;
}

void Configuration::setDriverPosition(aap_protobuf::service::control::message::DriverPosition value)
{
    driverPosition_ = value;
}

aap_protobuf::service::control::message::DriverPosition Configuration::getDriverPosition() const
{
    return driverPosition_;
}

void Configuration::showClock(bool value)
{
    showClock_ = value;
}

bool Configuration::showClock() const
{
    return showClock_;
}

void Configuration::showBigClock(bool value)
{
    showBigClock_ = value;
}

bool Configuration::showBigClock() const
{
    return showBigClock_;
}

void Configuration::oldGUI(bool value)
{
    oldGUI_ = value;
}

bool Configuration::oldGUI() const
{
    return oldGUI_;
}

size_t Configuration::getAlphaTrans() const
{
    return alphaTrans_;
}

void Configuration::setAlphaTrans(size_t value)
{
    alphaTrans_ = value;
}

void Configuration::hideMenuToggle(bool value)
{
    hideMenuToggle_ = value;
}

bool Configuration::hideMenuToggle() const
{
    return hideMenuToggle_;
}

void Configuration::hideAlpha(bool value)
{
    hideAlpha_ = value;
}

bool Configuration::hideAlpha() const
{
    return hideAlpha_;
}

void Configuration::showLux(bool value)
{
    showLux_ = value;
}

bool Configuration::showLux() const
{
    return showLux_;
}

void Configuration::showCursor(bool value)
{
    showCursor_ = value;
}

bool Configuration::showCursor() const
{
    return showCursor_;
}

void Configuration::hideBrightnessControl(bool value)
{
    hideBrightnessControl_ = value;
}

bool Configuration::hideBrightnessControl() const
{
    return hideBrightnessControl_;
}

void Configuration::hideWarning(bool value)
{
    hideWarning_ = value;
}

bool Configuration::hideWarning() const
{
    return hideWarning_;
}

void Configuration::showNetworkinfo(bool value)
{
    showNetworkinfo_ = value;
}

bool Configuration::showNetworkinfo() const
{
    return showNetworkinfo_;
}

std::string Configuration::getDisplayName() const
{
    return displayName_;
}

void Configuration::setDisplayName(const std::string &value)
{
    displayName_ = value;
}

std::string Configuration::getVehicleMake() const
{
    return vehicleMake_;
}

void Configuration::setVehicleMake(const std::string &value)
{
    vehicleMake_ = value;
}

std::string Configuration::getVehicleModel() const
{
    return vehicleModel_;
}

void Configuration::setVehicleModel(const std::string &value)
{
    vehicleModel_ = value;
}

std::string Configuration::getVehicleYear() const
{
    return vehicleYear_;
}

void Configuration::setVehicleYear(const std::string &value)
{
    vehicleYear_ = value;
}

std::string Configuration::getVehicleID() const
{
    return vehicleID_;
}

void Configuration::setVehicleID(const std::string &value)
{
    vehicleID_ = value;
}

std::string Configuration::getHeadUnitMake() const
{
    return headUnitMake_;
}
void Configuration::setHeadUnitMake(const std::string &value)
{
    headUnitMake_ = value;
}

std::string Configuration::getHeadUnitModel() const
{
    return headUnitModel_;
}

void Configuration::setHeadUnitModel(const std::string &value)
{
    headUnitModel_ = value;
}

std::string Configuration::getHeadUnitSoftwareVersion() const
{
    return headUnitSoftwareVersion_;
}

void Configuration::setHeadUnitSoftwareVersion(const std::string &value)
{
    headUnitSoftwareVersion_ = value;
}

std::string Configuration::getHeadUnitSoftwareBuild() const
{
    return headUnitSoftwareBuild_;
}

void Configuration::setHeadUnitSoftwareBuild(const std::string &value)
{
    headUnitSoftwareBuild_ = value;
}

bool Configuration::getControlSocketEnabled() const
{
    return controlSocketEnabled_;
}
void Configuration::setControlSocketEnabled(const bool value)
{
    controlSocketEnabled_ = value;
}
std::string Configuration::getControlSocketAddress() const
{
    return controlSocketAddress_;
}
void Configuration::setControlSocketAddress(const std::string& value)
{
    controlSocketAddress_ = value;
}
uint16_t Configuration::getControlSocketPort() const
{
    return controlSocketPort_;
}
void Configuration::setControlSocketPort(const uint16_t value)
{
    controlSocketPort_ = value;
}
bool Configuration::getControlSocketBypass() const
{
    return controlSocketBypass_;
}
void Configuration::setControlSocketBypass(const bool value)
{
    controlSocketBypass_ = value;
}

aap_protobuf::service::media::sink::message::VideoFrameRateType Configuration::getVideoFPS() const
{
    return videoFPS_;
}

void Configuration::setVideoFPS(aap_protobuf::service::media::sink::message::VideoFrameRateType value)
{
    videoFPS_ = value;
}

aap_protobuf::service::media::sink::message::VideoCodecResolutionType Configuration::getVideoResolution() const
{
    return videoResolution_;
}

void Configuration::setVideoResolution(aap_protobuf::service::media::sink::message::VideoCodecResolutionType value)
{
    videoResolution_ = value;
}

size_t Configuration::getScreenDPI() const
{
    return screenDPI_;
}

void Configuration::setScreenDPI(size_t value)
{
    screenDPI_ = value;
}

void Configuration::setOMXLayerIndex(int32_t value)
{
    omxLayerIndex_ = value;
}

int32_t Configuration::getOMXLayerIndex() const
{
    return omxLayerIndex_;
}

void Configuration::setVideoMargins(QRect value)
{
    videoMargins_ = value;
}

QRect Configuration::getVideoMargins() const
{
    return videoMargins_;
}

bool Configuration::getTouchscreenEnabled() const
{
    return enableTouchscreen_;
}

void Configuration::setTouchscreenEnabled(bool value)
{
    enableTouchscreen_ = value;
}

Configuration::ButtonCodes Configuration::getButtonCodes() const
{
    return buttonCodes_;
}

void Configuration::setButtonCodes(const ButtonCodes& value)
{
    buttonCodes_ = value;
}

BluetoothAdapterType Configuration::getBluetoothAdapterType() const
{
    return bluetoothAdapterType_;
}

void Configuration::setBluetoothAdapterType(BluetoothAdapterType value)
{
    bluetoothAdapterType_ = value;
}

std::string Configuration::getBluetoothAdapterAddress() const
{
    return bluetoothAdapterAddress_;
}

void Configuration::setBluetoothAdapterAddress(const std::string& value)
{
    bluetoothAdapterAddress_ = value;
}

bool Configuration::getWirelessProjectionEnabled() const {
    return wirelessProjectionEnabled_;
}

void Configuration::setWirelessProjectionEnabled(bool value) {
    wirelessProjectionEnabled_ = value;
}

bool Configuration::musicAudioChannelEnabled() const
{
  return _audioChannelEnabledMedia;
}

void Configuration::setMusicAudioChannelEnabled(bool value)
{
  _audioChannelEnabledMedia = value;
}

bool Configuration::guidanceAudioChannelEnabled() const
{
    return _audioChannelEnabledGuidance;
}

void Configuration::setGuidanceAudioChannelEnabled(bool value)
{
  _audioChannelEnabledGuidance = value;
}

  bool Configuration::systemAudioChannelEnabled() const
  {
    return _audioChannelEnabledSystem;
  }

  void Configuration::setSystemAudioChannelEnabled(bool value)
  {
    _audioChannelEnabledSystem = value;
  }

  bool Configuration::telephonyAudioChannelEnabled() const
  {
    return _audioChannelEnabledTelephony;
  }

  void Configuration::setTelephonyAudioChannelEnabled(bool value)
  {
    _audioChannelEnabledTelephony = value;
  }

AudioOutputBackendType Configuration::getAudioOutputBackendType() const
{
    return audioOutputBackendType_;
}

void Configuration::setAudioOutputBackendType(AudioOutputBackendType value)
{
    audioOutputBackendType_ = value;
}

QString Configuration::getCSValue(QString searchString) const
{
    using namespace std;
    ifstream inFile;
    ifstream inFile2;
    string line;
    searchString = searchString.append("=");
    inFile.open("/boot/crankshaft/crankshaft_env.sh");
    inFile2.open("/opt/crankshaft/crankshaft_default_env.sh");

    size_t pos;

    if(inFile) {
        while(inFile.good())
        {
            getline(inFile,line); // get line from file
            if (line[0] != '#') {
                pos=line.find(searchString.toStdString()); // search
                if(pos!=std::string::npos) // string::npos is returned if string is not found
                {
                    int equalPosition = line.find("=");
                    QString value = line.substr(equalPosition + 1).c_str();
                    value.replace("\"","");
                    OPENAUTO_LOG(debug) << "[Configuration] CS param found: " << searchString.toStdString() << " Value:" << value.toStdString();
                    return value;
                }
            }
        }
        OPENAUTO_LOG(warning) << "[Configuration] unable to find cs param: " << searchString.toStdString();
        OPENAUTO_LOG(warning) << "[Configuration] Fallback to /opt/crankshaft/crankshaft_default_env.sh)";
        while(inFile2.good())
        {
            getline(inFile2,line); // get line from file
            if (line[0] != '#') {
                pos=line.find(searchString.toStdString()); // search
                if(pos!=std::string::npos) // string::npos is returned if string is not found
                {
                    int equalPosition = line.find("=");
                    QString value = line.substr(equalPosition + 1).c_str();
                    value.replace("\"","");
                    OPENAUTO_LOG(debug) << "[Configuration] CS param found: " << searchString.toStdString() << " Value:" << value.toStdString();
                    return value;
                }
            }
        }
        return "";
    } else {
        OPENAUTO_LOG(warning) << "[Configuration] unable to open cs param file (/boot/crankshaft/crankshaft_env.sh)";
        OPENAUTO_LOG(warning) << "[Configuration] Fallback to /opt/crankshaft/crankshaft_default_env.sh)";

        while(inFile2.good())
        {
            getline(inFile2,line); // get line from file
            if (line[0] != '#') {
                pos=line.find(searchString.toStdString()); // search
                if(pos!=std::string::npos) // string::npos is returned if string is not found
                {
                    int equalPosition = line.find("=");
                    QString value = line.substr(equalPosition + 1).c_str();
                    value.replace("\"","");
                    OPENAUTO_LOG(debug) << "[Configuration] CS param found: " << searchString.toStdString() << " Value:" << value.toStdString();
                    return value;
                }
            }
        }
        return "";
    }
}

QString Configuration::getParamFromFile(QString fileName, QString searchString) const
{
    OPENAUTO_LOG(debug) << "[Configuration] Request param from file: " << fileName.toStdString() << " param: " << searchString.toStdString();
    using namespace std;
    ifstream inFile;
    string line;
    if (!searchString.contains("dtoverlay")) {
        searchString = searchString.append("=");
    }
    inFile.open(fileName.toStdString());

    size_t pos;

    if(inFile) {
        while(inFile.good())
        {
            getline(inFile,line); // get line from file
            if (line[0] != '#') {
                pos=line.find(searchString.toStdString()); // search
                if(pos!=std::string::npos) // string::npos is returned if string is not found
                {
                    int equalPosition = line.find("=");
                    QString value = line.substr(equalPosition + 1).c_str();
                    value.replace("\"","");
                    OPENAUTO_LOG(debug) << "[Configuration] Param from file: " << fileName.toStdString() << " found: " << searchString.toStdString() << " Value:" << value.toStdString();
                    return value;
                }
            }
        }
        return "";
    } else {
        return "";
    }
}

QString Configuration::readFileContent(QString fileName) const
{
    using namespace std;
    ifstream inFile;
    string line;
    inFile.open(fileName.toStdString());
    string result = "";
    if(inFile) {
        while(inFile.good())
        {
            getline(inFile,line); // get line from file
            result.append(line);
        }
        return result.c_str();
    } else {
        return "";
    }
}

void Configuration::readButtonCodes(boost::property_tree::ptree& iniConfig)
{
    this->insertButtonCode(iniConfig, cInputPlayButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PLAY);
    this->insertButtonCode(iniConfig, cInputPauseButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PAUSE);
    this->insertButtonCode(iniConfig, cInputTogglePlayButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PLAY_PAUSE);
    this->insertButtonCode(iniConfig, cInputNextTrackButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_NEXT);
    this->insertButtonCode(iniConfig, cInputPreviousTrackButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PREVIOUS);
    this->insertButtonCode(iniConfig, cInputHomeButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_HOME);
    this->insertButtonCode(iniConfig, cInputPhoneButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_CALL);
    this->insertButtonCode(iniConfig, cInputCallEndButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_ENDCALL);
    this->insertButtonCode(iniConfig, cInputVoiceCommandButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_SEARCH);
    this->insertButtonCode(iniConfig, cInputLeftButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_LEFT);
    this->insertButtonCode(iniConfig, cInputRightButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_RIGHT);
    this->insertButtonCode(iniConfig, cInputUpButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_UP);
    this->insertButtonCode(iniConfig, cInputDownButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_DOWN);
    this->insertButtonCode(iniConfig, cInputScrollWheelButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_ROTARY_CONTROLLER);
    this->insertButtonCode(iniConfig, cInputBackButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_BACK);
    this->insertButtonCode(iniConfig, cInputEnterButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_CENTER);
    this->insertButtonCode(iniConfig, cInputNavButtonKey, aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_NAVIGATION);
}

void Configuration::insertButtonCode(boost::property_tree::ptree& iniConfig, const std::string& buttonCodeKey, aap_protobuf::service::media::sink::message::KeyCode buttonCode)
{
    if(iniConfig.get<bool>(buttonCodeKey, false))
    {
        buttonCodes_.push_back(buttonCode);
    }
}

void Configuration::writeButtonCodes(boost::property_tree::ptree& iniConfig)
{
    iniConfig.put<bool>(cInputPlayButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PLAY) != buttonCodes_.end());
    iniConfig.put<bool>(cInputPauseButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PAUSE) != buttonCodes_.end());
    iniConfig.put<bool>(cInputTogglePlayButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PLAY_PAUSE) != buttonCodes_.end());
    iniConfig.put<bool>(cInputNextTrackButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_NEXT) != buttonCodes_.end());
    iniConfig.put<bool>(cInputPreviousTrackButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_MEDIA_PREVIOUS) != buttonCodes_.end());
    iniConfig.put<bool>(cInputHomeButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_HOME) != buttonCodes_.end());
    iniConfig.put<bool>(cInputPhoneButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_CALL) != buttonCodes_.end());
    iniConfig.put<bool>(cInputCallEndButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_ENDCALL) != buttonCodes_.end());
    iniConfig.put<bool>(cInputVoiceCommandButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_SEARCH) != buttonCodes_.end());
    iniConfig.put<bool>(cInputLeftButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_LEFT) != buttonCodes_.end());
    iniConfig.put<bool>(cInputRightButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_RIGHT) != buttonCodes_.end());
    iniConfig.put<bool>(cInputUpButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_UP) != buttonCodes_.end());
    iniConfig.put<bool>(cInputDownButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_DOWN) != buttonCodes_.end());
    iniConfig.put<bool>(cInputScrollWheelButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_ROTARY_CONTROLLER) != buttonCodes_.end());
    iniConfig.put<bool>(cInputBackButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_BACK) != buttonCodes_.end());
    iniConfig.put<bool>(cInputEnterButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_DPAD_CENTER) != buttonCodes_.end());
    iniConfig.put<bool>(cInputNavButtonKey, std::find(buttonCodes_.begin(), buttonCodes_.end(), aap_protobuf::service::media::sink::message::KeyCode::KEYCODE_NAVIGATION) != buttonCodes_.end());
}

}



