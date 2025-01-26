#include <ESP_I2S.h>


#define MIC_SAMPLE_RATE 8000

const uint8_t MIC_SCK = 45;    /* Audio data bit clock */
const uint8_t MIC_WS = 21;    /* Audio data left and right clock */
const uint8_t MIC_SDIN = 39; /* ESP32 audio data input */
int data_available;

// dont play with this if you dont know what you are doing
i2s_data_bit_width_t bps = I2S_DATA_BIT_WIDTH_32BIT;
i2s_mode_t usedmode = I2S_MODE_STD;
i2s_slot_mode_t slot = I2S_SLOT_MODE_MONO;

I2SClass i2s;

void setup() {
  Serial.begin(115200);
  Serial.println("I2S simple tone");

  i2s.setPins(MIC_SCK, MIC_WS, -1, MIC_SDIN);
  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(usedmode, MIC_SAMPLE_RATE, I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO, I2S_STD_SLOT_LEFT)) {
    Serial.println("Failed to initialize I2S!");
    while (1);  // do nothing
  }
  Serial.print("Initialised and starting");
 i2s.read();
}

void loop() {
  data_available = i2s.available();
  if (data_available)
    Serial.println(i2s.read());
}
