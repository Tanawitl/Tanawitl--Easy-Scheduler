
void TFT_AA() {

  //เริ่มต้นทำงาน
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(tft.color24to16(0xFFFFFF));//สีข้อความ
  tft.setTextSize(8);                         //ขนาดข้อความ
  tft.drawString("WELCOME", 100, 140);        //ข้อความ 100-160
  delay(3000);

//ส่วนของเมนู วัดระยะ
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(tft.color24to16(0xFFFFFF));          //สีข้อความ
  tft.setTextSize(2);                                   //ขนาดข้อความ
  tft.drawString("Distance menu choice", 0, 10);        //ข้อความ 100-160
  tft.setTextSize(2);                                   //ขนาดข้อความ
  tft.drawString("choice => ", 0, 40);           //ข้อความ 100-170
  tft.drawString("(A) Warning distance : 800 mm", 0, 70);   //ข้อความ
  tft.drawString("(B) Warning distance : 1000 mm", 0, 110);
  tft.drawString("(C) Warning distance : 1500 mm", 0, 150);
  tft.setTextColor(tft.color24to16(0xFF0000));          //สีข้อความ
  tft.setTextSize(2.5);                                   //ขนาดข้อความ
  tft.drawString("Timeout select 5 ms", 0, 190);
  delay(10000);//ทำต่อใน 10 ms
  
//เข้าเงื่อนไข
  choice = Serial.read();         //อ่านค่าที่เลือกจากSerial เปลี่ยนเป็นสวิตกด
  if ( choice == 'a') {
    Distance = 800;
    Serial.println("Distance = 800 mm");
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(tft.color24to16(0xFFFFFF));        //สีข้อความ
  tft.setTextSize(3);                                 //ขนาดข้อความ
  tft.drawString("Distance is: ", 60, 150);           //ข้อความ
  tft.setCursor(330, 150);
  tft.print(Distance);
  delay(3000);
  }
  else if( choice == 'b') {
    Distance = 1000;
    Serial.println("Distance = 1000 mm");
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(tft.color24to16(0xFFFFFF));        //สีข้อความ
  tft.setTextSize(3);                                 //ขนาดข้อความ
  tft.drawString("Distance is: ", 60, 150);          //ข้อความ
  tft.setCursor(330, 150);
  tft.print(Distance);
  delay(3000);
  }
  else if( choice == 'c') {
    Distance = 1500;
    Serial.println("Distance = 1500 mm");
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(tft.color24to16(0xFFFFFF));        //สีข้อความ
  tft.setTextSize(3);                                 //ขนาดข้อความ
  tft.drawString("Distance is: ", 60, 150);          //ข้อความ
  tft.setCursor(330, 150);
  tft.print(Distance);
  delay(3000);
  }
  else{
    Distance = 600; Serial.println("Auto distance = 600 mm"); delay(1000);//( choice != 'a'||'b'||'c')
    tft.fillScreen(TFT_BLUE);
    tft.setTextColor(tft.color24to16(0xFFFFFF));        //สีข้อความ
    tft.setTextSize(3);                                 //ขนาดข้อความ
    tft.drawString("Auto distance", 130, 150);           //ข้อความ
    delay(5000);
  }

//delay(3000);
/************************แสดงพื้นหลังพวกกรอบ************************************/

  tft.fillScreen(tft.color24to16(0xFFFFFF));
  tft.fillRect(150, 5, 200, 70, tft.color24to16(0x6699FF));//ระยะ
  tft.setTextColor(tft.color24to16(0xFFFFFF));//สีข้อความ
  tft.setTextSize(2);//ขนาดข้อความ
  tft.drawString("Phase", 155, 10);//ข้อความ
  tft.drawString("MM", 320, 60);//ข้อความ

  tft.drawFastHLine(0, 80, 480, tft.color24to16(0x6699FF));//เส้นบน
  tft.drawFastHLine(0, 185, 480, tft.color24to16(0x6699FF));//เส้นล่าง

  tft.fillRect(0, 190, 160, 195, tft.color24to16(0x6699FF));//หัวใจ
  tft.setTextColor(tft.color24to16(0xFFFFFF));//สีข้อความ
  tft.setTextSize(2);//ขนาดข้อความ
  tft.drawString("Heart rate", 10, 195);//ข้อความ
  tft.drawString("rpm", 120, 300);//ข้อความ

  tft.fillRect(165, 190, 155, 195, tft.color24to16(0x6699FF));//ออกซิเจน
  tft.setTextColor(tft.color24to16(0xFFFFFF));//สีข้อความ
  tft.setTextSize(2);//ขนาดข้อความ
  tft.drawString("Spo2", 170, 195);//ข้อความ
  tft.drawString("%", 300, 300);//ข้อความ

  tft.fillRect(325, 190, 480, 195, tft.color24to16(0x6699FF));//อุณหภูมิ
  tft.setTextColor(tft.color24to16(0xFFFFFF));//สีข้อความ
  tft.setTextSize(2);//ขนาดข้อความ
  tft.drawString("Temp", 330, 195);//ข้อความ
  tft.drawString("C", 460, 300);//ข้อความ


  /*
    //ทดสอบข้อความ
    tft.setTextColor(tft.color24to16(0x33FFFF));//สีข้อความ
    tft.setTextSize(5);//ขนาดข้อความ
    tft.drawString("BALANCE", 145, 130);//ข้อความ
  */

}
