# ESP32-PS4-Interface

Use an ESP32 to connect to and take inputs from a PS4 controller and transmit the data over serial using the SerialTransfer library.
For an example on how to receive these inputs on another arduino, see the implementation for [NJIT-ARPA-WHITE](https://github.com/Wayne-Valley-Robotics/NJIT-ARPA-WHITE)

###### Developed for NJIT-ARPA 2026. Licensed under GPLv3. Derivations must be open sourced.

## Instructions

Download and install the PlatformIO plugin for VSCode.
Clone the repository and follow the instructions in the [private.ini.template](https://github.com/Wayne-Valley-Robotics/ESP32-PS4-Interface/blob/main/private.ini.template) file.

Connect the **TX2** pin on the ESP32 to the Rx port of the receiving device. **Make sure to connect ground to ground!**

## TODO

- Implement Tx functionality to PS4 and the supplementary Rx counterparts from the child board (set color, rumble, etc.)

- Implement alternative data transfer protocols from the SerialTransfer library (I2C, etc.) That way we can support daisy-chaining, a la tetrix. Or don't. I hate tetrix. You do not need 40ms to read an encoder. That is absurd. That is insane. Do not come to my town[.](https://youtu.be/D0Pu7ZgEAwU?t=126)
