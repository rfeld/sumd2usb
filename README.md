# sumd2usb

## Idea
I wanted to use my Graupner mz-12 to control an RC flight simulator on a computer without buying an expensive cable.

The solution is to configure the receiver (GR-12) to output a SUMD signal on channel 6 and connect it to the UART RX pin of an Arduino micro (Leonardo should also work).
The arduino then decodes the SUMD protocol and sends the Stick movements and Button pushes to the PC emulating an USB Joystick.

## Requirements:
- Arduino Micro/Leonardo
- Graupner Receiver speaking SUMD
- Three jumper wires (+,-,Signal)
- Joystick Library for Arduino (https://github.com/MHeironimus/ArduinoJoystickLibrary)

