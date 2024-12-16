# Ware It ESP32S3

Client Link: https://www.wareit.ai/

### Endproduct Requirement 
1. Working Prototype with enclosure
2. 50~60mm size 
3. Before 20th Jan. 
4. All functionalities must be operational.

### Device Design Requirements:

1. **Audio Playback:**
   - Play audio through a speaker using the Audio BFF amplifier.
   - Include necessary components for driving the speaker.

2. **Battery Charging:**
   - Support rechargeable Li-ion/Li-poly battery integration with efficient charging and power management.
   - Include a charging circuit and IC for managing charging and power distribution to the ESP32-S3.

3. **Connectivity:**
   - Enable Wi-Fi and Bluetooth (including BLE) for app connectivity and efficient power use.

4. **Camera Integration:**
   - Integrate an OV2640 camera module for image and video capture.

5. **Microphone and Control:**
   - Include three tactile buttons for microphone control with LED feedback for status (e.g., mute/unmute).

6. **Enclosure:**
   - Design a compact, 3D-printed enclosure with ports (e.g., USB charging) and provisions for heat dissipation.


### Current Status:
Firmware tested on ESP32-S3 Xiao Sense with Audio BFF amplifier by client .


## Technicals
Language: C++ -> Need to create testcases for harware \
Folder Structure :
- Kicad
	- Test (First Prototype)
	- Main (Main Prototype)
- Docs
	- Datasheets
	- Images
- Gerbers


## Technology Used
Listing of Technologies used in the design:
- PMIC - [AXP2101](https://jlcpcb.com/partdetail/x_powersTech-AXP2101/C3036461) 
- Amplifier & Speaker  - [Max98357 Amplifier](https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp/overview)
- Switches -
- Camera - [OV5640](https://www.waveshare.com/ov5640-camera-board-a.htm)
- Microphone - [Mems Mic](https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/)
- Main Unit - [ESP32-S3-WROOM-1-N4](https://www.digikey.de/de/products/detail/espressif-systems/ESP32-S3-WROOM-1-N4/16163950)

## Askables
1. Where in the product does the camera go 
2. Need The cad of the device

## Problems
1. ESP32 Cam schematics not well defined, most schematics on internet are wrong (NEED TO CHECK WITH DATASHEET)

The schematic layout and tyhe original pin index is inverted
Schmeatic Index:
| Pin | Schematic Name | Actual Name |
|-----|---------------|--------------|
| 1   | Y0            | NC           |
| 2   | Y1            | AGND         |
| 3   | Y4            | SIO_DAT      |
| 4   | Y3            | AVDD         |
| 5   | Y5            | SIO_CLK      |
| 6   | Y2            | RESET        |
| 7   | Y6            | VSYNC        |
| 8   | PCLK          | PWDN         |
| 9   | Y7            | HREF         |
| 10  | DGND          | DVDD         |
| 11  | Y8            | DOVDD        |
| 12  | XCLK          | Y9           |
| 13  | Y9            | XCLK         |
| 14  | DOVDD         | Y8           |
| 15  | DVDD          | DGND         |
| 16  | HREF          | Y7           |
| 17  | PWDN          | PCLK         |
| 18  | VSYNC         | Y6           |
| 19  | RESET         | Y2           |
| 20  | SIO_CLK       | Y5           |
| 21  | AVDD          | Y3           |
| 22  | SIO_DAT       | Y4           |
| 23  | AGND          | Y1           |
| 24  | NC            | Y0           |

ORIGINAL Index:



Cross Refer OV5640-A.pdf and Ov5640-Camera-Schematic.pdf



## Flowchart


## Energy Charts

While connecting the amplifier , the supply to the amp should go just after the fuel gauge and the over current protection circuit 

| Component | Voltage  | Current  |
|-----------|----------|----------|
| Esp32 S3  | 3v3	 |   650mA       |
| Mic   |     3v3    |      2mA    |
| Amp        | 3v7     |      500mA    |
| Camera | 3v3 , 2v8, 1v5 | 200mA |
| LED 		| 3v3	| 70mA	|
| Extras |3v3 |30mA|

Max current: 1.5A


## Notes
1. Kindly create a seperate page for each new design block (power, camera,mic,...etc) in kicad
2. Kindly Name no connect jumpers as 0ohm resistors and reference as NC
3. BE CAREFUL TO PLACE NC RESISTORS ISOLATED IN FOOTPRINT AS THEY NEED TO BE DESOLDERED OR SOLDERED WITHOUT DISTURBING SURROUNDINGS
4. Refer [Design Considerations](DesignConsideration.md) for specific module requirements
5. Crossrefer pinconnections between footprint and datasheet to check if they are the same.
6. CHECK IF ALL I2S, I2C , SPI AND SDA INTERFACES HAVE PROPER PULLUPS INSTALLED ON SCHEMATIC
7. Breakout a JTAG controller for debugging esp32

## TODO
- [x] Create Kicad Project
- [ ] Make BMC and Avail power Rails
- [ ] Craete Flowchart
- [x] Create Esp32 Base 
- [x] Create Amp Schematic
- [x] Create Mic Schematic
- [x] Create Camera Schematic - Created a symbol in Kicad for testing (proceeding with it - need reverse engineer testing)
- [ ] Add switch Schematic
- [ ] Link Components to PCB 
- [ ] Test Cases for Hardware

## Reference
Kindly put circuit reference here
1. None

## Components Sourcing
Adafruit OV5640 Camera Breakout
-  Breakout Board uses FD5640 500W Camera sensor
-  Available in bluk from Aliexpress
