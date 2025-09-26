/*
   modified 8 May 2014
   by Scott Fitzgerald
   modified 2 Sep 2016
   by Arturo Guadalupi
   modified 8 Sep 2016
   by Colby Newman

   This example code is in the public domain.

   https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

#define LED_BUILTIN 25
int catCounter = 0;
boolean catDetected = false;

// Pin, an dem AO des Wassersensors angeschlossen ist
const int sensorPin = 4;

void setup() {
  //LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // LED aus (aktiv LOW auf ESP32/LOLIN32)

  Serial.begin(19200);
}

void loop() {
    // Wassermessung

  // Rohwert vom Wassersensor lesen (0 - 4095 bei ESP32)
  int waterSensorValue = analogRead(sensorPin);

  // Sensorwert auf Bereich 0-100 % skalieren
  int wasserProzent = map(waterSensorValue, 0, 4095, 0, 100);

  // Ausgabe ins Terminal
  Serial.println(String("Waterlevel: ") + wasserProzent);

  delay(100);



  // Sensorwert vom Pin 15 für die "Katzen"-Messung lesen
  int catSensorValue = analogRead(15);

  // ist Katze da oder nicht (oder Fehler tritt auf)
  if (catSensorValue == 0) {
    Serial.println("Error");
    digitalWrite(LED_BUILTIN, HIGH); // LED aus
  }
  else if (catSensorValue > 1000) {
    //Serial.println("Cat");
    digitalWrite(LED_BUILTIN, LOW);  // LED an (aktiv LOW)
    
    if (!catDetected) {
      // Katze ist NEU erkannt -> Counter erhöhen
      catCounter++;
      catDetected = true;
    }
  }
  else {
    //Serial.println("No Cat");
    digitalWrite(LED_BUILTIN, HIGH); // LED aus
    catDetected = false; 
  }

  Serial.println(catSensorValue);  // Sensorwert ausgeben
  Serial.println(catCounter);  // wie oft war Katze davor ausgeben

}

