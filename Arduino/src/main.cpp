#include <Arduino.h>
#include "core/AccessController.h"
#include "adapters/FileDatabase.h"
#include "adapters/SerialNotifier.h"
#include "adapters/LEDOutput.h"
#include "adapters/RFIDInput.h"

//#include "adapters/MockDatabase.h"
//MockDatabase db;

const char* FILENAME = "/cards.txt";  // Archivo para la base de datos

// Usamos FileDatabase para manejar la base de datos de tarjetas
FileDatabase db(FILENAME);
SerialNotifier notifier;
LEDOutput outputs(3, 4);  // Verde y rojo
RFIDInput rfid(5, 27);    // Pines RFID
AccessController controller(db, notifier, outputs);

void setup() {
  Serial.begin(115200);
  rfid.begin();
  controller.begin();
  Serial.println("Esperando tarjeta RFID...");
}

void loop() {
  String uid;

  if (rfid.readCard(uid)) {
    Serial.print("UID leído: ");
    Serial.println(uid);
    controller.onCardRead(uid.c_str());
  }

  delay(100);
}
