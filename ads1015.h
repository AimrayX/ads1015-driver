/**
 **********************************************************************************
 * @file   ads1015.h
 * @author Hall.T (https://github.com/AimrayX)
 * @brief  ads1015 driver
 **********************************************************************************
 *
 * Copyright (c) 2025 AimrayX
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************************************
 */

#ifndef ADS1015_H
#define ADS1015_H

typedef enum ads1015_conv_status_e{
    ADS1015_CONV_NOT_BUSY = 0,
    ADS1015_CONV_BUSY     = 1,

} ads1015_conv_status_t;

typedef enum ads1015_conv_command_e{
    ADS1015_CONV_NO_OP = 0,
    ADS1015_CONV_START = 1,

} ads1015_conv_command_t;

typedef enum ads1015_mux_e{
    ADS1015_MUX_AIN0_AIN1    = 0,
    ADS1015_MUX_AIN0_AIN3    = 1,
    ADS1015_MUX_AIN1_AIN3    = 2,
    ADS1015_MUX_AIN2_AIN3    = 3,
    ADS1015_MUX_AIN0_AIN_GND = 4,
    ADS1015_MUX_AIN1_AIN_GND = 5,
    ADS1015_MUX_AIN2_AIN_GND = 6,
    ADS1015_MUX_AIN3_AIN_GND = 7,

} ads1015_mux_t;

typedef enum ads1015_pga_e{
    ADS1015_PGA_6_144 = 0,
    ADS1015_PGA_4_096 = 1,
    ADS1015_PGA_2_048 = 2,
    ADS1015_PGA_1_024 = 3,
    ADS1015_PGA_0_512 = 4,
    ADS1015_PGA_0_256 = 5,
    ADS1015_PGA_0_256 = 6,
    ADS1015_PGA_0_256 = 7,

} ads1015_pga_t;

typedef enum ads1015_mode_e{
    ADS1015_MODE_CONTINUOUS  = 0,
    ADS1015_MODE_SINGLE_SHOT = 1,

} ads1015_mode_t;

typedef enum ads1015_data_rate_e{
    ADS1015_DATA_RATE_128SPS  = 0,
    ADS1015_DATA_RATE_250SPS  = 1,
    ADS1015_DATA_RATE_490SPS  = 2,
    ADS1015_DATA_RATE_920SPS  = 3,
    ADS1015_DATA_RATE_1600SPS = 4,
    ADS1015_DATA_RATE_2400SPS = 5,
    ADS1015_DATA_RATE_3300SPS = 6,
    ADS1015_DATA_RATE_3300SPS = 7,

} ads1015_data_rate_t;

typedef enum ads1015_comp_mode_e{
    ADS1015_COMP_MODE_TRADITIONAL = 0,
    ADS1015_COMP_MODE_WINDOW      = 1,

} ads1015_comp_mode_t;

typedef enum ads1015_comp_pol_e{
    ADS1015_COMP_POL_LOW  = 0,
    ADS1015_COMP_POL_HIGH = 1,

} ads1015_comp_pol_t;

typedef enum ads1015_comp_lat_e{
    ADS1015_COMP_POL_LOW  = 0,
    ADS1015_COMP_POL_HIGH = 1,

} ads1015_comp_lat_t;

#endif