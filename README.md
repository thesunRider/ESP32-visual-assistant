# Ware It ESP32S3

## Project Requirements for ESP32-S3 Device:

Audio Playback:

Support audio playback via a speaker.
Include an amplifier and necessary components for speaker output.
Battery Charging:

Integrate a rechargeable battery with efficient charging and power management.
Include a charging IC for Li-ion/Li-poly batteries, supporting both charging and power distribution to the ESP32-S3.
Connectivity:

Enable Wi-Fi and Bluetooth (including BLE) for app connectivity and efficient power use.
Camera Integration:

Include a camera module for image/video capture, compatible with the ESP32-S3.
Microphone Control:

Add a physical button to control the microphone (e.g., mute/unmute), connected to the ESP32-S3 GPIO.
Provide feedback (e.g., LED indicator) for microphone status.
Enclosure:

Design a compact, 3D-printed enclosure with ports (e.g., USB) and heat dissipation as needed.
Current Status:
Firmware tested on ESP32-S3 Xiao Sense with Audio BFF amplifier. Ready to design and manufacture the PCB and enclosure.

Language: C++ -> Need to create testcases for harware \
Folder Structure Required:
- Kicad
	- Test (First Prototype)
	- Main (Main Prototype)
- Docs
	- Datasheets
	- Images
- Gerbers


the specs just list it as a built-in digital microphone. i'm sure it's similar to this PDM MEMS microphone 
[8:01 pm, 6/12/2024] Haris Mujeeb Elab: the camera sensor is OV2640

## Technology Used
Listing of Technologies used in the design:
- ChargingBMC 
- Overvoltage Current protection
- Speaker  - https://www.adafruit.com/product/3923
- Amplifier
- Switches
- Camera
- Microphone - [Mems Mic](https://www.mouser.com/new/stmicroelectronics/stm-mp34dt06j-mems-microphone/?utm_id=177953056&gad_source=1&gclid=Cj0KCQiA3sq6BhD2ARIsAJ8MRwWJnhznsWiTNSwgZ1QY46zi9J55qz7O4NGU2KTo3JAvnQrWUm572PMaArC5EALw_wcB)
- Main Unit - ESP32

## Flowchart


## Energy Charts

## Notes
Kindly create a seperate page for each new design block (power, camera,mic,...etc) in kicad

## TODO
- [x] Create Kicad Project | Surya
- [ ] Make BMC and Avail power Rails
- [ ]
- [ ]
- [ ]
- [ ] Test Cases for Hardware
## Reference
Kindly put circuit reference here
1. None