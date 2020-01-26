# DK-Level
LEVEL is a one-knob MIDI controller compatible with any computer music software. It features a large numeric display with auto-brightness adjustment.

![Level MIDI Controller](/images/dk-level_front.jpg)
![Level MIDI Controller](/images/dk-level_back.jpg)

## About
This project was commissioned to control the volume level of a studio monitoring system. The client was quite happy with the result. It is available for sale in my 
[Etsy Store: Circuits & Sawdust](https://www.etsy.com/listing/685397087/level-audio-volume-one-knob-usb-midi).

## How it works
This is a [Teensy LC](https://www.pjrc.com/teensy/) based USB MIDI controller with my usual smoothing algorithms to provide quality MIDI signals. It is programmed within Arduino, and extended by my own C++ classes to manage the knob values and value scaling across my collection of MIDI projects.

## Ingredients
- [Teensy LC](https://www.pjrc.com/teensy/) microcontroller
- 4 digit 7-segment LED numeric display with I2C [HT16K33 driver](https://www.adafruit.com/product/881)
- 10K potentiometer with [1" solid metal knob](https://www.adafruit.com/product/2056)
- Photoresistor cell to control display brightness
- A shiny [upcycled project enclosure](https://www.ebay.com/itm/292067232173)
