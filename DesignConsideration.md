## Design COnsiderations

#### ESP32 Consideration 
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

### Warning
- IO47/IO48 operates in the 1.8V voltage domain.

