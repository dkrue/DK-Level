#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include <KnobDK.h>
#include <UtilityDK.h>

#define midiChannel 1

Adafruit_7segment matrix = Adafruit_7segment();

static const uint8_t numbertable_inverted[] = {
  0x3F, /* 0 */
  0x30, /* 1 */
  0x5B, /* 2 */
  0x79, /* 3 */
  0x74, /* 4 */
  0x6D, /* 5 */
  0x6F, /* 6 */
  0x38, /* 7 */
  0x7F, /* 8 */
  0x7D  /* 9 */
};

// Controller knobs (analogPin, midiCC, analogMin, analogMax)
KnobDK knob[2] = {
  KnobDK(A7, 7, 0, 1023), // volume knob
  KnobDK(A9, 0, 0, 1023) // photocell
};

void setup() {

  matrix.begin(0x70);
  matrix.setBrightness(0);

  // Display starting value
  knob[0].refresh();
  writeNumber(knob[0].ccVal());
  matrix.writeDisplay();
}

void loop() {

  // Analog inputs loop
  for (int i=0; i < 2; i++)
  {
    // Refresh controller value
    bool activity = knob[i].refresh();

    if(activity) {
      if(i==0) {
        // Update volume knob
        usbMIDI.sendControlChange(knob[i].ccNum(), knob[i].ccVal(), midiChannel);
        
        writeNumber(knob[i].ccVal());
        matrix.writeDisplay();
      } else {
        // Update display brightness from photocell
        matrix.setBrightness(UtilityDK::scale(knob[i].ccVal(), 0, 127, 0, 15));
        // (set brightness to 2 for photo purposes)
      }

    }
  }

  // Reduce analog sampling rate for smoother action
  delay(20);

  // MIDI Controllers should discard incoming MIDI messages
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

void writeNumber(int val) {
    uint8_t hundreds = (val / 100) % 10;
    if(hundreds > 0) {
      writeDigitNumInverted(1, (val / 100) % 10);
    } else {
        matrix.writeDigitRaw(4-1, 0x00);
    }
    writeDigitNumInverted(3, (val / 10) % 10);
    writeDigitNumInverted(4, val % 10);
}

void writeDigitNumInverted(uint8_t d, uint8_t num) {
  if(d > 4) return;
  
  matrix.writeDigitRaw(4-d, numbertable_inverted[num]);
}
