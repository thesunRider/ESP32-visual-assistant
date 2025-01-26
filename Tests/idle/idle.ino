#include <ESP_I2S.h>
#include <ezButton.h>
#include <Wire.h>
#include "ESP32_WS2812_Lib.h"


#define AXP2101_ADDRESS 0x34
#define I2C_SDA 10
#define I2C_SCL 9
#define AXP_IRQ 40



#define RGBLED 11
#define LEDS_COUNT 1
#define CHANNEL    0

ezButton button1(1);  // create ezButton object that attach to pin 6;
ezButton button2(2);  // create ezButton object that attach to pin 7;
ezButton button3(47);  // create ezButton object that attach to pin 8;
// first argument is the data pin, the second argument is the number of LEDs
ESP32_WS2812 strip = ESP32_WS2812(LEDS_COUNT, RGBLED, CHANNEL, TYPE_GRB);


boolean start_speaker = false;

const uint8_t AMP_SCK = 13;    /* Audio data bit clock */
const uint8_t AMP_WS = 12;    /* Audio data left and right clock */
const uint8_t AMP_SDOUT = 38; /* ESP32 audio data output (to speakers) */
const uint8_t AMP_ENABLE = 14;
const uint8_t AMP_VOLUME = 10;

const int frequency = 440;    // frequency of square wave in Hz
const int amplitude = 1;    // amplitude of square wave
const int sampleRate = 8000;  // sample rate in Hz

i2s_data_bit_width_t bps = I2S_DATA_BIT_WIDTH_16BIT;
i2s_mode_t usedmode = I2S_MODE_STD;
i2s_slot_mode_t slot = I2S_SLOT_MODE_MONO;

const int halfWavelength = (sampleRate / frequency);  // half wavelength of square wave

int32_t sample = amplitude;  // current sample value
int count = 0;

I2SClass i2s;

int ledState = LOW;  // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
long interval = 1000;  // interval at which to blink (milliseconds)

boolean deviceon = true;
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
  Serial.println("I2S simple tone");

  pinMode(AMP_ENABLE, OUTPUT);
  digitalWrite(AMP_ENABLE, HIGH); // Enable the amplifier

  i2s.setPins(AMP_SCK, AMP_WS, AMP_SDOUT, -1, -1);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(usedmode, sampleRate, bps, slot)) {
    Serial.println("Failed to initialize I2S!");
    while (1);  // do nothing
  }
  Serial.print("Initialised and starting");
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds

  strip.begin();
  strip.setBrightness(0);
  strip.setAllLedsColor(0, 0, 255);
  strip.show();

  pinMode(AXP_IRQ, INPUT_PULLUP);
  attachInterrupt(AXP_IRQ, setFlag, FALLING);

  delay(100);
  initAXP2101();
  delay(100);
}

void loop() {
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first

  if (button3.isPressed()) {
    Serial.print("pressed centre button");
    start_speaker = !start_speaker;
  }

  if (button2.isPressed()) {
    Serial.print("pressed 2 button");
    interval += 50;
    if (interval > 2000)
      interval = 2000;
  }

  if (button1.isPressed()) {
    Serial.print("pressed 1 button");
    interval -= 50;

    if (interval < 20)
      interval = 20;
  }
  
  if (start_speaker && deviceon) {
    if (count % halfWavelength == 0) {
      // invert the sample every half wavelength count multiple to generate square wave
      sample = -1 * sample;
    }

    i2s.write(sample * AMP_VOLUME); // Right channel

    // increment the counter for the next sample
    count++;
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval && deviceon) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      strip.setBrightness(100);
    } else {
      ledState = LOW;
      strip.setBrightness(0);
    }

  }

  if (pmu_flag) {

    pmu_flag = false;
    //detect keypress
    keypress_type keytype = detect_keypress();

    if (keytype == LONG_PRESS) {
      //write turn off logic here
      Serial.println("I am OFF");
      deviceon = false;
      digitalWrite(AMP_ENABLE, LOW); // Enable the amplifier
      strip.setBrightness(0);
    }
    else if (keytype == SHORT_PRESS) {
      //write turn on logic here
      Serial.println("I am ON");
      deviceon = true;
      
      digitalWrite(AMP_ENABLE, HIGH); // Enable the amplifier
    }
  }


  

}
