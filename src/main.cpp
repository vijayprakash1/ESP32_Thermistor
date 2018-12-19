#include <Arduino.h>
#include "esp_adc_cal.h"
#define THERMISTORPIN 26
#define SAMPLERATE 25        // Number of samples to average
#define POWERPIN 25
void setup() {
 Serial.begin(115200);
 pinMode(POWERPIN, OUTPUT);
 digitalWrite(POWERPIN, HIGH);
}

float get_KV_Temp() {
 
 float thermalSamples;
 float  average=0;
 float logR2, R2;
 for (int i = 1; i<SAMPLERATE; i++) {
 thermalSamples = analogRead(THERMISTORPIN);
 //Serial.println(thermalSamples);
 average = ((thermalSamples - average)/i) + average;
 delay(10);
 }
 R2 = 10000 * (4096.0 / average - 1.0);
 Serial.println( R2 );
 logR2 = log(R2);
 Serial.println(logR2);
 double c = (0.001129148 + (0.000234125 + (0.0000000876741 * logR2 * logR2 ))* logR2 );
 Serial.println(c);
 double celcius = (1.0 / c );
 Serial.println(celcius);
 celcius = celcius - 268.15;
 return celcius;
}

void loop() {
   digitalWrite(POWERPIN, HIGH);
   float temp;
   temp = get_KV_Temp();
   Serial.println(temp);
   delay(1000);
}