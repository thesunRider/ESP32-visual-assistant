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
- ChargingBMC 
- Overvoltage Current protection
- Amplifier & Speaker  - [Max98357 Amplifier](https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp/overview)
- Switches -
- Camera -
- Microphone - [Mems Mic](https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/)
- Main Unit - [ESP32-S3-WROOM-1-N4](https://www.digikey.de/de/products/detail/espressif-systems/ESP32-S3-WROOM-1-N4/16163950)

## Askables
1. Where in the product does the camera go 
2. Need The cad of the device

## Problems
1. ESP32 Cam schematics not well defined, most schematics on internet are wrong (NEED TO CHECK WITH DATASHEET)


## Flowchart


## Energy Charts

While connecting the amplifier , the supply to the amp should go just after the fuel gauge and the over current protection circuit 

| Component | Voltage  | Current  |
|-----------|----------|----------|
| Esp32 S3  | 3v3	 |   650mA       |
| Mic   |     3v3    |      2mA    |
| Amp        | 3v7     |      500mA    |

## Notes
Kindly create a seperate page for each new design block (power, camera,mic,...etc) in kicad
Refer [Design Considerations](DesignConsideration.md) for specific module requirements

## TODO
- [x] Create Kicad Project
- [ ] Make BMC and Avail power Rails
- [ ] Craete Flowchart
- [x] Create Esp32 Base 
- [x] Create Amp Schematic
- [x] Create Mic Schematic
- [ ] Create Camera Schematic
- [ ] Add switch Schematic
- [ ] Link Components to PCB 
- [ ] Test Cases for Hardware

## Reference
Kindly put circuit reference here
1. None