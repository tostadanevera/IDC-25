// main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "core/AccessController.h"
#include "adapters/FileDatabase.h"
#include "adapters/SerialNotifier.h"
#include "adapters/LEDOutput.h"
#include "adapters/RFIDInput.h"
#include "adapters/MQTTNotifier.h"

//#include "adapters/MockDatabase.h"
//MockDatabase db;

const char* SSID = "TU_SSID";
const char* PASSWORD = "TU_PASS";
const char* MQTT_SERVER = "BROKER_IP";
const char* MQTT_TOPIC = "rfid/access";
const char* FILENAME = "/cards.txt";  // Archivo para la base de datos

// Usamos FileDatabase para manejar la base de datos de tarjetas
FileDatabase db(FILENAME);
SerialNotifier serialNotifier;
LEDOutput outputs(3, 4);  // Verde y rojo
RFIDInput rfid(5, 27);    // Pines RFID
AccessController controller(db, outputs);

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setupWiFiAndMQTT() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  mqttClient.setServer(MQTT_SERVER, 1883);
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupWiFiAndMQTT();
  rfid.begin();
  controller.begin();

  MQTTNotifier* mqttNotifier = new MQTTNotifier(mqttClient, MQTT_TOPIC);
  controller.addNotifier(&serialNotifier);
  controller.addNotifier(mqttNotifier);

  Serial.println("Esperando tarjeta RFID...");
}

void loop() {
  mqttClient.loop();

  String uid;
  if (rfid.readCard(uid)) {
    Serial.print("UID leído: ");
    Serial.println(uid);
    controller.onCardRead(uid.c_str());
  }
  delay(100);
}