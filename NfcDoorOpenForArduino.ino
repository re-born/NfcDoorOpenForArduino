#include <stdio.h>
#include <Wire.h>
#include <Servo.h>
#include <FlexiTimer2.h>  //http://playground.arduino.cc/Main/FlexiTimer2
#include "rgb_lcd.h"

const int pin_servo = 3;
const int pin_led = 53;  //for debug
const int open_duration = 3000;
const int close_degree = 159;
const int open_degree = 132;

char serial_recv;
int counter;  //for debug

Servo grove_servo;
rgb_lcd lcd;  //for debug

void delay_close() {
  grove_servo.write(close_degree);
  FlexiTimer2::stop();
}

void setup(){
  Serial.begin(9600);

  pinMode(pin_led, OUTPUT);  //for debug
  grove_servo.attach(pin_servo);
  grove_servo.write(close_degree);
  
// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);  //for debug
  lcd.setRGB(0, 0, 0);  //for debug
  counter = 0;  //for debug
// Print a message to the LCD.
  lcd.print(counter);  //for debug
}

void loop(){
  Serial.flush();
  if(Serial.available() > 0){
    digitalWrite(pin_led, HIGH);  //for debug
    serial_recv = Serial.read();
    if (serial_recv == 'o'){
      FlexiTimer2::stop();
      grove_servo.write(open_degree);
      
      counter++;  //for debug
      lcd.print(counter);  //for debug
      
      FlexiTimer2::set(open_duration, delay_close);
      FlexiTimer2::start();
        
    } else {
//      when receiving data excepting 'o'
    }
//    Serial.println(serial_recv);
  } else {
//    when not having buffer
    digitalWrite(pin_led, LOW);  //for debug
  }
  delay(10);
}
