/**********************************************************************
* © 2014 YD Ynvisible, S.A.
*
* FileName:        Bluetooth_Fan.ino
* Dependencies:    SoftwareSerial.h
* Processor:       ATmega328
* IDE:             Arduino 1.0.5
*
* Description:
* Fan activated by a smartphone via Bluetooth 4.0
* Sending '#' activates the fan
**********************************************************************/

#include <SoftwareSerial.h> //Software Serial Port
#define RxD 11  //Bluetooth TX=Core RX
#define TxD 12  //Bluetooth RX=Core TX

int motor1_pwm=6; //Motor1 PWM
int motor1_dir=7; //Motor1 Direction
char recvChar=0;
  
SoftwareSerial blueToothSerial(RxD,TxD);

void setup()
{
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(motor1_pwm, OUTPUT); 
  pinMode(motor1_dir, OUTPUT); 
  digitalWrite(motor1_pwm,LOW);
  digitalWrite(motor1_dir,LOW);
  
  setupBlueToothConnection();        
}
void loop()
{
  if(blueToothSerial.available()){     //check if the pipe is free
    recvChar = blueToothSerial.read();
    if(recvChar=='#'){
      analogWrite(motor1_pwm,40);
      digitalWrite(motor1_dir,LOW);
    }
    else{
      analogWrite(motor1_pwm,0);  
      digitalWrite(motor1_dir,LOW);   
    }  
  }
}  
  
void setupBlueToothConnection(){
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 9600
  delay(10); // This delay is required.
  blueToothSerial.print("AT+RENEW"); //Restore all setup value to factory setup
  delay(10);  // This delay is required.
  blueToothSerial.print("AT+ROLE0"); //make it a slave   
  delay(10);  // This delay is required.
}
