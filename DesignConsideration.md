## Design Considerations
Here we specify all steps to produce each modules

## Technology Used
Listing of Technologies used in the design:
- ChargingBMC 
- Overvoltage Current protection
- Speaker  - https://www.adafruit.com/product/3923
- Amplifier
- Switches
- Camera
- Microphone - [Mems Mic](https://www.mouser.com/new/stmicroelectronics/stm-mp34dt06j-mems-microphone/?utm_id=177953056&gad_source=1&gclid=Cj0KCQiA3sq6BhD2ARIsAJ8MRwWJnhznsWiTNSwgZ1QY46zi9J55qz7O4NGU2KTo3JAvnQrWUm572PMaArC5EALw_wcB) [mems Mic 2](https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/)
- Main Unit - [ESP32-S3-WROOM-1-N4](https://www.digikey.de/de/products/detail/espressif-systems/ESP32-S3-WROOM-1-N4/16163950)

### ESP32 Module 
Unit: **ESP32-S3-WROOM-1-N4**
JLCPCB: Not Available
Logic levels ESP32 - VDD x 0.75 H : VDD x 0.25 L
Max 650 mA at 3.3V input

- Soldering the EPAD to the ground of the base board is not a must, however, it can optimize thermal
performance. If you choose to solder it, please apply the correct amount of soldering paste. Too much
soldering paste may increase the gap between the module and the baseboard. As result, the adhesion
between other pins and the baseboard may be poor.

- To ensure that the power supply to the ESP32-S3 chip is stable during power-up, it is advised to add an
RC delay circuit at the EN pin. The recommended setting for the RC delay circuit is usually R = 10 kΩ and
C = 1 µF. However, specific parameters should be adjusted based on the power-up timing of the module
and the power-up and reset sequence timing of the chip. For ESP32-S3’s power-up and reset sequence
timing diagram, please refer to ESP32-S3 Series Datasheet > Section Power Supply

For booting after reset:

| Boot Mode | GPIO0  | GPIO46  |
|-----------|----------|----------|
| SPI Boot  | 1	 |   Any       |
| Joint Boot   | 0        |   0       |

SPI Boot - Loads from internal memory and executes (default)
Joint Boot - In Joint Download Boot mode, users can download binary files into flash using UART0 or USB interface. It is
also possible to download binary files into SRAM and execute it from SRAM (Programming)

#### Warning
- IO47/IO48 operates in the 1.8V voltage domain.


## Microphone Module
Unit: ICS-43434
JLCPCB: Available
Logic Levels: VDD x 0.7 H : VDD x 0.3 L
Max 1mA at 3.3V
I2S unit with full itegrated components

Refer App notes
Refer Schematic at: https://learn.adafruit.com/assets/132616

### Warning
- SD Output Serial	Data Output	for	I²S	Interface.	This	pin	tristates	when	not	actively	driving	the	
appropriate	output	channel.	The	SD	trace	should	have	a	100	kΩ	pull-down	resistor	to	
discharge	the	line	during	the	time that	all	microphones	on	the	bus	have	tristated	their	
outputs.	

### Interfacing
ESP32-S3 includes two standard I2S interfaces. They can operate in master mode or slave mode, in full-duplex mode or half-duplex communication mode, and can be configured to operate with an 8-bit, 16-bit, 24-bit, or 32-bit resolution as an input or output channel. BCK clock frequency, from 10 kHz up to 40 MHz, is supported.

The I2S interface has a dedicated DMA controller. It supports TDM PCM, TDM MSB alignment, TDM LSB alignment, TDM Phillips, and PDM interface.
Pin Assignment:
For I2S, the pins used can be chosen from any GPIOs via the GPIO Matrix. For more information about the pin assignment, see ESP32-S3 Series Datasheet > Section IO Pins and ESP32-S3 Technical Reference Manual > Chapter IO MUX and GPIO Matrix.

