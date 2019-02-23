/* 

Ver 1.0a  -  2017.03.21

This sketch emulates Thrustmaster TH8A Shifter
allowing to connect arduino based shifter to Thrustmaster TX wheelbase (may work for T500/T300 as well)
and emulate shifting.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!            There are 2 flavours of arduino boards - powered by +5 volts or +3.3 volts                 !!!
!!!     If you have +5V Arduino version - disconnect it from USB before connecting to a wheelbase         !!!
!!! Just power your arduino from TX RW wheelbase Black pin - it supplies +3.3V voltage (should be enough) !!!
!!!         don't connect USB +5V wire to TX RW wheelbase Black +3.3V - you'll get a collision            !!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Thrustmaster Wheelbase cable pinout (PS/2 connector, also known as mini-Din 6pin female):

Base connector / note / Arduino pin
DIN6_1 /  nothing      /
DIN6_2 /  I2C-SCL      / A5
DIN6_3 /  /Shifter ON  / GND
DIN6_4 /  I2C-SDA      / A4
DIN6_5 /  Vdd          / RAW     (3,3V)
DIN6_6 /  Vss          / GND     (GND)

I used Arduino PRO Mini 3V3

Free to modify and use for your needs.
This sketch and the documentation above provided "AS IS" under the BSD New license.
http://opensource.org/licenses/BSD-3-Clause
(c) Istvan Virag (blog@rr-m.org) Febr 2017
*/

#define LoopForAntiPrell 16   // Need more speed testing

//*************************************************************************
//******** Elvileg minden digitális váltót itt be lehet állítani   ********
//*************************************************************************

const byte digitPins[] = {2, 3, 4, 5, 6, 7}; //An array to receive a binary 8-bit number on not necessarily consecutive pins, ordered by LSb to MSb
const byte digitSize = sizeof(digitPins);

#define HSSwitch 10     //H-SQ mode switch
#define H_Mode_Pins B00001111 //ordered MSb to LSb
#define Gear_N B00001111
#define Gear_1 B00001110
#define Gear_2 B00001101
#define Gear_3 B00001011
#define Gear_4 B00000111
#define Gear_5 B00000101
#define Gear_6 B00001001
#define Gear_7 B00001000
#define Gear_R B00000001
#define SQ_Mode_Pins B00110000
#define Gear_Center B00110000
#define Gear_Up B00100000
#define Gear_Down B00010000

//*******************************************
//****   Ez alatt ne nyúlj hozzá    *********
//*******************************************


//This is just for readable code
//  Gears
#define Center 0    //SQ
#define Up 1        //SQ
#define Down 2      //SQ
#define GearN 10    //H
#define Gear1 11    //H
#define Gear2 12    //H
#define Gear3 13    //H
#define Gear4 14    //H
#define Gear5 15    //H
#define Gear6 16    //H
#define Gear7 17    //H
#define GearR 18    //H

// Is there a way to Gear 9???




byte i2c_data[14];
//byte oldPinD = 0xFF;
byte ShiftGear;
byte err = 0;
boolean Hmode;
int shifting;
int Program = 0;





#include <Wire.h>

void setup() {
  //Set each pin connected to Shifter an input, and pullup
  for (int i = 0; i < digitSize; i++)
  {
    pinMode(digitPins[i], INPUT_PULLUP);
  }

  pinMode(HSSwitch, INPUT_PULLUP);

  // Set i2c static data
  i2c_data[1] = 0x0C;
  i2c_data[2] = 0x01;
  i2c_data[5] = 0x80;
  i2c_data[6] = 0x80;
  i2c_data[7] = 0x80;  // Y cordinate
  i2c_data[8] = 0x80;  // X cordinate
  i2c_data[9] = 0x00;
  i2c_data[10] = 0x00;
  i2c_data[11] = 0x00;
  i2c_data[12] = 0x00;
  i2c_data[13] = 0x00;

  Wire.begin(0x03); // join i2c bus (address optional for master)
}



