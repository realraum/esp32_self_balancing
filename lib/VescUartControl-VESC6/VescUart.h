/*
Copyright 2015 - 2017 Andreas Chaitidis Andreas.Chaitidis@gmail.com

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _VESCUART_h
#define _VESCUART_h


//#include <Config.h>
#include <HardwareSerial.h>

void SetSerialPort(HardwareSerial* _serialPort1, HardwareSerial* _serialPort2, HardwareSerial* _serialPort3, HardwareSerial* _serialPort4);
void SetSerialPort(HardwareSerial* _serialPort);
void SetDebugSerialPort(HardwareSerial* _debugSerialPort);



/*TThis library was created on an Adruinio 2560 with different serial ports to have a better possibility
to debug. The serial ports are define with #define:
#define SERIALIO Serial1  		for the UART port to VESC
#define DEBUGSERIAL Serial		for debugging over USB
So you need here to define the right serial port for your arduino.
If you want to use debug, uncomment DEBUGSERIAL and define a port.*/


//#ifndef _CONFIG_h
//
//#ifdef __AVR_ATmega2560__
//#define SERIALIO0 Serial
//#define SERIALIO1 Serial1
//#define SERIALIO2 Serial2
//#define SERIALIO3 Serial3
//#define DEBUGSERIAL Serial1
//#endif
//
//#ifdef ARDUINO_AVR_NANO
//#define SERIALIO0 Serial
//#define SERIALIO1 Serial
//#define SERIALIO2 Serial
//#define SERIALIO3 Serial
//#ifdef DEBUG
////#define DEBUGSERIAL Serial
//#endif
////TODO: ifndef DEBUG trow build exception
//#endif
//#endif

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "datatypes.h"
#include "local_datatypes.h"

///SetSerialPort sets the serial to communicate with the VESC
///Multiple ports possible
void SetSerialPort(HardwareSerial*  _serialPort1, HardwareSerial*  _serialPort2, HardwareSerial*  _serialPort3, HardwareSerial*  _serialPort4);
void SetSerialPort(HardwareSerial* _serialPort);

///SetDebugSerialPort sets the serial for debug information

void SetDebugSerialPort(HardwareSerial* _debugSerialPort);

///PackSendPayload Packs the payload and sends it over Serial.
///Define in a Config.h a SERIAL with the Serial in Arduino Style you want to you
///@param: payload as the payload [unit8_t Array] with length of int lenPayload
///@return the number of bytes send

int PackSendPayload(uint8_t* payload, int lenPay, int num);

///ReceiveUartMessage receives the a message over Serial
///Define in a Config.h a SERIAL with the Serial in Arduino Style you want to you
///@parm the payload as the payload [unit8_t Array]
///@return the number of bytes receeived within the payload

int ReceiveUartMessage(uint8_t* payloadReceived, int num);

///Help Function to print struct bldcMeasure over Serial for Debug
///#define DEBUG necessary
///Define in a Config.h the DEBUGSERIAL you want to use

void SerialPrint(const struct bldcMeasure& values);

///Help Function to print uint8_t array over Serial for Debug
///Define in a Config.h the DEBUGSERIAL you want to use

void SerialPrint(uint8_t* data, int len);

///Sends a command to VESC and stores the returned data
///@param bldcMeasure struct with received data
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial
//@return true if success
bool VescUartGetValue(struct bldcMeasure& values, int num);
bool VescUartGetValue(bldcMeasure& values);

///Sends a command to VESC to control the motor current
///@param current as float with the current for the motor
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial

void VescUartSetCurrent(float current, int num);
void VescUartSetCurrent(float current);

///Sends a command to VESC to control the motor brake
///@param breakCurrent as float with the current for the brake
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial

void VescUartSetCurrentBrake(float brakeCurrent, int num);
void VescUartSetCurrentBrake(float brakeCurrent);

///Sends values of a joystick and 2 buttons to VESC to control the nunchuk app
///@param struct remotePackage with all values
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial

void VescUartSetNunchukValues(remotePackage& data, int num);
void VescUartSetNunchukValues(remotePackage& data);

///Sends a command to VESC to control the motor position
///@param position as float with the position in degrees for the motor
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial

void VescUartSetPosition(float position, int num) ;
void VescUartSetPosition(float position) ;

///Sends a command to VESC to control the motor duty cycle
///@param duty as float with the duty cycle for the motor
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial

void VescUartSetDuty(float duty, int num) ;
void VescUartSetDuty(float duty) ;

///Sends a command to VESC to control the motor rotational speed
///@param rpm as float with the revolutions per second for the motor
///@param num as integer with the serial port in use (0=Serial; 1=Serial1; 2=Serial2; 3=Serial3;)
///num must not be set, when only one Serial

void VescUartSetRPM(float rpm, int num);
void VescUartSetRPM(float rpm);

#endif
