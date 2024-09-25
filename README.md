# Obstacle Avoiding Car
![Obstacle Avoiding Car](https://github.com/yazansrayyes/ObastacleAvoidingCar/blob/main/assets/exhibit.jpg)


# Key Features
* Split Design: The split configuration allows for natural hand positioning, reducing strain during long typing sessions.
* 72 Keys: With a full set of 72 keys, the keyboard provides all the functionality you need and can be extended even further with enabling multi-layers.
* Wireless Operation: With full wireless connectivity, making your workspace cleaner and more organized.
* Ergonomic Layout: The 6x6 column staggered keys and additional thumb keys enhance typing efficiency and reduce finger movement.

# Firmware
The Tair Keyboard utilizes ZMK Firmware, which is based on the **Zephyr RTOS**. This powerful firmware enables wireless functionality and ensures that the keyboard can handle multiple keypresses simultaneously without any hiccups. ZMK Firmware provides a high degree of customization, allowing you to tailor the keyboard's behavior to your specific needs.

# Flashing
The nice!nano v2 is the Adafruit nRF52 Bootloader, an easy-to-use CDC/DFU/UF2 bootloader for Nordic nRF52 microcontrollers that appears as a flash drive. 

To flash the firmware onto the nice!nano v2 microcontroller, follow these steps:

1. Enter Bootloader Mode:
Double-tap the RST and GND pins on the nice!nano to enter bootloader mode. The device will appear as a storage device on your computer once connected through USB.

2. Prepare Firmware File:
Compile your ZMK firmware project. This build will generate a .uf2 firmware file.