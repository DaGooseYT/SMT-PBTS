/****************************************************************************
 * Copyright (C) 2023 DaGoose
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

/* THIS IS NOT THE FULL FIRMWARE CODE! THIS CODE ONLY DEMONSTRATES USAGE FOR AIC3254 IN THIS APPLICATION */

#include <stream.h>
#include <sink.h>
#include <source.h>
#include <string.h>
#include <panic.h>
#include <message.h>
#include <stdlib.h>
#include <i2c.h>

static void I2cWrite8bitDeviceRegister(uint8 deviceReg, uint8 data);
static void Aic3254WriteData(void);
static void Aic3254Shutdown(void);

void I2cWrite8bitDeviceRegister(uint8 deviceReg, uint8 data) {
    uint8 i2c_data[2];
    i2c_data[0] = deviceReg;
    i2c_data[1] = data;

    /* 0011000 slave address */
    if (I2cReset()) {
        PanicZero(I2cTransfer(0x30, i2c_data, 2, NULL, 0));
    }
}

void Aic3254Shutdown(void) {
    /*		    --------------------------------------------------------------- page 0 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x00);
    /*			# reg[  0][  1] = 0x01	; shutdown the device through software reset                  */
    I2cWrite8bitDeviceRegister(0x01, 0x01);
}

