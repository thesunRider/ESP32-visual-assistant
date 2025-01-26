#include <Wire.h>
#define AXP2101_ADDRESS 0x34
#define I2C_SDA 10
#define I2C_SCL 9
#define AXP_IRQ 40

bool  pmu_flag = 0;

enum keypress_type {
  SHORT_PRESS,
  LONG_PRESS,
  PRESS_ELSE
};

void setFlag(void)
{
  Serial.println("IRQ Fired!");
  pmu_flag = true;
}

void initAXP2101() {

  // DONT PLAY WITH FIRE, CHANGE BELOW VALUES IF YOU KNOW WHAT YOU ARE DOING
  //set batfet value to on
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(18);
  Wire.write(8);
  Wire.endTransmission();


  // set rbfet charger current limit to 0.9A
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(22);
  Wire.write(2);
  Wire.endTransmission();



  // change vsys min threshold voltage 3.3V
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(36);
  Wire.write(7);
  Wire.endTransmission();


  //change vindpm to 4.25V max lipo voltage
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(21);
  Wire.write(4); //change to 15 if necessary
  Wire.endTransmission();

  // Start writing aldo1 value
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(146);
  Wire.write(9);
  Wire.endTransmission();

  // Start writing aldo2 value
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(147);
  Wire.write(23);
  Wire.endTransmission();

  // Start writing dcdc1 value
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(130);
  Wire.write(18);
  Wire.endTransmission();

  //enable dcdc1
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(128);
  Wire.write(1);
  Wire.endTransmission();

  //enable aldos 1 and 2
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(144);
  Wire.write(3);
  Wire.endTransmission();


  //set ONLEVEL 2 s , OFFLEVEL 4 s and IRQ level as 1s
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(39);
  Wire.write(14);
  Wire.endTransmission();


  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(0x49);
  Wire.write(255);
  Wire.endTransmission();

  //clear all IRQ
  for (int i = 0; i < 3; i++) {
    Wire.beginTransmission(AXP2101_ADDRESS);
    Wire.write(0x48 + i);
    Wire.write(255);
    Wire.endTransmission();
  }

}

keypress_type detect_keypress(void ) {
  Wire.beginTransmission(AXP2101_ADDRESS);
  Wire.write(73); //Read IRQ register
  Wire.endTransmission();
  int read_val = Wire.requestFrom((byte) AXP2101_ADDRESS, 1, (byte) true);
  byte b = (byte) Wire.read();

  //clear all irq
  for (int i = 0; i < 3; i++) {
    Wire.beginTransmission(AXP2101_ADDRESS);
    Wire.write(0x48 + i);
    Wire.write(255);
    Wire.endTransmission();
  }
  if ((b & ( 1 << 3 )) >> 3)
    return SHORT_PRESS;
  if ((b & ( 1 << 2 )) >> 2)
    return LONG_PRESS;
    
  return PRESS_ELSE;
}


void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  Serial.println("Starting PMIC configurations");


  delay(100);

  pinMode(AXP_IRQ, INPUT_PULLUP);
  attachInterrupt(AXP_IRQ, setFlag, FALLING);

  //wait for everything to start
  initAXP2101();


}

void loop() {
  // put your main code here, to run repeatedly:
  if (pmu_flag) {

    pmu_flag = false;
    //detect keypress
    keypress_type keytype = detect_keypress();

    if (keytype == LONG_PRESS) {
      //write turn off logic here
      Serial.println("I am OFF");
    }
    else if (keytype == SHORT_PRESS) {
      //write turn on logic here
      Serial.println("I am ON");
    }
  }

  delay(10);
}
