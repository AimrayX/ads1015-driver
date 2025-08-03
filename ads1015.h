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

#include <stdint.h>

// Default I2C addresses
#define ADS1015_I2C_ADDR_GND 0x48
#define ADS1015_I2C_ADDR_VDD 0x49
#define ADS1015_I2C_ADDR_SDA 0x4A
#define ADS1015_I2C_ADDR_SCL 0x4B

// I2C registers
#define ADS1015_REG_CONVERSION  0x00
#define ADS1015_REG_CONFIG      0x01
#define ADS1015_REG_LO_THRESH   0x02
#define ADS1015_REG_HI_THRESH   0x03


// Setting starting point in register
#define ADS1015_CONV_SHIFT      15
#define ADS1015_MUX_SHIFT       12
#define ADS1015_PGA_SHIFT        9
#define ADS1015_MODE_SHIFT       8
#define ADS1015_DATA_RATE_SHIFT  5
#define ADS1015_COMP_MODE_SHIFT  4
#define ADS1015_COMP_POL_SHIFT   3
#define ADS1015_COMP_LAT_SHIFT   2
#define ADS1015_COMP_QUE_SHIFT   0

// Setting mask in register
#define ADS1015_CONV_MASK      (0x1 << ADS1015_CONV_SHIFT)
#define ADS1015_MUX_MASK       (0x7 << ADS1015_MUX_SHIFT)
#define ADS1015_PGA_MASK       (0x7 << ADS1015_PGA_SHIFT )
#define ADS1015_MODE_MASK      (0x1 << ADS1015_MODE_SHIFT )
#define ADS1015_DATA_RATE_MASK (0x7 << ADS1015_DATA_RATE_SHIFT)
#define ADS1015_COMP_MODE_MASK (0x1 << ADS1015_COMP_MODE_SHIFT)
#define ADS1015_COMP_POL_MASK  (0x1 << ADS1015_COMP_POL_SHIFT)
#define ADS1015_COMP_LAT_MASK  (0x1 << ADS1015_COMP_LAT_SHIFT)
#define ADS1015_COMP_QUE_MASK  (0x3 << ADS1015_COMP_QUE_SHIFT)

typedef enum ads1015_result_e {
    ADS1015_OK   = 0,
    ADS1015_FAIL = 1,
} ads1015_result_t;

typedef enum ads1015_conv_status_e {
    ADS1015_CONV_NOT_BUSY = 0,
    ADS1015_CONV_BUSY     = 1,

} ads1015_conv_status_t;

typedef enum ads1015_conv_command_e {
    ADS1015_CONV_NO_OP = 0,
    ADS1015_CONV_START = 1,

} ads1015_conv_command_t;

typedef enum ads1015_mux_e {
    ADS1015_MUX_AIN0_AIN1    = 0,
    ADS1015_MUX_AIN0_AIN3    = 1,
    ADS1015_MUX_AIN1_AIN3    = 2,
    ADS1015_MUX_AIN2_AIN3    = 3,
    ADS1015_MUX_AIN0_AIN_GND = 4,
    ADS1015_MUX_AIN1_AIN_GND = 5,
    ADS1015_MUX_AIN2_AIN_GND = 6,
    ADS1015_MUX_AIN3_AIN_GND = 7,

} ads1015_mux_t;

typedef enum ads1015_pga_e {
    ADS1015_PGA_6_144 = 0,
    ADS1015_PGA_4_096 = 1,
    ADS1015_PGA_2_048 = 2,
    ADS1015_PGA_1_024 = 3,
    ADS1015_PGA_0_512 = 4,
    ADS1015_PGA_0_256 = 5,
    ADS1015_PGA_0_256 = 6,
    ADS1015_PGA_0_256 = 7,

} ads1015_pga_t;

typedef enum ads1015_mode_e {
    ADS1015_MODE_CONTINUOUS  = 0,
    ADS1015_MODE_SINGLE_SHOT = 1,

} ads1015_mode_t;

