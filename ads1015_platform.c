/**
 **********************************************************************************
 * @file   ads1015_platform.c
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

#include "ads1015_platform.h"

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <stdio.h>


int8_t platform_write(uint8_t address, int8_t *data, uint8_t len, int fd) {
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    int fd = open("/dev/i2c-1", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to open i2c bus\n", __FILE__, __LINE__);
        return -1;
    }

    messages[0].addr  = address;
    messages[0].flags = 0; // Write
    messages[0].len   = len;
    messages[0].buf   = data;

    packets.msgs  = messages;
    packets.nmsgs = 1;

    if (ioctl(fd, I2C_RDWR, &packets) < 0) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to read register\n", __FILE__, __LINE__);
        return -1;
    }

    return 0;
}

int8_t platform_read(uint8_t address, int8_t *data, uint8_t len, int fd) {
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr  = address;
    messages[0].flags = I2C_M_RD; // Read
    messages[0].len   = len;
    messages[0].buf   = data;

    packets.msgs  = messages;
    packets.nmsgs = 1;

    if (ioctl(fd, I2C_RDWR, &packets) < 0) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to read register\n", __FILE__, __LINE__);
        return -1;
    }

    return 0;
}

int8_t platform_init() {
    
}

int8_t platform_deinit() {
    
}

void ads1015_platform_init(ads1015_handler_t *handler) {
    handler->send = platform_write;
    handler->receive = platform_read;
    handler->platform_init = platform_init;
    handler->platform_deinit = platform_deinit;
}