#include <ESP8266WiFi.h> 
#include <ThingerESP8266.h>


#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#include <SPI.h>
#include <MFRC522.h>




const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
long duration;
int distance;

ThingerWifi thing("cyber_panda","parking101","cyber_panda");
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
//char a[50]="fhbkjhvy";


void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(1,OUTPUT);// Sets the echoPin as an Input
  pinMode(3,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(12,OUTPUT);
  //thing.add_wifi(".","12345678");
//lcd.setBacklightPin(3,POSITIVE); 
//lcd.setBacklight(HIGH);
//lcd.begin(16,2);
    Serial.begin(115200);
  // put your setup code here, to run once:
   Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

}
void rfid()
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
            {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "65 F5 06 85") //change UID of the card that you want to give access
  {
    
   Serial.println(" Welcome Mr.Circuit ");
    delay(100);
    Serial.println(" Have FUN ");
    Serial.println();
    statuss = 1;
   
  }
  
  else   {
    //lcd.print(" Access Denied ");
      Serial.println(" Access Denied ");
    delay(50);
    digitalWrite(15,HIGH);
    delay(50);
   
 
  }
}

void ultra()
{
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
if(distance<3)
{
  digitalWrite(15,HIGH);
  //digitalWrite(3,LOW);
    
}
else
{
  digitalWrite(15,LOW);
  //digitalWrite(3,HIGH);
}
}
void loop() 
{
  ultra();
  // Look for new cards
  rfid();
  // Clears the trigPin
  thing.handle();
}