void loop() {
  Hmode = digitalRead(HSSwitch);
  //  Hmode = true;

  if (Hmode) {
    i2c_data[0] = 0x80;
    i2c_data[3] = 0x00; // Gear
    i2c_data[4] = 0x00; // Shift
    ShiftGear = GearN;
  }
  else { //seq mode
    i2c_data[0] = 0x00;
    i2c_data[3] = 0x00; // Gear
    i2c_data[4] = 0x05; // Shift
    ShiftGear = Center;
  }

  int Shifter_State = parallelToByte();   //Read shifter State

  if (Hmode) {  // Hmode
    Shifter_State &= H_Mode_Pins;
    if (Shifter_State == Gear_N) {
      if (ShiftGear = GearN) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = GearN;
      }
    }
    else if (Shifter_State == Gear_1) {    // & Right & !Left & Down
      if (ShiftGear = Gear1) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear1;
      }
    }
    else if (Shifter_State == Gear_2) {
      if (ShiftGear = Gear2) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear2;
      }
    }
    else if (Shifter_State == Gear_3) {
      if (ShiftGear = Gear3) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear3;
      }
    }
    else if (Shifter_State == Gear_4) {
      if (ShiftGear = Gear4) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear4;
      }
    }
    else if (Shifter_State == Gear_5) {
      if (ShiftGear = Gear5) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear5;
      }
    }
    else if (Shifter_State == Gear_6) {
      if (ShiftGear = Gear6) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear6;
      }
    }
    else if (Shifter_State == Gear_7) {
      if (ShiftGear = Gear7) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Gear7;
      }
    }
    else if (Shifter_State == Gear_R) {
      if (ShiftGear = GearR) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = GearR;
      }
    }
    /// config more gears here
  }
  else { //seq mode
    Shifter_State &= SQ_Mode_Pins;
    if (Shifter_State == Gear_Center) {
      if (ShiftGear = Center) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Center;
      }
    }
    else if (Shifter_State == Gear_Up) {
      if (ShiftGear = Up) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Up;
      }
    }
    else if (Shifter_State == Gear_Down) {
      if (ShiftGear = Down) {
        shifting++;
      } else {
        shifting = 0;
        ShiftGear = Down;
      }
    }
    /// config more shifts here
  }
  //*/



  if (shifting = LoopForAntiPrell) {
    // Shift bytes paramtering
    if (ShiftGear == Center) {
      i2c_data[4] = 0x04;
      i2c_data[8] = 0xB9;
    }
    else if (ShiftGear == Up) {

      i2c_data[4] = 0x06;
      i2c_data[8] = 0xA5;
    }
    else if (ShiftGear == Down) {
      //Down
      i2c_data[4] = 0x05;
      i2c_data[8] = 0xD9;
    }
    else if (ShiftGear == GearN) {
      i2c_data[3] = 0x00;
      i2c_data[7] = 0x80;
      i2c_data[8] = 0x80;
    }
    else if (ShiftGear == Gear1) {
      i2c_data[3] = 0x01;
      i2c_data[7] = 0xB4;
      i2c_data[8] = 0xEB;
    }
    else if (ShiftGear == Gear2) {
      i2c_data[3] = 0x02;
      i2c_data[7] = 0x43;
      i2c_data[8] = 0xEB;
    }
    else if (ShiftGear == Gear3) {
      i2c_data[3] = 0x04;
      i2c_data[7] = 0xB4;
      i2c_data[8] = 0xA3;
    }
    else if (ShiftGear == Gear4) {
      i2c_data[3] = 0x08;
      i2c_data[7] = 0x43;
      i2c_data[8] = 0xA3;
    }
    else if (ShiftGear == Gear5) {
      i2c_data[3] = 0x10;
      i2c_data[7] = 0xB4;
      i2c_data[8] = 0x60;
    }
    else if (ShiftGear == Gear6) {
      i2c_data[3] = 0x20;
      i2c_data[7] = 0x43;
      i2c_data[8] = 0x60;
    }
    else if (ShiftGear == Gear7) {
      i2c_data[3] = 0x40;
      i2c_data[7] = 0xB4;
      i2c_data[8] = 0x1C;
    }
    else if (ShiftGear == GearR) {
      i2c_data[3] = 0x80;
      i2c_data[7] = 0x43;
      i2c_data[8] = 0x1C;
    }


    do {
      Wire.beginTransmission(0x01);    // transmit to Base
      Wire.write(i2c_data, 14);        // sends 14 bytes
      err = Wire.endTransmission();    // stop transmitting
    } while (err);



  } else if (shifting > LoopForAntiPrell) {
    shifting--;
  }
}



/*
* parallelToByte() - converts a binary value on max 8 digital inputs to an integer.
*/

int parallelToByte()
{
  int ret = 0;  // Initialize the variable to return
  const  int bitValue[] = {1, 2, 4, 8, 16, 32, 64, 128, 256}; // bit position decimal equivalents
  for (int i = 0; i < digitSize; i++) // cycle through all the pins
  {
    if (digitalRead(digitPins[i]) == HIGH) // because all the bits are pre-loaded with zeros, only need to do something when we need to flip a bit high
    {
      ret = ret + bitValue[i];  // adding the bit position decimal equivalent flips that bit position
    }
  }
  return ret;
}
