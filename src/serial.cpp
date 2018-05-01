#include "serial.h"

#include <Arduino.h>
#include <VescUart.h>
#include <datatypes.h>
#include <driver/uart.h>
#include "analog.h"
#include "mpu.h"

#include <PID_v1.h>


double Setpoint, Input, Output;
double Kp=1, Ki=3, Kd=4;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);



struct bldcMeasure measuredVal;
//unsigned long count=20;
HardwareSerial Serial1(1);
HardwareSerial Serial2(2);
//uint8_t mc_payload[512];
int dir=0;
int lastdir=0;

long ago(long a){
  return millis()-a;
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint32_t lastmove=0;
bool brake(){
  return 0;
  if(leftnow!=0 || rightnow!=0)lastmove=millis();
  if(millis()-lastmove>2000)return 1;
  return 0;
}

void drive(float current,int vesc){
  if(digitalRead(15) || current>10 || current<-10){
    VescUartSetCurrentBrake(10,0);
    VescUartSetCurrentBrake(10,1);
  }
  else VescUartSetCurrent(current,vesc);
}

void serial_task(void *pvParameter){

  Serial1.begin(115200, SERIAL_8N1, 13,12);// RX, TX
  Serial2.begin(115200, SERIAL_8N1, 14,27);// RX, TX

  SetSerialPort(&Serial1,&Serial2,&Serial2,&Serial2);//,nullptr,nullptr);
  SetDebugSerialPort(NULL);//&Serial);

  //delay(500);
  Input = kalAngleY;
  Setpoint = 17;

 //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-5,5);

  while(1){
    /*if (VescUartGetValue(measuredVal,0)) {
  		Serial.println("ONE: ");// Serial.println(count++);
  		//SerialPrint(measuredVal);
  	}
  	else
  	{
  		Serial.println("Failed to get data one!");
  	}
    if (VescUartGetValue(measuredVal,1)) {
  		Serial.println("TWO: ");// Serial.println(count++);
  		//SerialPrint(measuredVal);
  	}
  	else
  	{
  		Serial.println("Failed to get data two!");
  	}*/


    /*if(ago(lastdir)<300){
      switch(dir){
        case 1:
          drive(-5,1);
          drive(5,0);
          break;
        case 2:
          drive(5,1);
          drive(5,0);
          break;
        case 3:
          drive(-5,1);
          drive(-5,0);
          break;
        case 4:
          drive(5,1);
          drive(-5,0);
          break;
      }
    }*/
  if(kalAngleY>10 && kalAngleY<30){
    Input = kalAngleY;
    myPID.Compute();
    drive(Output,0);
    drive(-Output,1);
  }
  else{
    if(leftnow==0){
      drive(0,1);
    }
    else drive(-leftnow/5,1);

    if(rightnow==0){
      drive(0,0);
    }
    else drive(rightnow/5,0);
  }



  //Serial.print(compAngleY);
  //Serial.print("\t");
  Serial.println(kalAngleY);

    delay(10);





    /*if(leftnow==0)VescUartSetCurrent(0,1);
    else VescUartSetRPM(mapf(leftnow,0.0,100.0,0.0,13000.0),1);

    if(rightnow==0)VescUartSetCurrent(0,0);
    else VescUartSetRPM(mapf(rightnow,0.0,100.0,0.0,13000.0),0);*/


    //VescUartSetRPM(mapf(leftnow,0.0,100.0,0.0,13000.0),1);
    //VescUartSetRPM(mapf(rightnow,0.0,100.0,0.0,13000.0),0);





    /*if(Serial1.available()){
      Serial.write(Serial1.read());
    }
    if(Serial.available()){
      Serial1.write(Serial.read());
    }*/
    //delayMicroseconds(1);
  }

  vTaskDelete( NULL ); //will never happen
}
