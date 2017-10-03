#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

#define DHT_PIN 14 // what pin we're connected to
#define LED_S 2   // Pin 2  LED
#define LED_R 15  // Pin 15 Red
#define LED_G 12  // Pin 12 Green
#define LED_B 13  // Pin 13 Blue
#define SCL 4
#define SDA 5
#define FAN 16
#define DHTTYPE DHT11 // DHT 1  

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3f, 16, 2); // 0x27
SimpleDHT11 dht11;  
void setup()
{
  Serial.begin(115200); 
  Serial.println("DHTxx test!");
  pinMode(LED_S, OUTPUT);  
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT);  
  pinMode(LED_B, OUTPUT);  
  pinMode(FAN, OUTPUT);
//  pinMode(SW, INPUT);
 // initialize the LCD
 lcd.begin(SDA,SCL); // SDA Pin5, SCL Pin4
 // Turn on the blacklight and print a message.
// lcd.backlight();
  lcd.setCursor(0,0); // col=0, row=1
  //         1234567890123456
 lcd.print(" Nuntchayathorn ");
  lcd.setCursor(0,1); // col=0, row=1
  //         1234567890123456
  lcd.print(" T=24 H=50 F=ON");
}

void loop()
{
   byte temp = 0, humi = 0;
  int err = dht11.read(DHT_PIN, &temp, &humi, NULL);
  if (err != SimpleDHTErrSuccess) { return; }
  Serial.printf("TEMP=%d\tHUMI=%d\n", temp, humi);
  if (temp>24) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    lcd.setCursor(0,1); // col=0, row=1
    //         1234567890123456
    lcd.print(" T=");    lcd.print(temp);
    lcd.print(" H=");    lcd.print(humi);
    lcd.print(" F=ON "); digitalWrite(FAN, HIGH);
  } else {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    lcd.setCursor(0,1); // col=0, row=1
    //         1234567890123456
    lcd.print(" T=");    lcd.print(temp);
    lcd.print(" H=");    lcd.print(humi);
    lcd.print(" F=OFF"); digitalWrite(FAN, LOW);
  }
  if (humi>50) {
    digitalWrite(LED_S, HIGH);
  } else {
    digitalWrite(LED_S, LOW);    
  }


  delay(1000);

}
