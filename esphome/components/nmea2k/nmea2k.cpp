#include "nmea2k.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/datatypes.h"
#include "esphome/core/helpers.h"

#include "Nmea2kTwai.h"

//Used for getting mac address
#include "esp_mac.h"
namespace esphome {
namespace nmea2k {

static const char *const TAG = "nmea2k";

void Nmea2kComponent::set_id_from_mac() {
  uint8_t chipid[6];
  uint32_t id = 0;
  esp_efuse_mac_get_default(chipid);
  for (int i = 0; i < 6; i++) id += (chipid[i] << (7 * i));
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting device id to %d", address);
  this->nmea2k_device_id_ = id;
}

void Nmea2kComponent::loop() {
    this->n2k->loop();
    this->n2k->ParseMessages();
    int SourceAddress = this->n2k->GetN2kSource();
    if (SourceAddress != NodeAddress) { // Save potentially changed Source Address to NVS memory
        NodeAddress = SourceAddress;      // Set new Node Address (to save only once)
        ESP_LOGD("custom", "Node Address Changed to %i", NodeAddress);
    }
}

void Nmea2kComponent::setup() {
  ESP_LOGCONFIG(TAG, "Nmea2k Setup: starting...");
      // Setup NMEA Here

    // if user doesn't specify device id, use MAC address
    if (this->nmea2k_device_id_ == 0) {
      set_id_from_mac();
    }

    n2k = new Nmea2kTwai(
      (gpio_num_t)this->can_tx_pin_->get_pin(),  // Get the GPIO number for the TX pin
      (gpio_num_t)this->can_rx_pin_->get_pin(),  // Get the GPIO number for the RX pin
      this->can_recovery_period_);

    n2k->SetN2kCANMsgBufSize(this->can_msg_buffer_size_); // Set the size of the CAN message buffer
    n2k->SetN2kCANReceiveFrameBufSize(this->can_rx_buffer_size_); // These appear to have no effect with twai
    n2k->SetN2kCANSendFrameBufSize(this->can_tx_buffer_size_); // These appear to have no effect with twai

    // Set product information
    n2k->SetProductInformation(this->nmea2k_product_serial_,    // Manufacturer's Model serial code
                                this->nmea2k_product_code_,     // Manufacturer's product code
                                this->nmea2k_firmware_version_,  // Manufacturer's Model ID
                                this->nmea2k_firmware_type_,    // Manufacturer's Software version code
                                this->nmea2k_version_,         // Manufacturer's Model version,
                                this->nmea2k_product_load_,    // Load Equivalency Number (LEN) of the product
                                this->nmea2k_version_,         // Version
                                this->nmea2k_certification_   // Certification level
                                );
    // Set device information
    n2k->SetDeviceInformation(this->nmea2k_device_id_, // Unique number. Use e.g. Serial number. Id is generated from MAC-Address
                              this->nmea2k_device_function_, // Device function=Analog to NMEA 2000 Gateway. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                              this->nmea2k_device_class_, // Device class=Inter/Intranetwork Device. See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                              this->nmea2k_manufacturer_id_ // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf
                                  );
                                 
    n2k->SetMode(tNMEA2000::N2km_ListenAndNode, NodeAddress);
    n2k->SetForwardOwnMessages(false);
    n2k->SetHeartbeatInterval(this->nmea2k_heartbeat_period_); // Set the heartbeat period in milliseconds
    n2k->Open();
  ESP_LOGCONFIG(TAG, "Nmea2k Setup: Complete...");
}

void Nmea2kComponent::set_nmea2k_device_id(uint32_t id) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting device id to %d", id);
  this->nmea2k_device_id_ = id;
}

void Nmea2kComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Nmea2k Config:");
}

float Nmea2kComponent::get_setup_priority() const { return setup_priority::DATA; }

void Nmea2kComponent::set_can_tx_pin(InternalGPIOPin *tx_pin) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN TX pin to %s", tx_pin.get_name().c_str());
  this->can_tx_pin_ = tx_pin;
}

void Nmea2kComponent::set_can_rx_pin(InternalGPIOPin *rx_pin) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN RX pin to %s", rx_pin.get_name().c_str());
  this->can_rx_pin_ = rx_pin;
}

void Nmea2kComponent::set_nmea2k_device_function(int function) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting device function to %d", function);
  this->nmea2k_device_function_ = function;
}

void Nmea2kComponent::set_can_recovery_period(int period){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN recovery period to %d ms", period);
  this->can_recovery_period_ = period;
}

void Nmea2kComponent::set_can_msg_buffer_size(int size){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN message buffer size to %d", size);
  this->can_msg_buffer_size_ = size;
}

void Nmea2kComponent::set_can_rx_buffer_size(int size){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN RX buffer size to %d", size);
  this->can_rx_buffer_size_ = size;
}

void Nmea2kComponent::set_can_tx_buffer_size(int size){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN TX buffer size to %d", size);
  this->can_tx_buffer_size_ = size;
}

void Nmea2kComponent::set_nmea2k_device_class(int device_class){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting device class to %d", class);
  this->nmea2k_device_class_ = device_class;
}

void Nmea2kComponent::set_nmea2k_manufacturer_id(int id){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting manufacturer ID to %d", id);
  this->nmea2k_manufacturer_id_ = id;
}

void Nmea2kComponent::set_nmea2k_product_load(int load){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product load to %d", load);
  this->nmea2k_product_load_ = load;
}

void Nmea2kComponent::set_nmea2k_product_serial(int serial){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product serial to %d", serial);
  this->nmea2k_product_serial_ = serial;
}

void Nmea2kComponent::set_nmea2k_product_code(int code){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product code to %d", code);
  this->nmea2k_product_code_ = code;
}

void Nmea2kComponent::set_nmea2k_certification(int cerfication){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting certification to %d", cerfication);
  this->nmea2k_certification_ = cerfication;
}

void Nmea2kComponent::set_nmea2k_version(int version){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting version to %d", version);
  this->nmea2k_version_ = version;
}

void Nmea2kComponent::set_nmea2k_heartbeat_period(int period){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting heartbeat period to %d ms", period);
  this->nmea2k_heartbeat_period_ = period;
}

void Nmea2kComponent::set_nmea2k_product_name(std::string name){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product name to %s", name.c_str());
  this->nmea2k_product_name_ = name;
}

void Nmea2kComponent::set_nmea2k_firmware_type(std::string type){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting firmware type to %s", type.c_str());
  this->nmea2k_firmware_type_ = type;
}

void Nmea2kComponent::set_nmea2k_firmware_version(std::string version){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting firmware version to %s", version.c_str());
  this->nmea2k_firmware_version_ = version;
}

void Nmea2kComponent::set_esphome_update_period(int period){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting ESPHome update period to %d ms", period);
  this->esphome_update_period_ = period;
}
      


}  // namespace nmea2k
}  // namespace esphome