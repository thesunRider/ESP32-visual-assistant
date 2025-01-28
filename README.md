# ESP32 AI portable visual-assistant  
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
- [x] Make BMC and Avail power Rails
- [x] Craete Flowchart
- [x] Create Esp32 Base 
- [x] Create Amp Schematic
- [x] Create Mic Schematic
- [x] Create Camera Schematic - Created a symbol in Kicad for testing (proceeding with it - need reverse engineer testing)
- [x] Add switch Schematic
- [x] Link Components to PCB 
- [x] Test Cases for Hardware

Project Finished Rev2 Board created with superior perfomance

## Reference
Kindly put circuit reference here
1. USB from here: https://github.com/jenschr/USB-C-Connectors
2. PMIC Reference Design https://oshwhub.com/mondraker/axp2101_2023-11-18_20-15-19


## Components Sourcing
Adafruit OV5640 Camera Breakout
-  Breakout Board uses FD5640 500W Camera sensor
-  Available in bluk from Aliexpress
- Switch: K2-1114SA-A4SW-06, https://jlcpcb.com/partdetail/OmronElectronics-B3S1000/C2733655 Check pin configs
- Switch: K2-1114SA-A4SW-06, https://jlcpcb.com/partdetail/OmronElectronics-B3S1000/C2733655
- Speakers , https://www.lcsc.com/product-detail/Speakers_INGHAi-GSPK151035PN-8R0-5W-L35-1-25T_C530539.html
- Tactile Switches https://de.aliexpress.com/item/32912259140.html?gatewayAdapt=glo2deu

AXP2101 Component
- Inductor   3.1A 1uH ±20% 0806 Power Inductors ROHS
  https://www.lcsc.com/product-detail/Power-Inductors_Chilisin-Elec-HEI201610K-1R0M-Q8DG_C329576.html

