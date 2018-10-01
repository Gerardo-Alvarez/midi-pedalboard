
#include "MIDIUSB.h" 
const byte CC = 0x0B; //Control Change
const byte CHANNEL = 0xB0; 
const byte EXP_PEDAL1 = 0;

uint8_t newValPedal1, oldValPedal1;

void setup()
{ 
    pinMode(2, INPUT_PULLUP);
    pinMode(3, OUTPUT);
    oldValPedal1 = analogRead(EXP_PEDAL1) >> 3;
}   
 
void loop()
{  
    newValPedal1 = analogRead(EXP_PEDAL1) >> 3;
    if(abs(newValPedal1 - oldValPedal1) > 1) {
       MidiUSB.sendMIDI(getExpPedalCC(18, newValPedal1));
       MidiUSB.flush(); 
       oldValPedal1 = newValPedal1;
    }
    if( digitalRead(2) == false ) 
    { 
        // note on 
        midiEventPacket_t noteOn = {CC, CHANNEL, 18, 127}; 
        MidiUSB.sendMIDI(noteOn); 
        MidiUSB.flush(); 
        digitalWrite(3, !digitalRead(3));
        delay(500); 
    }
}

midiEventPacket_t getExpPedalCC(uint8_t CCvalue, uint8_t level) {
  return (midiEventPacket_t) {CC, CHANNEL, CCvalue, level};
}
