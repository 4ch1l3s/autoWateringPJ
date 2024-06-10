
#include <LiquidCrystal.h> //LCD Library - thư viện điều khiển màn hình LCD

// note tượng trưng cho tần số tương ứng để phát âm qua loa
#define NOTE_C6 1100


int temp;
//chân cảm biến nhiệt độ và chân cảm biến độ ẩm đất
int T_Sensor = A3;
int M_Sensor = A0;
//chân led báo hiệu nước
int W_led = 7;
//chân led báo hiệu bơm
int P_led = 13;
//chân loa
int Speaker = 9;
//giá trị nhiệt độ - val là giá trị anal, cel là giá trị sau chuyển đổi
int val;
int cel;  
//các chân cắm hiển thị lên mand LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
 {
    lcd.begin(16, 2);
    lcd.clear(); 
    pinMode(13,OUTPUT);
    pinMode(7,INPUT);
    pinMode(9,OUTPUT);
    

    lcd.setCursor(0,0);
    lcd.print("MADE BY");
    lcd.setCursor(0,1);
    lcd.print("NOBODY");
    delay(1000);
    Serial.begin(9600);
   
}

void loop()
{


  lcd.clear();
  int Moisture = analogRead(M_Sensor); //Đọc giá trị của cảm biến độ ẩm đất
  val = analogRead(T_Sensor); //Đọc giá trị cảm biến nhiệt độ
  int mv = (val/2)-1;
  cel = mv;



  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.setCursor(5,0);
  lcd.print(cel);
  lcd.setCursor(7,0);
  lcd.print("'C");
 
 if (Moisture> 700)   // Trong trường hợp đất khô
  { 
        lcd.setCursor(11,0);
        lcd.print("DRY");
        lcd.setCursor(11,1);
        lcd.print("SOIL");
       if (digitalRead(W_led)==1) 
       {
         digitalWrite(13, HIGH);
         lcd.setCursor(0,1);
         lcd.print("PUMP:ON");
       }
       else
       {
         digitalWrite(13, LOW);
         lcd.setCursor(0,1);
         lcd.print("PUMP:OFF");
           
           tone(Speaker, NOTE_C6, 2000); 
           delay(1000); 
           tone(Speaker, NOTE_C6, 2000); 
           delay(1000); 
           tone(Speaker, NOTE_C6, 2000); 
           delay(1000); 
   
       }
    }
 
     if (Moisture>= 300 && Moisture<=700) //Trong trường hợp đất ẩm 
    { 
      lcd.setCursor(11,0);
     lcd.print("MOIST");
     lcd.setCursor(11,1);
     lcd.print("SOIL");
     digitalWrite(13,LOW);
     lcd.setCursor(0,1);
     lcd.print("PUMP:OFF");    
  }
 
  if (Moisture < 300)  // Trong trường hợp đất ướt
  { 
    lcd.setCursor(11,0);
     lcd.print("WET");
     lcd.setCursor(11,1);
     lcd.print("SOIL");
     digitalWrite(13,LOW);
     lcd.setCursor(0,1);
     lcd.print("PUMP:OFF");
  }

 Serial.print(cel);
 Serial.print("x");
 Serial.print(Moisture);


 Serial.println();
 delay(1000);    
}  
