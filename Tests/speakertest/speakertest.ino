#include <ESP_I2S.h>

const uint8_t AMP_SCK = 13;    /* Audio data bit clock */
const uint8_t AMP_WS = 12;    /* Audio data left and right clock */
const uint8_t AMP_SDOUT = 38; /* ESP32 audio data output (to speakers) */
const uint8_t AMP_ENABLE = 14;
const uint8_t AMP_VOLUME = 200;

const int frequency = 440;    // frequency of square wave in Hz
const int amplitude = 500;    // amplitude of square wave
const int sampleRate = 8000;  // sample rate in Hz

i2s_data_bit_width_t bps = I2S_DATA_BIT_WIDTH_16BIT;
i2s_mode_t usedmode = I2S_MODE_STD;
i2s_slot_mode_t slot = I2S_SLOT_MODE_MONO;

const int halfWavelength = (sampleRate / frequency);  // half wavelength of square wave

int32_t sample = amplitude;  // current sample value
int count = 0;

I2SClass i2s;

void setup() {
  Serial.begin(115200);
  Serial.println("I2S simple tone");

  pinMode(AMP_ENABLE,OUTPUT);
  digitalWrite(AMP_ENABLE,HIGH); // Enable the amplifier 

  i2s.setPins(AMP_SCK, AMP_WS, AMP_SDOUT, -1, -1);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(usedmode, sampleRate, bps, slot)) {
    Serial.println("Failed to initialize I2S!");
    while (1);  // do nothing
  }
  Serial.print("Initialised and starting");
}

void loop() {
  if (count % halfWavelength == 0) {
    // invert the sample every half wavelength count multiple to generate square wave
    sample = -1 * sample;
  }

  i2s.write(sample*AMP_VOLUME);  // Right channel
  i2s.write(sample*AMP_VOLUME);  // Left channel WRITE TO BOTH CHANNELS FOR MAXIMUM OUTPUT

  // increment the counter for the next sample
  count++;
}