/* AIC3254 config */
void Aic3254WriteData(void) {
    /*			--------------------------------------------------------------- page 1 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x01);
    /*			# reg[  1][  2] = 0xa9	; power up AVDD LDO                                           */
    I2cWrite8bitDeviceRegister(0x02, 0xA9);
    /*			# reg[  1][  1] = 0x08	; disable weak AVDD to DVDD connection                        */
    I2cWrite8bitDeviceRegister(0x01, 0x08);
    /*			# reg[  1][  2] = 0xa1	; enable Master Analog Power Control, AVDD LDO Powered        */
    I2cWrite8bitDeviceRegister(0x02, 0xA1);
    /*			# reg[  1][ 71] = 0x32	; set the input power-up time to 3.1ms                        */
    I2cWrite8bitDeviceRegister(0x47, 0x32);
    /*			# reg[  1][123] = 0x01	; set REF charging time to 40ms (automatic)                   */
    I2cWrite8bitDeviceRegister(0x7B, 0x01);
    /*			--------------------------------------------------------------- page 44 is selected   */
    I2cWrite8bitDeviceRegister(0x00, 0x2C);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 0                                         */
    I2cWrite8bitDeviceRegister(0x08, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x09, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0A, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 1                                         */
    I2cWrite8bitDeviceRegister(0x0C, 0xFF);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x0D, 0xFF);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0E, 0xFF);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 2                                         */
    I2cWrite8bitDeviceRegister(0x10, 0x80);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x11, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x12, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x13, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 3                                         */
    I2cWrite8bitDeviceRegister(0x14, 0x40);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x15, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x16, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x17, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 4                                         */
    I2cWrite8bitDeviceRegister(0x18, 0x7F);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x19, 0xFF);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1A, 0xFF);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 5                                         */
    I2cWrite8bitDeviceRegister(0x1C, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x1D, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1E, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 15                                        */
    I2cWrite8bitDeviceRegister(0x44, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x45, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x46, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x47, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 16                                        */
    I2cWrite8bitDeviceRegister(0x48, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x49, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x4A, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x4B, 0x00);
    /*			--------------------------------------------------------------- page 62 is selected   */
    I2cWrite8bitDeviceRegister(0x00, 0x3E);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 256                                       */
    I2cWrite8bitDeviceRegister(0x08, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x09, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0A, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 257                                       */
    I2cWrite8bitDeviceRegister(0x0C, 0xFF);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x0D, 0xFF);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0E, 0xFF);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 258                                       */
    I2cWrite8bitDeviceRegister(0x10, 0x80);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x11, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x12, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x13, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 259                                       */
    I2cWrite8bitDeviceRegister(0x14, 0x40);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x15, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x16, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x17, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 260                                       */
    I2cWrite8bitDeviceRegister(0x18, 0x7F);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x19, 0xFF);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1A, 0xFF);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 261                                       */
    I2cWrite8bitDeviceRegister(0x1C, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x1D, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1E, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 271                                       */
    I2cWrite8bitDeviceRegister(0x44, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x45, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x46, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x47, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC COEFF No. 272                                       */
    I2cWrite8bitDeviceRegister(0x48, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x49, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x4A, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x4B, 0x00);
    /*			--------------------------------------------------------------- page 152 is selected  */
    I2cWrite8bitDeviceRegister(0x00, 0x98);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 0                                          */
    I2cWrite8bitDeviceRegister(0x08, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x09, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0A, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 1                                          */
    I2cWrite8bitDeviceRegister(0x0C, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x0D, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0E, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 2                                          */
    I2cWrite8bitDeviceRegister(0x10, 0x08);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x11, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x12, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x13, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 3                                          */
    I2cWrite8bitDeviceRegister(0x14, 0x08);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x15, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x16, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x17, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 4                                          */
    I2cWrite8bitDeviceRegister(0x18, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x19, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1A, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 5                                          */
    I2cWrite8bitDeviceRegister(0x1C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x1D, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1E, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 6                                          */
    I2cWrite8bitDeviceRegister(0x20, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x21, 0x17);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x22, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x23, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 7                                          */
    I2cWrite8bitDeviceRegister(0x24, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x25, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x26, 0x02);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x27, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 8                                          */
    I2cWrite8bitDeviceRegister(0x28, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x29, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x2A, 0x03);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x2B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 9                                          */
    I2cWrite8bitDeviceRegister(0x2C, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x2D, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x2E, 0x04);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x2F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 10                                         */
    I2cWrite8bitDeviceRegister(0x30, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x31, 0x43);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x32, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x33, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 11                                         */
    I2cWrite8bitDeviceRegister(0x34, 0x38);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x35, 0x07);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x36, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x37, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 12                                         */
    I2cWrite8bitDeviceRegister(0x38, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x39, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x3A, 0x05);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x3B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 13                                         */
    I2cWrite8bitDeviceRegister(0x3C, 0x48);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x3D, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x3E, 0x0F);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x3F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 14                                         */
    I2cWrite8bitDeviceRegister(0x40, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x41, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x42, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x43, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 15                                         */
    I2cWrite8bitDeviceRegister(0x44, 0x18);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x45, 0xF0);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x46, 0x02);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x47, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 16                                         */
    I2cWrite8bitDeviceRegister(0x48, 0x90);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x49, 0x7C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x4A, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x4B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 17                                         */
    I2cWrite8bitDeviceRegister(0x4C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x4D, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x4E, 0x02);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x4F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 18                                         */
    I2cWrite8bitDeviceRegister(0x50, 0x90);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x51, 0xFC);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x52, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x53, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 19                                         */
    I2cWrite8bitDeviceRegister(0x54, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x55, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x56, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x57, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 20                                         */
    I2cWrite8bitDeviceRegister(0x58, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x59, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x5A, 0x06);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x5B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 21                                         */
    I2cWrite8bitDeviceRegister(0x5C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x5D, 0x08);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x5E, 0x06);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x5F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 22                                         */
    I2cWrite8bitDeviceRegister(0x60, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x61, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x62, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x63, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 23                                         */
    I2cWrite8bitDeviceRegister(0x64, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x65, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x66, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x67, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 24                                         */
    I2cWrite8bitDeviceRegister(0x68, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x69, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x6A, 0x07);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x6B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 25                                         */
    I2cWrite8bitDeviceRegister(0x6C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x6D, 0x07);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x6E, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x6F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 26                                         */
    I2cWrite8bitDeviceRegister(0x70, 0x80);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x71, 0x3F);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x72, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x73, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 27                                         */
    I2cWrite8bitDeviceRegister(0x74, 0x38);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x75, 0x07);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x76, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x77, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 28                                         */     
    I2cWrite8bitDeviceRegister(0x78, 0x80);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x79, 0x3F);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x7A, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x7B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 29                                         */
    I2cWrite8bitDeviceRegister(0x7C, 0x88);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x7D, 0x08);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x7E, 0x05);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x7F, 0x00);
    /*			--------------------------------------------------------------- page 153 is selected  */
    I2cWrite8bitDeviceRegister(0x00, 0x99);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 30                                         */
    I2cWrite8bitDeviceRegister(0x08, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x09, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0A, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 31                                         */
    I2cWrite8bitDeviceRegister(0x0C, 0x88);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x0D, 0x08);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0E, 0x08);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 32                                         */
    I2cWrite8bitDeviceRegister(0x10, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x11, 0x17);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x12, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x13, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 33                                         */
    I2cWrite8bitDeviceRegister(0x14, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x15, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x16, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x17, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 34                                         */
    I2cWrite8bitDeviceRegister(0x18, 0x88);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x19, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1A, 0x08);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 35                                         */
    I2cWrite8bitDeviceRegister(0x1C, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x1D, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1E, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 36                                         */
    I2cWrite8bitDeviceRegister(0x20, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x21, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x22, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x23, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 37                                         */
    I2cWrite8bitDeviceRegister(0x24, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x25, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x26, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x27, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 38                                         */
    I2cWrite8bitDeviceRegister(0x28, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x29, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x2A, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x2B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 39                                         */
    I2cWrite8bitDeviceRegister(0x2C, 0x88);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x2D, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x2E, 0x03);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x2F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 40                                         */
    I2cWrite8bitDeviceRegister(0x30, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x31, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x32, 0x07);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x33, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 41                                         */
    I2cWrite8bitDeviceRegister(0x34, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x35, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x36, 0x07);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x37, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 42                                         */
    I2cWrite8bitDeviceRegister(0x38, 0x88);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x39, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x3A, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x3B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 43                                         */
    I2cWrite8bitDeviceRegister(0x3C, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x3D, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x3E, 0x08);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x3F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 44                                         */
    I2cWrite8bitDeviceRegister(0x40, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x41, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x42, 0x09);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x43, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 45                                         */
    I2cWrite8bitDeviceRegister(0x44, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x45, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x46, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x47, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 46                                         */
    I2cWrite8bitDeviceRegister(0x48, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x49, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x4A, 0x01);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x4B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 47                                         */
    I2cWrite8bitDeviceRegister(0x4C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x4D, 0x17);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x4E, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x4F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 48                                         */
    I2cWrite8bitDeviceRegister(0x50, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x51, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x52, 0x0A);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x53, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 49                                         */
    I2cWrite8bitDeviceRegister(0x54, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x55, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x56, 0x0B);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x57, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 50                                         */  
    I2cWrite8bitDeviceRegister(0x58, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x59, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x5A, 0x0C);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x5B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 51                                         */
    I2cWrite8bitDeviceRegister(0x5C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x5D, 0x03);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x5E, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x5F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 52                                         */
    I2cWrite8bitDeviceRegister(0x60, 0x38);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x61, 0x07);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x62, 0xFB);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x63, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 53                                         */
    I2cWrite8bitDeviceRegister(0x64, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x65, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x66, 0x0D);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x67, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 54                                         */
    I2cWrite8bitDeviceRegister(0x68, 0x48);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x69, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x6A, 0x0f);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x6B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 55                                         */
    I2cWrite8bitDeviceRegister(0x6C, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x6D, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x6E, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x6F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 56                                         */
    I2cWrite8bitDeviceRegister(0x70, 0x18);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x71, 0xF0);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x72, 0x02);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x73, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 57                                         */
    I2cWrite8bitDeviceRegister(0x74, 0x90);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x75, 0x7C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x76, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x77, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 58                                         */
    I2cWrite8bitDeviceRegister(0x78, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x79, 0x0C);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x7A, 0x0A);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x7B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 59                                         */
    I2cWrite8bitDeviceRegister(0x7C, 0x90);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x7D, 0xFC);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x7E, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x7F, 0x00);
    /*			--------------------------------------------------------------- page 154 is selected  */
    I2cWrite8bitDeviceRegister(0x00, 0x9A);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 60                                         */
    I2cWrite8bitDeviceRegister(0x08, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x09, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0A, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 61                                         */
    I2cWrite8bitDeviceRegister(0x0C, 0x20);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x0D, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x0E, 0x0E);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x0F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 62                                         */
    I2cWrite8bitDeviceRegister(0x10, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x11, 0x10);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x12, 0x0E);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x13, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 63                                         */
    I2cWrite8bitDeviceRegister(0x14, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x15, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x16, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x17, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 64                                         */
    I2cWrite8bitDeviceRegister(0x18, 0x18);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x19, 0x04);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1A, 0x02);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1B, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 65                                         */
    I2cWrite8bitDeviceRegister(0x1C, 0x30);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x1D, 0x10);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x1E, 0x08);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x1F, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 66                                         */
    I2cWrite8bitDeviceRegister(0x20, 0x00);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x21, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x22, 0x00);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x23, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 67                                         */
    I2cWrite8bitDeviceRegister(0x24, 0x18);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x25, 0x00);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x26, 0x02);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x27, 0x00);
    /*			 (Bit 31-24) ------------ MSB DAC INST No. 68                                         */
    I2cWrite8bitDeviceRegister(0x28, 0x88);
    /*			 (Bit 23-16)                                                                          */
    I2cWrite8bitDeviceRegister(0x29, 0x03);
    /*			 (Bit 15-8)                                                                           */
    I2cWrite8bitDeviceRegister(0x2A, 0xFF);
    /*			 (Bit 7-0)                                                                            */
    I2cWrite8bitDeviceRegister(0x2B, 0x00);
    /*			--------------------------------------------------------------- page 0 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x00);
    /*			# reg[  0][ 60] = 0x00	; use miniDSP_D for signal processing                         */
    I2cWrite8bitDeviceRegister(0x3C, 0x00);
    /*			# reg[  0][ 17] = 0x02	; 2x interpolation                                            */
    I2cWrite8bitDeviceRegister(0x11, 0x02);
    /*			# reg[  0][ 23] = 0x01	; 1x decimation                                               */
    I2cWrite8bitDeviceRegister(0x17, 0x01);
    I2cWrite8bitDeviceRegister(0x0F, 0x01);
    I2cWrite8bitDeviceRegister(0x10, 0x00);
    /*			--------------------------------------------------------------- page 44 is selected   */
    I2cWrite8bitDeviceRegister(0x00, 0x2C);
    /*			# reg[ 44][  1] = 0x04	; adaptive mode for DAC                                       */
    I2cWrite8bitDeviceRegister(0x01, 0x04);
    /*			--------------------------------------------------------------- page 0 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x00);
    /*			# reg[  0][  5] = 0x91	; P=1, R=1, J=8                                               */
    I2cWrite8bitDeviceRegister(0x05, 0x91);
    /*			# reg[  0][  6] = 0x08	; P=1, R=1, J=8                                               */
    I2cWrite8bitDeviceRegister(0x06, 0x08);
    /*			# reg[  0][  7] = 0x00	; D=0000 (MSB)                                                */
    I2cWrite8bitDeviceRegister(0x07, 0x00);
    /*			# reg[  0][  8] = 0x00	; D=0000 (LSB)                                                */
    I2cWrite8bitDeviceRegister(0x08, 0x00);
    /*			# reg[  0][  4] = 0x07	; PLL_clkin = BCLK, codec_clkin = PLL_CLK, PLL on             */
    I2cWrite8bitDeviceRegister(0x04, 0x07);
    /*			# reg[  0][ 12] = 0x88	; MDAC = 8, divider powered on                                */
    I2cWrite8bitDeviceRegister(0x0C, 0x88);
    /*			# reg[  0][ 13] = 0x00	; DOSR = 128 (MSB)                                            */
    I2cWrite8bitDeviceRegister(0x0D, 0x00);
    /*			# reg[  0][ 14] = 0x80	; DOSR = 128 (LSB)                                            */
    I2cWrite8bitDeviceRegister(0x0E, 0x80);
    /*			# reg[  0][ 20] = 0x80	; AOSR = 128                                                  */
    I2cWrite8bitDeviceRegister(0x14, 0x80);
    /*			# reg[  0][ 11] = 0x82	; NDAC = 2, divider powered on                                */
    I2cWrite8bitDeviceRegister(0x0B, 0x82);
    /*			--------------------------------------------------------------- page 1 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x01);
    /*			# reg[  1][ 20] = 0x25	; de-pop: 5 time constants, 6k resistance                     */
    I2cWrite8bitDeviceRegister(0x14, 0x25);
    /*			# reg[  1][ 14] = 0x08	; route LDAC to LOL                                           */
    I2cWrite8bitDeviceRegister(0x0E, 0x08);
    /*			# reg[  1][ 15] = 0x08	; route LDAC to LOR                                           */
    I2cWrite8bitDeviceRegister(0x0F, 0x08);
    /*			--------------------------------------------------------------- page 0 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x00);
    /*			# reg[  0][ 63] = 0xd4	; power up LDAC/RDAC w/ soft stepping                         */
    I2cWrite8bitDeviceRegister(0x3F, 0xD4);
    /*			--------------------------------------------------------------- page 1 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x01);
    /*			# reg[  1][ 18] = 0x17	; unmute LOL driver, 23dB Gain                                */
    I2cWrite8bitDeviceRegister(0x12, 0x17);
    /*			# reg[  1][ 19] = 0x16	; unmute LOR driver, 22dB Gain                                */
    I2cWrite8bitDeviceRegister(0x13, 0x16);
    /*			# reg[  1][  9] = 0x3c	; power up LOL/LOR drivers                                    */
    I2cWrite8bitDeviceRegister(0x09, 0x3C);
    /*			--------------------------------------------------------------- page 0 is selected    */
    I2cWrite8bitDeviceRegister(0x00, 0x00);
    /*			# reg[  0][ 64] = 0x00	; unmute LDAC/RDAC                                            */
    I2cWrite8bitDeviceRegister(0x40, 0x00);
}

