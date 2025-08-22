#include <Arduino.h>

// SPDX-FileCopyrightText: 2023 Carter Nelson for Adafruit Industries
//
// SPDX-License-Identifier: MIT
// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// --------------------------------------

#include <Wire.h>
//            SDA  SCL
TwoWire Wire1(PB7, PB6); //
// Set I2C bus to use: Wire, Wire1, etc.
//#define WIRE Wire1

//HardwareSerial1 Serial1(PA9, PA10);// setup pin TX RX

void setup() {
  Wire1.begin();
  Serial1.setRx(PA10);
  Serial1.setTx(PA9);
  Serial1.begin(115200);
  while (!Serial1)
     delay(10);
  Serial1.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial1.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();

    if (error == 0)
    {
      Serial1.print("I2C device found at address 0x");
      if (address<16)
        Serial1.print("0");
      Serial1.print(address,HEX);
      Serial1.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial1.print("Unknown error at address 0x");
      if (address<16)
        Serial1.print("0");
      Serial1.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial1.println("No I2C devices found\n");
  else
    Serial1.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}