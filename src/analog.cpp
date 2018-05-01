#include "serial.h"

#include <Arduino.h>
#include <VescUart.h>
#include <datatypes.h>
#include <driver/uart.h>
#include <Coordinates.h>
Coordinates point = Coordinates();

#define DEADBAND 4 //adjust till desired deadband is achieved
#define DEBUG true // set to false to stop serial messages

int leftnow = 0;
int rightnow = 0;

int throttle, steering;
int xraw, yraw, leftSpd, rightSpd;

int lastl = 0;
int lastr = 0;
double lastrr=0;

void analog_task(void *pvParameter){

  pinMode(33,INPUT);
  pinMode(32,INPUT);
  pinMode(35,INPUT);

  analogReadResolution(11); // Default of 12 is not very linear. Recommended to use 10 or 11 depending on needed resolution.
  analogSetAttenuation(ADC_11db);

  while(1){

    int raw_z=analogRead(33);
    int raw_x=analogRead(35);
    int raw_y=analogRead(32);
    //Serial.println(String("")+raw_x+" "+raw_y+" "+raw_z);
  //  delay(100);


  yraw = raw_y-385;
  xraw = raw_x-375;

  /*Serial.print("x ");
  Serial.print(xraw);
  Serial.print(" y ");
  Serial.println(yraw);*/

  /*if(xraw>-40 && xraw<+40)xraw=0;
  else if(xraw<512-40)xraw+=40;
  else if(xraw>512+40)xraw-=40;

  if(yraw>-40 && yraw<+40)yraw=0;
  else if(yraw<-40)yraw+=40;
  else if(yraw>+40)yraw-=40;*/

  yraw=-yraw;


  point.fromCartesian(xraw,yraw);
  //if(angle<0)angle+=360;

  int angle=(int)(point.getAngle()*180.0/M_PI);



  if(xraw>=0 && yraw>=0){
    leftnow=100;
    rightnow=map(angle,90,0,100,-100);

  }
  if(xraw>=0 && yraw<0){
    leftnow=map(angle,360,270,100,-100);
    rightnow=-100;

  }
  if(xraw<0 && yraw<0){

    leftnow=-100;
    rightnow=map(angle,270,180,-100,100);
  }
  if(xraw<0 && yraw>=0){
    leftnow=map(angle,180,90,-100,100);
    rightnow=100;

  }

  //int max=sqrt(sin(point.getAngle())*sin(point.getAngle())+cos(point.getAngle())*cos(point.getAngle()))*100;
  //Serial.println(max);

  double r=point.getR();

  /*int d=500;
  if(power==1)d=300;
  if(power==2)d=200;
  if(power==3)d=100;*/

  if(leftnow>100)leftnow=100;
  if(rightnow>100)rightnow=100;
  if(leftnow<-100)leftnow=-100;
  if(rightnow<-100)rightnow=-100;

  int ar=raw_z;//analogRead(A5);

  int power=map(ar,840,0,1000,375); //actually a output of +-500 was expected...

  leftnow=leftnow*r/power;
  rightnow=rightnow*r/power;



  if(rightnow>500)rightnow=500;
  if(rightnow<-500)rightnow=-500;

  if(leftnow>500)leftnow=500;
  if(leftnow<-500)leftnow=-500;


  //Serial.println(String("")+leftnow+" "+rightnow);


  if(leftnow<DEADBAND && leftnow>-DEADBAND)leftnow=0;
  if(rightnow<DEADBAND && rightnow>-DEADBAND)rightnow=0;

  delay(1);

  //Serial.println(digitalRead(2));


  //Serial.print(1500+leftnow);Serial.print(" ");
  //Serial.println(1500+rightnow);
  //Serial.print(r);Serial.print(" ");
  //Serial.println(lastrr);

  //Serial.print(lastl);Serial.print(" ");
  //Serial.println(lastr);

  }

  vTaskDelete( NULL ); //will never happen
}
