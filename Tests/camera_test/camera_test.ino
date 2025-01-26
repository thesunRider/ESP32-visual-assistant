#include <Wire.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#define AXP2101_ADDRESS 0x34
#define I2C_SDA 10
#define I2C_SCL 9
#define AXP_IRQ 40


//device we have is : Espressif Systems ESP32-S3-WROOM-1-N16R2 , 16MBQuadSPI,2MB PSRAM

const char* ssid = "iobeam";
const char* password = "12345678";

AsyncWebServer server(80);

#define CAMERA_MODEL_ESP32_CAM_BOARD

#include "ESP32_OV5640_AF.h"

#define I2C_SDA 10
#define I2C_SCL 9

// ESP32 AI-THINKER Board
#define PWDN_GPIO_NUM 3
#define RESET_GPIO_NUM 42
#define XCLK_GPIO_NUM 8
#define SIOD_GPIO_NUM I2C_SDA
#define SIOC_GPIO_NUM I2C_SCL
#define Y9_GPIO_NUM 19
#define Y8_GPIO_NUM 18
#define Y7_GPIO_NUM 17
#define Y6_GPIO_NUM 15
#define Y5_GPIO_NUM 6
#define Y4_GPIO_NUM 4
#define Y3_GPIO_NUM 5
#define Y2_GPIO_NUM 7
#define VSYNC_GPIO_NUM 41
#define HREF_GPIO_NUM 20
#define PCLK_GPIO_NUM 16


static camera_config_t camera_config = {
  .pin_pwdn  = PWDN_GPIO_NUM,
  .pin_reset = RESET_GPIO_NUM,
  .pin_xclk = XCLK_GPIO_NUM,
  .pin_sscb_sda = SIOD_GPIO_NUM,
  .pin_sscb_scl = SIOC_GPIO_NUM,

  .pin_d7 = Y9_GPIO_NUM,
  .pin_d6 = Y8_GPIO_NUM,
  .pin_d5 = Y7_GPIO_NUM,
  .pin_d4 = Y6_GPIO_NUM,
  .pin_d3 = Y5_GPIO_NUM,
  .pin_d2 = Y4_GPIO_NUM,
  .pin_d1 = Y3_GPIO_NUM,
  .pin_d0 = Y2_GPIO_NUM,
  .pin_vsync = VSYNC_GPIO_NUM,
  .pin_href = HREF_GPIO_NUM,
  .pin_pclk = PCLK_GPIO_NUM,

  //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
  .xclk_freq_hz = 20000000,
  .ledc_timer = LEDC_TIMER_0,
  .ledc_channel = LEDC_CHANNEL_0,

  .pixel_format = PIXFORMAT_JPEG,//YUV422,GRAYSCALE,RGB565,JPEG
  .frame_size = FRAMESIZE_QVGA,//QQVGA-QXGA Do not use sizes above QVGA when not JPEG

  .jpeg_quality = 20, //0-63 lower number means higher quality
  .fb_count = 1 //if more than one, i2s runs in continuous mode. Use only with JPEG
};

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
}


esp_err_t camera_init() {
  //power up the camera if PWDN pin is defined
  if (PWDN_GPIO_NUM != -1) {
    pinMode(PWDN_GPIO_NUM, OUTPUT);
    digitalWrite(PWDN_GPIO_NUM, LOW);

    pinMode(PWDN_GPIO_NUM, OUTPUT);
    digitalWrite(PWDN_GPIO_NUM, LOW);
  }

  //initialize the camera
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK) {
    Serial.print( "Camera Init Failed");
    return err;
  }

  return ESP_OK;
}

esp_err_t camera_capture() {
  //acquire a frame
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println( "Camera Capture Failed");
    return ESP_FAIL;
  }
  //replace this with your own function
  Serial.print("got it");

  //return the frame buffer back to the driver for reuse
  esp_camera_fb_return(fb);
  return ESP_OK;
}



void setup() {
  Serial.begin(115200);
  Serial.println("Starting PMIC configurations");
  Wire.begin(I2C_SDA, I2C_SCL);

  delay(100);
  initAXP2101();
  delay (100); //wait for sometime for the voltages to stabilize

  Serial.println("Starting Camera");
  camera_init();
  Serial.println("Starting Capture");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  //Print the IP address
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("HTTP server started");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println( "Camera Capture Failed");
      request->send(200, "text/plain", "F no!");
    } else {
      //replace this with your own function

      AsyncResponseStream *response = request->beginResponseStream("image/jpg", fb->len);
      response->write(fb->buf, fb->len);
      request->send(response);

      Serial.print("wrote it");
      //request->send(200, "text/plain", "Hello AsyncWebServer!");
    }
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
  });
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
