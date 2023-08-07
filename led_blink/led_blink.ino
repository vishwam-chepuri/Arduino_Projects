#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9); // RX, TX
int LED = 13;
int buzzer = 12;
int Blink= 7;// the on-board LED
int Data; // the data received

void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  pinMode(LED,OUTPUT);

}

void loop() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    if(Data == '1')
    {  
      digitalWrite(LED,1);
      Serial.println("LED On!");
      Bluetooth.println("LED On!");
            }
    else if(Data =='2')        
    {

       digitalWrite(LED,0);
       Serial.println("LED Off!");
       Bluetooth.println("LED  On D13 Off ! ");
    }
    else if(Data =='5')
    { 
        digitalWrite(buzzer,1);
        Serial.println("Buzzer on");
        Bluetooth.println("Buzzer on");
    }
    else if(Data =='6')
     {
        digitalWrite(buzzer,0);
        Serial.println("Buzzer off");
        Bluetooth.println("Buzzer D12 off");
     }
     else if(Data =='3')
     { int Blink = 7;
      Serial.println("BLink on");
      Bluetooth.println("Blink on");int f;
      if(digitalRead(LED) == 0){f = 0;}
      else { f = 1;}
      while(Bluetooth.read()!='4')
      { digitalWrite(LED,1);
        digitalWrite(Blink,1);
        delay(80);
        digitalWrite(LED,0);
        digitalWrite(Blink,0);
        delay(300);
        
      }
      if(f == 1)
        {digitalWrite(LED,1);digitalWrite(Blink,1);}
      else 
      { digitalWrite(LED,0); digitalWrite(Blink,0);}      
     }
     else if(Data =='4')
     {
      digitalWrite(Blink,0);
      Serial.println("BLink off");
      Bluetooth.println("Blink off");
     }
  } 
   else{;}   
delay(10);
}
