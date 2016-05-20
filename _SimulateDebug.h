/* 
* SimulateDebug.h
*
* Created: 5/5/2016 9:17:32 AM
* Author: lenovo
*/
#include <Arduino.h>
//#include <Wire.h>

#ifndef __SIMULATEDEBUG_H__
#define __SIMULATEDEBUG_H__

bool _IsDebuging;

//#define _DEBUG

//void check_debug(){
	//#if DEBUG || _DEBUG
	//isDebuging = true;
	//#else
	//isDebuging = false;
	//#endif
//}
#if DEBUG || _DEBUG
#define delay(s)  sim_delay(s)
void sim_delay(unsigned long ms){
	_IsDebuging = true;
	uint32_t start = micros() + 2000;
		
		while (ms > 0) {
		yield();
			while ( ms > 0 && (micros() - start) >= 1000) {
				ms -= 10;
				start += 1;
		}
	}
}
#undef i2cEndTransmission
#define i2cEndTransmission  sim_i2cEndTransmission
uint8_t sim_i2cEndTransmission(){
	return 0;
}

#undef endTransmission(stopit)
#define endTransmission(stopit) sim_endTransmission(stopit)
uint8_t sim_endTransmission(uint8_t stopit){
	return (uint8_t)0;
}
//#define endTransmission() sim_endTransmission()
//uint8_t sim_endTransmission(){
	//return (uint8_t)0;
//}
//#define i2cEndTransmission Wire.endTransmission

#endif


#endif //__SIMULATEDEBUG_H__
