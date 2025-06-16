#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

#include "Nmea2kTwai.h"
#include "N2kTypes.h"
#include "N2kMessages.h"

#ifdef ARDUINO_ARCH_ESP32
#include <driver/pcnt.h>
#endif

#ifndef N2K_LOAD_LEVEL
#define N2K_LOAD_LEVEL 3
#endif

#ifndef N2K_CERTIFICATION_LEVEL
#define N2K_CERTIFICATION_LEVEL 0xff
#endif

#define ESP32_CAN_TX_PIN 20
#define ESP32_CAN_RX_PIN 19

#define MAX_NMEA2000_MESSAGE_SEASMART_SIZE 500

#define SYSTEM_NAME "Waveshare"
#define FIRMWARE_TYPE "ALPHA TESTING"
#define VERSION "0.0.1"

static const unsigned long CAN_RECOVERY_PERIOD=3000; //ms

static const unsigned long NMEA2000_HEARTBEAT_INTERVAL=5000;

static const unsigned long pgns[] = {129026UL, 129025UL};

static const unsigned long esphome_update_period = 500;

class handle129026 : public tNMEA2000::tMsgHandler{
  private:
  public:

    double COG = 0;
    double SOG = 0;

    handle129026(tNMEA2000 *_pNMEA2000) : tNMEA2000::tMsgHandler(129026,_pNMEA2000) {}
    void HandleMsg(const tN2kMsg &n2kMsg){
      // ESP_LOGD("custom", "processing message %lu", n2kMsg.PGN);
      unsigned char SID;
      tN2kHeadingReference ref;
      ParseN2kPGN129026(n2kMsg, SID, ref, COG, SOG);
    };
};
class handle129025 : public tNMEA2000::tMsgHandler{
  private:
  public:

    double LAT = 0;
    double LON = 0;

    handle129025(tNMEA2000 *_pNMEA2000) : tNMEA2000::tMsgHandler(129025,_pNMEA2000) {}
    void HandleMsg(const tN2kMsg &n2kMsg){
      // ESP_LOGD("custom", "processing message %lu", n2kMsg.PGN);
      ParseN2kPGN129025(n2kMsg, LAT, LON);
    };
};


class Nmea2kSensor : public Component, public Sensor {

 private:
  uint16_t example_count = 0;
  Nmea2kTwai *n2k;
  int NodeAddress = 32;
  handle129026 *rapid_vector_handler;
  handle129025 *rapid_position_handler;

 public:
  // constructor
  Nmea2kSensor() {
  }

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; } // wait until most hardware is setup

  Sensor *n2kstatus = new Sensor();
  Sensor *rx_error_counter = new Sensor();
  Sensor *tx_error_counter = new Sensor();
  Sensor *tx_failed = new Sensor();
  Sensor *rx_missed = new Sensor();
  Sensor *rx_overrun = new Sensor();
  Sensor *tx_timeouts = new Sensor();
  Sensor *n2kaddress = new Sensor();
  Sensor *sog = new Sensor();
  Sensor *cog = new Sensor();
  Sensor *lat = new Sensor();
  Sensor *lon = new Sensor();
  unsigned long esp_last_update = 0;
  
  void setup() override {
    // Setup NMEA Here
    uint8_t chipid[6];
    uint32_t id = 0;

    n2k = new Nmea2kTwai((gpio_num_t)ESP32_CAN_TX_PIN,(gpio_num_t)ESP32_CAN_RX_PIN,CAN_RECOVERY_PERIOD);
    n2k->SetN2kCANMsgBufSize(32);
    n2k->SetN2kCANReceiveFrameBufSize(10); // These appear to have no effect with twai
    n2k->SetN2kCANSendFrameBufSize(10); // These appear to have no effect with twai
    esp_efuse_mac_get_default(chipid);
    for (int i = 0; i < 6; i++) id += (chipid[i] << (7 * i));

    // Set product information
    n2k->SetProductInformation("1", // Manufacturer's Model serial code
                                 100, // Manufacturer's product code
                                 SYSTEM_NAME,  // Manufacturer's Model ID
                                 FIRMWARE_TYPE,  // Manufacturer's Software version code
                                 VERSION, // Manufacturer's Model version,
                                 N2K_LOAD_LEVEL,
                                 0xffff, //Version
                                 N2K_CERTIFICATION_LEVEL
                                );
    // Set device information
    n2k->SetDeviceInformation(id, // Unique number. Use e.g. Serial number. Id is generated from MAC-Address
                                    130, // Device function=Analog to NMEA 2000 Gateway. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                    25, // Device class=Inter/Intranetwork Device. See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                    2046 // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf
                                  );
                                 
    n2k->SetMode(tNMEA2000::N2km_ListenAndNode, NodeAddress);
    n2k->SetForwardOwnMessages(false);
    n2k->SetHeartbeatInterval(NMEA2000_HEARTBEAT_INTERVAL);
    n2k->ExtendTransmitMessages(pgns);
    rapid_vector_handler = new handle129026(n2k);
    rapid_position_handler = new handle129025(n2k);
    n2k->Open();
  }

  void loop() override {
    n2k->loop();
    n2k->ParseMessages();
    int SourceAddress = n2k->GetN2kSource();
    if (SourceAddress != NodeAddress) { // Save potentially changed Source Address to NVS memory
        NodeAddress = SourceAddress;      // Set new Node Address (to save only once)
        ESP_LOGD("custom", "Node Address Changed to %i", NodeAddress);
    }
    unsigned long now = esphome::millis();
    if ((now - esp_last_update) > esphome_update_period){
      Nmea2kTwai::Status canState=n2k->getStatus();
      n2kstatus->publish_state(canState.state);
      rx_error_counter->publish_state(canState.rx_errors);
      tx_error_counter->publish_state(canState.tx_errors);
      tx_failed->publish_state(canState.tx_failed);
      rx_missed->publish_state(canState.rx_missed);
      tx_timeouts->publish_state(canState.tx_timeouts);
      rx_overrun->publish_state(canState.rx_overrun);
      n2kaddress->publish_state(NodeAddress);
      sog->publish_state(rapid_vector_handler->SOG);
      cog->publish_state(rapid_vector_handler->COG);
      lat->publish_state(rapid_position_handler->LAT);
      lon->publish_state(rapid_position_handler->LON);
      esp_last_update = now;
    }
  }
};


