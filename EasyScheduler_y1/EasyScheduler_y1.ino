
#include <EasyScheduler.h>


//Scheduler
Schedular Task1; // สร้างงาน Task
Schedular Task2;
Schedular Task3;
Schedular Task4;
Schedular Task5;
Schedular Task6;

int Distance = 0;
char choice;

int buzzer =13; //buzzer

#include "config.h"

#define time_A 300 //กำหนดการทำงานใน Tasks

void setup() {
  
  Serial.begin(9600);
  Task1.start(); // สั่งให้งาน Task เริ่มทำงาน
  Task2.start();
  Task3.start();
  Task4.start();
  Task5.start();
  Task6.start();

   pinMode(buzzer, OUTPUT); //buzzer

  //setupจอTFT
  tft.init();
  tft.setRotation(1);
  TFT_AA();


  //setupวัดระยะ
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    tft.setTextColor(tft.color24to16(0xFF4500));
    tft.setTextSize(2);//ขนาดข้อความ
    tft.drawString("Failed to detect and initialize sensor!", 10, 120);
    while (1) {}
  }
  sensor.startContinuous();//วัดระยะ

  //setupแกน
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);


  Serial.println("Initializing...");
  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED


}

/*****************************************void loop*************************************************/
void loop() {
  
  Task1.check(t1Callback, time_A); // ทำงานฟังก์ชั่น LED1_blink ทุก 1 วินาที
  Task2.check(t2Callback, time_A); 
  Task3.check(t3Callback, time_A); 
  Task4.check(t4Callback, 0); 
  Task5.check(t5Callback, time_A); 
  Task6.check(t6Callback, time_A); 

  long i = sensor.readRangeContinuousMillimeters();
  DacAudio.FillBuffer();                       // Fill the sound buffer with data
  if (i > Distance)
  {
    char c = 'A';
    switch (c) {
      case 'A':
        DacAudio.Play(&ForceWithYou);          // play it, this will cause it to repeat and repeat...
        break;                                 //การพักคำสั่ง เมื่อ case ตรงตามเงื่อนไขจะออกจาก switch ทันที
     }
   }

   A_sensor();//หัวใจ




}
void t1Callback() {

  //แสดงระยะ
  long phase = sensor.readRangeContinuousMillimeters();
  Serial.print("phase : ");
  Serial.println(phase);
  tft.fillRect(200, 50, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(200, 50);
  tft.print(phase);

  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }
  Serial.println();
  if (sensor.readRangeContinuousMillimeters() < Distance)
  {
    tft.fillRect(0, 85, 480, 95, tft.color24to16(0xFFFFFF));//ปิดข้อความแจ้งเตือนตรงกลาง
    //tft.setTextSize(3);
    tft.setTextColor(tft.color24to16(0xFF4500));
    tft.setTextSize(5);//ขนาดข้อความ
    tft.drawString("Be Careful", 100, 120);
  }
  else
  {
    tft.fillRect(0, 85, 480, 95, tft.color24to16(0xFFFFFF));//ปิดข้อความแจ้งเตือนตรงกลาง
    //tft.setTextSize(3);
    tft.setTextColor(tft.color24to16(0xFF4500));
    tft.setTextSize(5);//ขนาดข้อความ
    tft.drawString("****safe****", 70, 120);
  }

}
void t2Callback() {

  //แสดงแกน
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) //Tmp/340.00+36.53
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("ACC X:");
  Serial.print(AcX);
  Serial.print("  ACC Y:");
  Serial.print(AcY);
  Serial.print("  ACC Z:");
  Serial.print(AcZ);
  Serial.println();
  //แสดงแกนบนจอ
  tft.fillRect(0, 20, 130, 45, tft.color24to16(0xFFFFFF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("ACC X: ", 10, 20);//ข้อความ
  tft.setCursor(45, 20);
  tft.print(AcX);

  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("ACC Y: ", 10, 30);//ข้อความ
  tft.setCursor(45, 30);
  tft.print(AcY);

  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("ACC Z: ", 10, 40);//ข้อความ
  tft.setCursor(45, 40);
  tft.print(AcZ);

}
void t3Callback() {

  //จำลองแสดงค่า Tmp
  tft.fillRect(360, 250, 90, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(360, 250);
  tft.print(Tmp/340.00+36.53);


}
void t4Callback() {

// Serial.println(F("Wait about four seconds"));
// particleSensor.heartrateAndOxygenSaturation(/**SPO2=*/&SPO2, /**SPO2Valid=*/&SPO2Valid, /**heartRate=*/&heartRate, /**heartRateValid=*/&heartRateValid);
  //Print result 
/*  Serial.print(F("heartRate="));
  Serial.print(heartRate, DEC);
  Serial.print(F(", heartRateValid="));
  Serial.print(heartRateValid, DEC);
  Serial.print(F("; SPO2="));
  Serial.print(SPO2, DEC);
  Serial.print(F(", SPO2Valid="));
  Serial.println(SPO2Valid, DEC);
  //หัวใจ
  tft.fillRect(30, 250, 100, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(50, 250);
  tft.print(heartRate);
  //ออกซิเจน
  tft.fillRect(180, 250, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(210, 250);
  tft.print(SPO2);
*/

}
void t5Callback() {
  
  //นับเวลาการทำงาน
  int a = millis() / 1000;
  tft.fillRect(0, 0, 120, 20, tft.color24to16(0xFFFFFF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("Time: ", 10, 10);//ข้อความ
  tft.setCursor(40, 10);
  tft.print(a);
  a++;
  
}
void t6Callback() {

 Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers  
  AcX = Wire.read() << 8 | Wire.read(); 
  if (AcX > 8000)
  {
    Serial.print("AcX tt = ");
    Serial.println(AcX);
    char g = 'B';
    switch (g) {
      case 'B':
        digitalWrite(buzzer, HIGH);
         delay(200);
        digitalWrite(buzzer, LOW);
      break;                                 //การพักคำสั่ง เมื่อ case ตรงตามเงื่อนไขจะออกจาก switch ทันที
    }
  }
}
