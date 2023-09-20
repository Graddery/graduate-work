#define USE_ARDUINO_INTERRUPTS true                    // Set-up low-level interrupts for most acurate BPM math
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
#include <I2Cdev.h>
#include <MPU9250.h>
#include <Wire.h>
MPU9250 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t walk;
long ACC, GYR;
long maxACC, maxGYR, trACC, trGYR;
#include <PulseSensorPlayground.h>                    // Includes the PulseSensorPlayground Library
const int PulseWire = 0;
int Threshold = 550;
const int LED13 = 13;                                 // The on-board Arduino LED
PulseSensorPlayground pulseSensor;
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
#include <SoftwareSerial.h>
SoftwareSerial sim800l(8, 9);                         // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted
void setup() {
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    //Serial.println("PulseSensor object created!");
  }
  delay(100);
  oled.init();                                        // initialization
  oled.clear();                                       // clear screen
  oled.setScale(1);                                   // text size (1..4)
  //oled.setCursorXY(8, 17);
  delay(1000);
  oled.print("Привет");
  //oled.print("Hello");
  Wire.begin();
  mpu.initialize();
  mpu.setFullScaleAccelRange(MPU9250_ACCEL_FS_2);
  delay(1000);
  for (int i = 0; i < 30; i++) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ACC = abs(ax) + abs(ay) + abs(az);
    GYR = abs(gx) + abs(gy) + abs(gz);
    if (ACC > maxACC) maxACC = ACC;
    if (GYR > maxGYR) maxGYR = GYR;
    delay(5);
  }
  maxACC = maxACC + trACC;
  maxGYR = maxGYR + trGYR;
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  sim800l.begin(9600);                                // Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);
  delay(1000);
}
void SendSMS1()
{
  sim800l.print("AT+CMGF=1\r");                        // Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+79638636037\"\r");         // Your phone number example +212123456789"
  delay(150);
  sim800l.print("I need a help");                      // This is the text to send to the phone number
  delay(150);
  sim800l.print((char)26);                             // (required according to the datasheet)
  delay(150);
  sim800l.println();
  Serial.println("Text Sent.1");
  delay(10);
  }
void SendSMS2()
{
  sim800l.print("AT+CMGF=1\r");                           
  delay(100);
  sim800l.print("AT+CMGS=\"+79638636037\"\r");           
  delay(150);
  sim800l.print("I am okey");                             
  delay(150);
  sim800l.print((char)26);                                
  delay(150);
  sim800l.println();
  Serial.println("Text Sent.2");
  delay(10);
  }
void SendSMS3()
{
  sim800l.print("AT+CMGF=1\r");                          
  delay(100);
  sim800l.print("AT+CMGS=\"+79638636037\"\r");            
  delay(150);
  sim800l.print("Call to my phone pls");                 
  delay(150);
  sim800l.print((char)26);                                
  delay(150);
  sim800l.println();
  Serial.println("Text Sent.3");
  delay(10);
  }
void SendSMS4()
{
  sim800l.print("AT+CMGF=1\r");                           
  delay(100);
  sim800l.print("AT+CMGS=\"+79638636037\"\r");            
  delay(150);
  sim800l.print("Fast call 03!");                         
  delay(150);
  sim800l.print((char)26);                                
  delay(150);
  sim800l.println();
  Serial.println("Text Sent.4");
  delay(10);
  }
void SendSMSbpm()
{
  sim800l.print("AT+CMGF=1\r");                           
  delay(100);
  sim800l.print("AT+CMGS=\"+79638636037\"\r");            
  delay(150);
  sim800l.print("BPM is low or high!");                   
  delay(150);;
  sim800l.print((char)26);                                
  delay(150);
  sim800l.println();
  Serial.println("Text Sent.BPM");
  delay(10);
  }
void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  // summ ACC and GYR cord
  ACC = abs(ax) + abs(ay) + abs(az);
  GYR = abs(gx) + abs(gy) + abs(gz);
  if (ACC > 5*maxACC || GYR > 5*maxGYR) {  
    walk++;                                
  }
  oled.clear();                                                         
  oled.setCursorXY(8, 17);
  oled.print("Шагов: ");
  oled.println(walk);
  Serial.print(walk);
  int myBPM = pulseSensor.getBeatsPerMinute();
  delay(10);
  oled.setCursorXY(8, 30);
  oled.print("Пульс: ");
  oled.print(abs(myBPM-145));                          // Print the BPM value
  
  //delay(1600);
  if (digitalRead(button1)== LOW){                    // Yellow button
    delay(50);
    SendSMS1();
  }
  if (digitalRead(button2)== LOW){                    // White button
    delay(50);
    SendSMS2();
  }
  if (digitalRead(button3)== LOW){                    // Blue button
    delay(50);
    SendSMS3();
  }
  if (digitalRead(button4)== LOW){                    // Red button
    delay(50);
    SendSMS4();
  }
  if (sim800l.available()){                           // Displays on the serial monitor if there's a communication from the module
    Serial.write(sim800l.read()); 
  }
  if (abs(myBPM-145) > 119 and abs(myBPM-145) != 145 or abs(myBPM-145) < 55 and abs(myBPM-145) > 20){
    SendSMSbpm();
  }
}
