
#include "Arduino.h"

#define PROBE_PIN 13

/**
 *
 */
 
 
static inline void wait_for_state(bool state) {
    
    //Wait for the first bit;
    while(digitalRead(PROBE_PIN) != state);
    
}

uint8_t probe_read() {
  
   
    //Wait for low state;
    wait_for_state(0);
    
    //Wait for high state;
    wait_for_state(1);
    
    //Save the time;
    uint32_t init_time = micros();

    //Wait for low state;
    wait_for_state(0);
    
    //Save the bit time;
    uint32_t bit_time = micros() - init_time;
    
    //Wait a bit time and a half to sync on the middle of the bit;
    delayMicroseconds(bit_time + (bit_time >> 1));
    
    
    //Cache the read value;
     uint8_t res = 0;
    
    uint8_t msk = 1;
    
    //For each bit : 
    for (uint8_t i = 8; i--;) {
      
      //If the line is high, bit is set;
      if (digitalRead(PROBE_PIN)) {
        res |= msk;    
      }
          
      //Shift the mask;
      msk<<=1;
      
     delayMicroseconds(bit_time);
     
    }
    
    return res;
}


void setup() {
  
  Serial.begin(57600);
  
  pinMode(PROBE_PIN, INPUT);
  
}

void loop() {
  
  while(true) {
    
    uint8_t c = probe_read();
    
     Serial.print((char)c);

  }
  
    
}


