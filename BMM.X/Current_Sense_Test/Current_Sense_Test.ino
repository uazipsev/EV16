#include <Wire.h>
#include <Adafruit_ADS1015.h>

 //Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
Adafruit_ADS1115 ads(0x48);     /* Use thi for the 12-bit version */
Adafruit_ADS1115 ads2(0x49);     /* Use thi for the 12-bit version */
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  //ads.Adafruit_ADS1015(0x48);
  //ads2.Adafruit_ADS1015(0x49);
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
   //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
   ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
   ads2.setGain(GAIN_ONE); 
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
   //ads2.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}

void loop(void) 
{
  float adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  
  //Serial.print("AIN 1 0: "); Serial.println(((((((adc0*0.0625)/1000)/200000)*4990)/40)/1), 6);
  //Serial.print("AIN 1 1: "); Serial.println(((((((adc1*0.0625)/1000)/200000)*4990)/40)/1), 6);
  //Serial.print("AIN 1 2 Volts = : "); Serial.println(((adc2* 0.0625*158)/1000), 2);
  Serial.println("*******************START***************");
  Serial.print("AIN 1 3 Volts = : "); Serial.println(((adc3* 0.125*158)/1000), 2);
 Serial.println("*******************CURRENT***************");
  adc0 = ads2.readADC_SingleEnded(0);
  adc1 = ads2.readADC_SingleEnded(1);
  adc0 = (adc0*0.125)/1000;
  adc1 = (adc1*0.125)/1000;
  Serial.print("AIN 1 0: v in = "); Serial.println(adc0, 6);
  Serial.print("AIN 1 1: v in = "); Serial.println(adc1, 6);
  adc0 = adc0-0.032;
  adc1 = adc1-0.01;
  Serial.println(" offsets fixed");
  Serial.print("AIN 1 0: v in = "); Serial.println(adc0, 6);
  Serial.print("AIN 1 1: v in = "); Serial.println(adc1, 6);
  adc0 = adc0/40;
  adc1 = adc1/40;
  Serial.println(" Gain removed");
  Serial.print("AIN 1 0: v in = "); Serial.println(adc0, 6);
  Serial.print("AIN 1 1: v in = "); Serial.println(adc1, 6);
  adc0 = (adc0/200000)*4999;
  adc1 = (adc1/200000)*4999;
  Serial.println(" Voltage At R sense");
  Serial.print("AIN 1 0: v in = "); Serial.println(adc0, 6);
  Serial.print("AIN 1 1: v in = "); Serial.println(adc1, 6);
  adc0 = adc0/0.0001;
  adc1 = adc1/0.0001;
  Serial.println(" Mesured Current");
  Serial.print("AIN 1 0: v in = "); Serial.println(adc0, 6);
  Serial.print("AIN 1 1: v in = "); Serial.println(adc1, 6);
  Serial.println("*******************END***************");
  //adc2 = ads2.readADC_SingleEnded(2);
  //adc3 = ads2.readADC_SingleEnded(3);
  //Serial.print("AIN 1 0: v in = "); Serial.println((((adc0*0.125)/1000/40)-0.032)/200000*4990, 6);
  //Serial.print("AIN 1 0: v in = "); Serial.println((((adc1*0.125)/1000/40)-0.01)/200000*4990, 6);
  //Serial.print("AIN 1 1: "); Serial.println((((((adc1*0.0625)/1000)/200000)*4990)/40)/1, 6);
  //Serial.print("AIN 1 2: "); Serial.println((((((adc2*0.0625)/1000)/200000)*4990)/40)/1, 6);
  //Serial.print("AIN 1 3: "); Serial.println((((((adc3*0.0625)/1000)/200000)*4990)/40)/1, 6);
  Serial.println(" ");
  
  delay(2000);
}
