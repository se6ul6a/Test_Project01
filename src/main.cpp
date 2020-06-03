#include <Arduino.h>

#include <Wire.h>               // biblioteka odpowiedzialna za I2C

void blink();             // definicja funkcji do migania dioda - uzywana w celach testowych PCB
void scannerI2C();        // definicja funkcji skanowania magistrali I2C w poszukiwaniu adresu urzadzen  

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // uzywane do migania diody tylko do celow testowych

  Serial.begin(9600);               // inicjacja terminala
  Wire.begin();                     // inicjalizacja I2C

  while (!Serial);                 // Arduino: wait for serial monitor
  Serial.println("\nI2C Scanner");
}

void loop() {
  // blink();                         // uruchomienie migania diody uzywane w celach testowych PCB
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}

// definicja funkcji migania diody na PCB
void blink() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
}