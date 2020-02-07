#include <Servo.h>
#include "DHT.h"

#define DHTTYPE DHT11
//Connection to the humidity sensor
const int DHTPIN = 5; //What digital pin we're connected to
#ifdef DHTTYPE DHT11
  DHT dht(DHTPin, DHTTYPE);
#endif


// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 90;   // 90;     // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

//Horizontal servo for the door
Servo horizontal_2;
int servo_h = 90;

int servo_h_LimitHigh = 180;
int servo_h_LimitLow = 65;

// 65 degrees MAX
Servo vertical;   // vertical servo
int servov = 90;    //   90;     // stand vertical servo

int servovLimitHigh = 120;
int servovLimitLow = 15;


// LDR pin connections
//  name  = analogpin;
int ldrlt = 2; //LDR top left - BOTTOM LEFT    <--- BDG
int ldrrt = 3; //LDR top rigt - BOTTOM RIGHT
int ldrld = 0; //LDR down left - TOP LEFT
int ldrrd = 1; //ldr down rigt - TOP RIGHT

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  horizontal.attach(9);
  horizontal.write(180);

  vertical.attach(10);
  vertical.write(45);

  horizontal_2.attach(8);
  horizontal_2.write(180);
  dht.begin();

  delay(3000);
}

void loop()
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt

  // int dtime = analogRead(4)/20; // read potentiometers
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;

  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt


  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");


  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh)
     {
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }

  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime);

   //Door algorithm to open and close
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   if(isnan(h) || isnan(t)){
     Serial.println("Failed to read from DHT sensor...");
     return;
   }

   Serial.print("Humidity: ");
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.print(" *C ");

 // Depending on the humidity the trap attached to the servo will open
 // and let the water pass through
     if(h < 40){
       servo_h = servo_h_LimitLow;
     }else{
       servo_h = servo_h_LimitLow;
     }
     horizontal_2.write(servo_h);


}
