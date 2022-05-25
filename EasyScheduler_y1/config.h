//จอTFT
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include "TFT_A.h"

//วัดระยะ
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;

//นับการทำงาน
long elapsedTime = 0; //นับเวลาการทำงาน
long nowTime = 0;     //นับเวลาการทำงาน

//แกน
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

//ลำโพง
#include "SoundData.h"
#include "XT_DAC_Audio.h"

XT_Wav_Class ForceWithYou(Force);     // create an object of type XT_Wav_Class that is used by
XT_DAC_Audio_Class DacAudio(26, 0);   // Create the main player class object.
                                      // Use GPIO 25, one of the 2 DAC pins and timer 0



#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
MAX30105 particleSensor;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

#include"max30102_A.h"





                                    