static bool sinkPowerProcessEventPower(const MessageId EventPower) {
    bool indicate_event = TRUE;

    if(peerProcessEvent(EventPower)) {
        indicate_event = FALSE;
    }
    else {
        switch(EventPower) {
            case EventUsrPowerOn:
            case EventSysPowerOnPanic:
                MAIN_DEBUG(("HS: Power On\n" ));
                
                if (stateManagerGetState() == deviceLimbo) {
                    displaySetState(TRUE);
                    displayShowText(DISPLAYSTR_HELLO, strlen(DISPLAYSTR_HELLO), DISPLAY_TEXT_SCROLL_SCROLL, 1000, 2000, FALSE, 10, SINK_TEXT_TYPE_DEVICE_STATE);
                    displayUpdateVolume((VOLUME_NUM_VOICE_STEPS * sinkHfpDataGetDefaultVolume()) / sinkVolumeGetNumberOfVolumeSteps(audio_output_group_main));
                    /* update battery display */
                    displayUpdateBatteryLevel(powerManagerIsChargerConnected());
                }

                sinkAncHandlePowerOn();

                stateManagerPowerOn();
                /* indicate now "Power On" voice prompt before audio plugins kick in, derisking playing audio with low volume.*/
                IndicateEvent(EventPower);
                indicate_event = FALSE;

                configManagerReadSessionData();

                if (!isDUTPIOActive()) {
                    sinkRouteAudio();
                }

                sinkFmSetFmRxOn(FALSE);
                sinkDataSetPowerUpNoConnectionFlag(TRUE);

                if (powerManagerIsVthmCritical()) {
                    MessageSend(&theSink.task, EventUsrPowerOff, 0);
                }

                powerManagerReadVbat(battery_level_initial_reading);

                if (sinkDataGetEncryptionRefreshTimeout() != 0) {
                    MessageSendLater(&theSink.task, EventSysRefreshEncryption, 0, D_MIN(sinkDataGetEncryptionRefreshTimeout()));
                }

                if (sinkDataCheckDisablePowerOffAfterPowerOn()) {
                    sinkDataSetPoweroffEnabled(FALSE);
                    MAIN_DEBUG(("DIS[%x]\n", sinkDataGetDisablePoweroffAfterPoweronTimeout()));
                    MessageSendLater (&theSink.task, EventSysEnablePowerOff, 0, D_SEC(sinkDataGetDisablePoweroffAfterPoweronTimeout()));
                }
                else {
                    sinkDataSetPoweroffEnabled(TRUE);
                }

                #ifdef ENABLE_SUBWOOFER
                /* check to see if there is a paired subwoofer device, if not kick off an inquiry scan */
                MessageSend(&theSink.task, EventSysSubwooferCheckPairing, 0);
                #endif

                if (sinkDataDefragCheckTimout()) {
                    MessageSendLater(&theSink.task, EventSysCheckDefrag, 0, D_SEC(sinkDataDefragCheckTimout()));
                }

                /* generate event to drive EQ indicator */
                sinkAudioEQOperatingStateIndication();

                MessageSend(&theSink.task, EventSysUpdateDevicesConnectedStatus, NULL);
            
                /* power on BLE */
                sinkBlePowerOnEvent();

                sinkBroadcastAudioHandleUserPowerOn();
                
                PioDriveUserPio(PioGetUserPioState());
                
                /* write data AIC3254 */
                Aic3254WriteData();
                
                break;

            case EventSysPeerGeneratedPowerOff:
            case EventUsrPowerOff:
                /* reset the silence detected flag in case if the audio silence detected (i.e. set to 1) and before the timer expiry if user pressed the EventUsrPowerOff event. */
                if (sinkAudioIsSilenceDetected()) {
                    sinkAudioSetSilence(FALSE);
                }

                MAIN_DEBUG(("HS: PowerOff - En[%c]\n" , TRUE_OR_FALSE(sinkDataIsPowerOffEnabled())));

                /* don't indicate event if already in limbo state */
                if (stateManagerGetState() == deviceLimbo) {
                    indicate_event = FALSE;
                }

                /* only power off if timer has expired or battery is low and the charger isn't connected or temperature high */
                if (sinkDataIsPowerOffEnabled() || ((!powerManagerIsChargerConnected() || sinkDataAllowAutomaticPowerOffWhenCharging()) && powerManagerIsVbatCritical()) || powerManagerIsVthmCritical()) {
                    /* store current volume levels for non bluetooth volumes */
                    configManagerWriteSessionData();

                    configManagerWriteDspData();
                    
                    audioSwitchToAudioSource(audio_source_none);

                    stateManagerEnterLimboState(limboShutDown);
                    AuthResetConfirmationFlags();

                    sinkBroadcastAudioPowerOff();

                    VolumeUpdateMuteStatusAllOutputs(FALSE);
                    VolumeSetHfpMicrophoneGain(hfp_invalid_link, MICROPHONE_MUTE_OFF);

                    sinkClearQueueudEvent();

                    sinkStopAutoPowerOffTimer();

                    if (sinkDataGetEncryptionRefreshTimeout() != 0) {
                        MessageCancelAll(&theSink.task, EventSysRefreshEncryption);
                    }

                    MessageCancelAll(&theSink.task, EventSysCheckDefrag);
                    MessageCancelAll(&theSink.task, EventSysDefrag);

                    MessageCancelAll(&theSink.task, EventSysPairingFail);
                    #ifdef ENABLE_PEER
                    MessageCancelAll(&theSink.task, EventSysA2DPPeerLinkLossTimeout);
                    setA2dpPeerLinkLossReconnect(FALSE);
                    #endif

                    #ifdef ENABLE_AVRCP
                    /* cancel any queued ff or rw requests */
                    MessageCancelAll(&theSink.task, EventUsrAvrcpFastForwardPress);
                    MessageCancelAll(&theSink.task, EventUsrAvrcpRewindPress);
                    #endif
                    #ifdef ENABLE_SPEECH_RECOGNITION
                    /* if speech recognition is in tuning mode stop it */
                    if (speechRecognitionTuningIsActive()) {
                        speechRecognitionStop();
                        speechRecognitionSetTuningActive(FALSE);
                    }
                    #endif

                    if (sinkFmIsFmRxOn()) {
                        MessageSend(&theSink.task, EventUsrFmRxOff, 0);
                    }

                    /* keep the display on if charging */
                    if (powerManagerIsChargerConnected() && (stateManagerGetState() == deviceLimbo)) {
                        displaySetState(TRUE);
                        displayUpdateVolume(0);
                        displayUpdateBatteryLevel(TRUE);
                    }
                    else {
                        displaySetState(FALSE);
                    }

                    #ifdef ENABLE_GAIA
                    if (!gaia_get_remain_connected()) {
                        gaiaDisconnect();
                    }
                    #endif

					/* generate event to drive EQ indicator */
					sinkAudioEQOperatingStateIndication();

                    /* power off BLE if not in BA mode*/
                    sinkBlePowerOffEvent();
                    sinkAncHandlePowerOff();

                    /* cancel any on-going VA session */
                    SinkVaHandlePowerOff();

                    MessageSend(&theSink.task, EventSysUpdateDevicesConnectedStatus, NULL);

                }
                else {
                    indicate_event = FALSE ;
                }
                
                /* software reset (shutdown) for AIC3254 */
                Aic3254Shutdown();
        }
    }

    return indicate_event;
}

