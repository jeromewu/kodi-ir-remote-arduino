Kodi IR Remote Arduino
=========

Make your Arduino Uno as an remote controller for your Kodi!

## Prerequisite

- Arduino IDE
- [Arduino-IRremote](https://github.com/z3t0/Arduino-IRremote)
- dfu-programmer

## Hardware Wiring

Check this awesome article: [Arduino IR Remote Receiver](https://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/)

## Installation & Development

### Installation

- Upload [ir-remote.ino](./ir-remote.ino) to your Arduino Uno using IDE
- Short the 2 leftmost ICSP headers next to the USB port ([Tutorial](http://wei48221.blogspot.com/2016/06/how-to-turn-arduino-uno-into-hid_26.html))
- Execute **flash-kb.sh**
```
$ sh flash-kb.sh
```
- Re-connect USB
- Done!

### Development

- Short the 2 leftmost ICSP headers
- Execute **flash-usb.sh**
```
$ sh flash-usb.sh
```
- Uncomment line 39 in [ir-remote.ino](./ir-remote.ino) to see ir codes from your remote controller in Serial Monitor, but **remember to comment this line after development or it might crash your computer**
- Repeat steps in installation

## Reference

- Keycodes: https://github.com/trusktr/arduino-keyboard-sketch/blob/master/arduino-keyboard-sketch.ino
