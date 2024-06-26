// I2Cdev library collection - Main I2C device class header file
// Abstracts bit and byte I2C R/W functions into a convenient class
// 6/9/2012 by Jeff Rowberg <jeff@rowberg.net>
// 6/6/2015 by Andrey Voloshin <voloshin@think.in.ua>
//
// Changelog:
//      2015-06-06 - ported to STM32 HAL library from Arduino code

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2013 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef _I2CDEV_H_
#define _I2CDEV_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef I2CDEVLIB_WIRE_BUFFER_LENGTH
    #if defined(I2C_BUFFER_LENGTH)
        // Arduino ESP32 core Wire uses this
        #define I2CDEVLIB_WIRE_BUFFER_LENGTH I2C_BUFFER_LENGTH
    #elif defined(BUFFER_LENGTH)
        // Arduino AVR core Wire and many others use this
        #define I2CDEVLIB_WIRE_BUFFER_LENGTH BUFFER_LENGTH
    #elif defined(SERIAL_BUFFER_SIZE)
        // Arduino SAMD core Wire uses this
        #define I2CDEVLIB_WIRE_BUFFER_LENGTH SERIAL_BUFFER_SIZE
    #else
        // should be a safe fallback, though possibly inefficient
        #define I2CDEVLIB_WIRE_BUFFER_LENGTH 32
    #endif
#endif

// TODO: include depending on chip family
//#include "stm32f1xx_hal.h"
//#include "stm32f2xx_hal.h"
//#include "stm32f3xx_hal.h"
#include "stm32f4xx_hal.h"
#ifndef __cplusplus
typedef int bool;
#endif
#define true 1
#define false 0

#define boolean bool
#define F(x) x

class Arduino_Serial{
    public:
    void write(char ch);
    void print(const char* s);
    void println(const char* s = 0);
    void println(char s);
    void println(float dt,int sz);
    void println(double dt,int sz);
    void print(float dt,int sz);
    void print(double dt,int sz = 0);
    void print(int t);
    void print(char t);
};
extern Arduino_Serial Serial;
extern uint32_t ulHighFrequencyTimerTicks;
uint32_t micros(void);
void delayMicroseconds(int t);
void delay(int n);

// 1000ms default read timeout (modify with "I2Cdev::readTimeout = [ms];")
#define I2CDEV_DEFAULT_READ_TIMEOUT     1000
class I2Cdev{
    public:
static uint16_t readTimeout;
static void init(I2C_HandleTypeDef * hi2c);

static uint8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout,void* wireObj = 0);
static uint8_t readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout,void* wireObj = 0);

static uint16_t writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data,void* wireObj = 0);
static uint16_t writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data,void* wireObj = 0);
static uint16_t writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data,void* wireObj = 0);
static uint16_t writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data,void* wireObj = 0);
static uint16_t writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data,void* wireObj = 0);
static uint16_t writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data,void* wireObj = 0);
static uint16_t writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data,void* wireObj = 0);
static uint16_t writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data,void* wireObj = 0);
};
#endif /* _I2CDEV_H_ */