int main(void) {
    MAIN_DEBUG (("Main [%s]\n",__TIME__));

    /* certain chips require a HUB attach to enumerate as a USB device. */
    usbAttachToHub();

    /* initialise Sink Ahi */
    sinkAhiInit(&theSink.task);

    /* initialise memory required early */
    configManagerInitMemory();

    /* initialise device state */
    AuthResetConfirmationFlags();

    /* the internal regs must be latched on (smps and LDO)*/
    PioSetPowerPin(TRUE);

    switch (BootGetMode()) {
        #ifdef CVC_PRODTEST
        case BOOTMODE_CVC_PRODTEST:
            /* run the cvc prod test code and dont start the applicaiton */
            cvcProductionTestEnter();
        break;
        #endif
        case BOOTMODE_DFU:
            /* do nothing special for the DFU boot mode, this mode expects to have the appropriate host interface enabled. don't start the application */
            /* initializing only the system components required for flashing the led pattern in the DFU mode */

            configManagerInit(FALSE);
            LedManagerIndicateEvent(EventUsrEnterDFUMode);
        break;

        case BOOTMODE_DEFAULT:
        case BOOTMODE_CUSTOM:
        case BOOTMODE_USB_LOW_POWER:
        case BOOTMODE_ALT_FSTAB:
        default: {
            /* initialize global data for audio*/
            sinkAudioInit();
            sinkA2dpTtpLatencyInit();

            /* make sure the mute states are correctly set up */
            VolumeSetInitialMuteState();

            if (sinkAhiGetAppMode() == ahi_app_mode_configuration) {
                /* config mode - do not initialise the main sink app. */
                stateManagerEnterConfigMode();
                
                /* software reset (shutdown) for AIC3254 */
                Aic3254Shutdown();
            }
            else {
                /* configure Broadcast Audio mode based on last stored configuration */
                sinkBroadcastAudioConfigure();
                /* initialise the Connection lib */
                sinkConnectionInit();
            }
        }
        break;
    }

    /* initialise the Upgrade lib only if BA mode is not Active*/
    sinkUpgradeInit(&theSink.task);

    /* start protection mechanism for buffer defences */
    watchdogReset();

    /* start the message scheduler loop */
    MessageLoop();

    /* never get here... */
    return 0;
}