typedef enum ads1015_data_rate_e {
    ADS1015_DATA_RATE_128SPS  = 0,
    ADS1015_DATA_RATE_250SPS  = 1,
    ADS1015_DATA_RATE_490SPS  = 2,
    ADS1015_DATA_RATE_920SPS  = 3,
    ADS1015_DATA_RATE_1600SPS = 4,
    ADS1015_DATA_RATE_2400SPS = 5,
    ADS1015_DATA_RATE_3300SPS = 6,
    ADS1015_DATA_RATE_3300SPS = 7,

} ads1015_data_rate_t;

typedef enum ads1015_comp_mode_e {
    ADS1015_COMP_MODE_TRADITIONAL = 0,
    ADS1015_COMP_MODE_WINDOW      = 1,

} ads1015_comp_mode_t;

typedef enum ads1015_comp_pol_e {
    ADS1015_COMP_POL_LOW  = 0,
    ADS1015_COMP_POL_HIGH = 1,

} ads1015_comp_pol_t;

typedef enum ads1015_comp_lat_e {
    ADS1015_COMP_LAT_NONLATCHING = 0,
    ADS1015_COMP_LAT_LATCHING    = 1,

} ads1015_comp_lat_t;

typedef enum ads1015_comp_que_e {
    ADS1015_COMP_QUE_AFTER_1 = 0,
    ADS1015_COMP_QUE_AFTER_2 = 1,
    ADS1015_COMP_QUE_AFTER_4 = 2,
    ADS1015_COMP_QUE_DISABLE = 3,

} ads1015_comp_que_t;

/**
 * @brief  Sample
 */
typedef struct ads1015_sample_s {
    int16_t raw;
    float voltage;

} ads1015_sample_t;

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 */
typedef struct ads1015_handler_s {
    ads1015_mux_t mux;
    ads1015_pga_t pga;
    ads1015_mode_t mode;
    ads1015_data_rate_t data_rate;
    ads1015_comp_mode_t comp_mode;
    ads1015_comp_pol_t comp_pol;
    ads1015_comp_lat_t comp_lat;
    ads1015_comp_que_t comp_que;

    uint8_t i2c_addr;
    int fd;

    ads1015_init_deinit_t platform_init;
    ads1015_init_deinit_t platform_deinit;
    ads1015_send_receive_t send;
    ads1015_send_receive_t receive;

    
} ads1015_handler_t;

/**
 * @brief  Function type for Initialize/Deinitialize the platform dependent layer.
 * @retval 
 *          -  0: The operation was successful.
 * @retval
 *          - -1: The operation failed. 
 */
typedef int8_t (*ads1015_init_deinit_t)(void);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval 
 *          -  0: The operation was successful.
 * @retval
 *          - -1: The operation failed. 
 */
typedef int8_t (*ads1015_send_receive_t)(uint8_t address, uint8_t *data, uint8_t len, int fd);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_init(ads1015_handler_t *handler, uint8_t address, int fd);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_start_single_meas(ads1015_handler_t *handler);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_check_if_data_available(ads1015_handler_t *handler);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_read_sample(ads1015_handler_t *handler, ads1015_sample_t *sample);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_mux(ads1015_handler_t *handler, ads1015_mux_t mux);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_pga(ads1015_handler_t *handler, ads1015_pga_t pga);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_mode(ads1015_handler_t *handler, ads1015_mode_t mode);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_data_rate(ads1015_handler_t *handler, ads1015_data_rate_t rate);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_comp_mode(ads1015_handler_t *handler, ads1015_comp_mode_t comp_mode);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_comp_pol(ads1015_handler_t *handler, ads1015_comp_pol_t comp_pol);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_comp_lat(ads1015_handler_t *handler, ads1015_comp_lat_t comp_lat);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_comp_que(ads1015_handler_t *handler, ads1015_comp_que_t comp_que);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_i2c_address(ads1015_handler_t *handler, uint8_t i2c_address);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_high_thresh(ads1015_handler_t *handler, uint16_t thresh);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_set_low_thresh(ads1015_handler_t *handler, uint16_t thresh);

/**
 * @brief  Start single measurement
 * @note   This command will start a single measurement
 *         
 * @param  handler: Pointer to handler
 * @retval ads1015_result_t  
 * @retval
 *                           - ADS1015_OK: Operation was successful 
 * @retval
 *                           - ADS1015_FAIL: Operation was unsuccessful
 */
ads1015_result_t ads1015_general_call_reset(ads1015_handler_t *handler);

#endif