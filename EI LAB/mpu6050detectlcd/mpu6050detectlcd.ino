#include <Wire.h>

#include<LiquidCrystal.h> // lcd Header

LiquidCrystal lcd(7,6,5,4,3,2);

#include <MPU6050.h>

#define minval -8

#define maxval 10

#define buzzer 8

#define led 13

MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  pinMode(buzzer,OUTPUT);

  pinMode(led,OUTPUT);
  
  lcd.begin(16,2);
  
  Serial.println("Initialize MPU6050");
    
    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))

    { Serial.println("Could not find a valid MPU6050 sensor, check wiring!");

      delay(500);}
      
  lcd.print("EarthQuake ");
  
  lcd.setCursor(0,1);
  
  lcd.print("Detector ");
  
  delay(2000);
  
  lcd.clear();
  
  lcd.print("Calibrating.....");
  
  mpu.setThreshold(3); 
  
  
  checkSettings();
  
  lcd.clear();

  lcd.print("Calibrated");
  
  delay(1000);

  lcd.clear();

  lcd.print("Device Ready");

  delay(1000);

  lcd.clear();

  lcd.print(" X Y Z ");

}

void checkSettings()

{

  Serial.println();
  
  Serial.print(" * Sleep Mode:        ");

  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:      ");

  switch(mpu.getClockSource())

  {case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;

    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;

    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;

    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;

    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;

    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;

    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;

  }

  Serial.print(" * Gyroscope:         ");

  switch(mpu.getScale())

  {case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;

    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;

    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;

    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;}

  Serial.print(" * Gyroscope offsets: ");

  Serial.print(mpu.getGyroOffsetX()); Serial.print(" / ");

  Serial.print(mpu.getGyroOffsetY()); Serial.print(" / ");

  Serial.println(mpu.getGyroOffsetZ()); Serial.println();
 
 }

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  
  Vector rawGyro = mpu.readRawGyro();

  Vector normGyro = mpu.readNormalizeGyro();

  Serial.print(" Xraw = ");    Serial.print(rawGyro.XAxis);

  Serial.print(" Yraw = ");    Serial.print(rawGyro.YAxis);

  Serial.print(" Zraw = ");    Serial.println(rawGyro.ZAxis); 

  
  if(normGyro.XAxis > maxval || normGyro.XAxis < minval && normGyro.YAxis > maxval || normGyro.YAxis  < minval && normGyro.ZAxis > maxval || normGyro.ZAxis  < minval)

  { digitalWrite(led,HIGH);    digitalWrite(buzzer,HIGH);

    Serial.print(" Xnorm = ");   Serial.print(normGyro.XAxis);

    Serial.print(" Ynorm = ");   Serial.print(normGyro.YAxis);

    Serial.print(" Znorm = ");   Serial.println(normGyro.ZAxis);

    delay(10);
    
    lcd.setCursor(0,0);
    
    lcd.print("Earthquake Alert ");
    
    }

   else{
    digitalWrite(led,LOW);

    digitalWrite(buzzer,LOW);}

    Serial.print(" Xnorm = ");   Serial.print(normGyro.XAxis);

    Serial.print(" Ynorm = ");   Serial.print(normGyro.YAxis);

    Serial.print(" Znorm = ");   Serial.println(normGyro.ZAxis);
    
    lcd.clear();    lcd.print(" X     Y     Z ");

    lcd.setCursor(0,1);   lcd.print(normGyro.XAxis);

    lcd.setCursor(6,1);   lcd.print(normGyro.YAxis);

    lcd.setCursor(12,1);  lcd.print(normGyro.ZAxis);

  
    delay(10);
}
