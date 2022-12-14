// I2Cdev library collection - Main I2C device class
// Abstracts bit and byte I2C R/W functions into a convenient class
// EFM32 stub port by Nicolas Baldeck <nicolas@pioupiou.fr>
// Based on Arduino's I2Cdev by Jeff Rowberg <jeff@rowberg.net>
//
// Changelog:
//      2015-01-02 - Initial release


/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2015 Jeff Rowberg, Nicolas Baldeck

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

#ifndef _ESP_I2CDEV_H_
#define _ESP_I2CDEV_H_

#include <stdlib.h>
#include <stdio.h>

#include <driver/i2c.h>

#include "interfaces/if_I2C_driver.h"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
#define I2C_SDA_PORT gpioPortA
#define I2C_SDA_PIN 15
#define I2C_SDA_MODE gpioModeWiredAnd
#define I2C_SDA_DOUT 1

#define I2C_SCL_PORT gpioPortA
#define I2C_SCL_PIN 14
#define I2C_SCL_MODE gpioModeWiredAnd
#define I2C_SCL_DOUT 1

#define I2CDEV_DEFAULT_READ_TIMEOUT 1000

#define DATA_LENGTH 512                  /*!< Data buffer length  */


#define I2C_DEVICE_SCL_IO CONFIG_I2C_DEVICE_SCL               /*!< gpio number for i2c device clock */
#define I2C_DEVICE_SDA_IO CONFIG_I2C_DEVICE_SDA               /*!< gpio number for i2c device data */

#define I2C_DEVICE_TX_BUF_LEN (2 * DATA_LENGTH)              /*!< I2C device tx buffer size */
#define I2C_DEVICE_RX_BUF_LEN (2 * DATA_LENGTH)              /*!< I2C device rx buffer size */

#define I2C_HOST_SCL_IO CONFIG_I2C_HOST_SCL               /*!< gpio number for I2C master clock */
#define I2C_HOST_SDA_IO CONFIG_I2C_HOST_SDA               /*!< gpio number for I2C master data  */

#define I2C_HOST_FREQ_HZ CONFIG_I2C_HOST_FREQUENCY        /*!< I2C master clock frequency */
#define I2C_HOST_TX_BUF_DISABLE 1                           /*!< I2C master doesn't need buffer */
#define I2C_HOST_RX_BUF_DISABLE 1                           /*!< I2C master doesn't need buffer */

#define ESP_DEVICE_ADDR CONFIG_I2C_DEVICE_ADDRESS /*!< ESP32 device address, you can set any 7bit value */

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */

#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from device*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from device */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */


class esp_I2Cdev : public if_I2C_driver {
    public:
        esp_I2Cdev();

        uint8_t i2c_port = I2C_NUM_0;
        uint16_t readTimeout = I2CDEV_DEFAULT_READ_TIMEOUT;

        void initialize(uint8_t _i2c_port, bool host_mode);

        void enable(bool isEnabled);

        esp_err_t i2c_host_init();
        esp_err_t i2c_device_init();

        int8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout=I2CDEV_DEFAULT_READ_TIMEOUT);
        //TODO static int8_t readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout=I2Cdev::readTimeout);
        int8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout=I2CDEV_DEFAULT_READ_TIMEOUT);
        //TODO static int8_t readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout=I2Cdev::readTimeout);
        int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout=I2CDEV_DEFAULT_READ_TIMEOUT);
        int8_t readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout=I2CDEV_DEFAULT_READ_TIMEOUT);
        int8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout=I2CDEV_DEFAULT_READ_TIMEOUT);
        //TODO static int8_t readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout=I2Cdev::readTimeout);

        bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
        //TODO static bool writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data);
        bool writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
        //TODO static bool writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);
        bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
        bool writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);
        bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
        //TODO static bool writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);


    //private:
        void SelectRegister(uint8_t dev, uint8_t reg);
        //static I2C_TransferReturn_TypeDef transfer(I2C_TransferSeq_TypeDef *seq, uint16_t timeout=I2Cdev::readTimeout);
};

#endif /* _I2CDEV_H_ */
