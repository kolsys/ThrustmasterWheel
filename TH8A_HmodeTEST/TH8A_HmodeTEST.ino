/* I used Arduino PRO Mini

Base connector / note / Arduino pin
DIN6_1 /  nothing      /
DIN6_2 /  I2C-SCL      / A5
DIN6_3 /  /Shifter ON  / GND
DIN6_4 /  I2C-SDA      / A4
DIN6_5 /  Vdd          / RAW
DIN6_6 /  Vss          / GND

*/

byte baseInit[3] = {0x80, 0x0C, 0x01};
byte endBytes[5] = {0x00, 0x00, 0x00, 0x00,0x00};

#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x03); // join i2c bus (address optional for master)
  Serial.begin(115200);
  Serial.println("START");
  digitalWrite(13, HIGH);
}

void interval() {
  Serial.println("WHILE");
  digitalWrite(13, LOW);
  delay(3000);
  digitalWrite(13, HIGH);
}

void switchHGear(byte gear) { // Gear num 0-N, 8-R
  byte cmd[6] = {(0x80 >> (8-gear)), 0x00, 0x80, 0x80, 0x00, 0x00};
  Wire.beginTransmission(0x01); // transmit to Base
  Wire.write(baseInit, 3);      // Init bytes
  Wire.write(cmd, 6); // we do not send XY coordinates
  Wire.write(endBytes, 5);
  Wire.endTransmission();
  Serial.print("Gear ");
  Serial.print(" ");
  Serial.println(gear);
}

void loop() {
  byte i = 0;
  for (i=0; i<9; i++) {
    switchHGear(i);
    digitalWrite(13, LOW);
    delay(3000);
    digitalWrite(13, HIGH);
  }

//   // // put your main code here, to run repeatedly:
//   // Wire.beginTransmission(0x01); // transmit to Base
//   // Wire.write(GearN, 9);        // sends 14 bytes
//   // Wire.write(endbytes, 5);
//   // Wire.endTransmission();    // stop transmitting
//   // interval();
//   Serial.println("WHILE2");
//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(Gear1, 9);        // sends 14 bytes
//   Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
// interval();

//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(Gear2, 9);        // sends 14 bytes
// Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
//   interval();

//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(GearN, 9);        // sends 14 bytes
//   Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
// interval();

// Serial.println("WHILE");

//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(Gear2, 9);        // sends 14 bytes
//   Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
// interval();

//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(Gear4, 9);        // sends 14 bytes
//   Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
// interval();

// //   Wire.beginTransmission(0x01); // transmit to Base
// //   Wire.write(Gear6, 9);        // sends 14 bytes
// //   Wire.write(endbytes, 5);
// //   Wire.endTransmission();    // stop transmitting
// // interval();


// //   Wire.beginTransmission(0x01); // transmit to Base
// //   Wire.write(Gear5, 9);        // sends 14 bytes
// //   Wire.write(endbytes, 5);
// //   Wire.endTransmission();    // stop transmitting
// // interval();

//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(Gear3, 9);        // sends 14 bytes
//   Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
// interval();

//   Wire.beginTransmission(0x01); // transmit to Base
//   Wire.write(Gear1, 9);        // sends 14 bytes
//   Wire.write(endbytes, 5);
//   Wire.endTransmission();    // stop transmitting
// interval();


// //   Wire.beginTransmission(0x01); // transmit to Base
// //   Wire.write(GearR, 9);        // sends 14 bytes
// //   Wire.write(endbytes, 5);
// //   Wire.endTransmission();    // stop transmitting
// // interval();


}



