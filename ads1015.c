/**
 **********************************************************************************
 * @file   ads1015.c
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


#include "ads1015.h"


static ads1015_result_t ads1015_write_to_register(ads1015_handler_t *handler, uint8_t reg, uint16_t data) {
    uint8_t buffer[3] = {0};

    buffer[0] = reg;
    buffer[1] = (uint8_t)(data >> 8);
    buffer[2] = (uint8_t)data;

    return handler->send(handler->i2c_addr, buffer, 3, handler->fd);

}

static ads1015_result_t ads1015_read_register(ads1015_handler_t *handler, uint8_t reg, uint16_t *data) {
    uint8_t buffer[2] = {0};
    int8_t ret_val = 0;
    
    ret_val = handler->send(handler->i2c_addr, &reg, 1, handler->fd);

    if (ret_val < 0)
    {
        return ret_val;
    }

    ret_val = handler->receive(handler->i2c_addr, buffer, 2, handler->fd);

    if (ret_val < 0)
    {
        return ret_val;
    }

    *data = (uint16_t)(buffer[0] << 8) | (uint16_t)buffer[1];

    return ADS1015_OK;

}

ads1015_result_t ads1015_init(ads1015_handler_t *handler, uint8_t address, int fd) {

    if (ads1015_set_i2c_address(handler, address) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    if (ads1015_set_fd(handler, fd) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    if (handler->platform_init) {
        if (handler->platform_init() != 0) {
            return ADS1015_FAIL;
        }
    }

    // Default config
    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, 0x8583) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->mux       = ADS1015_MUX_AIN0_AIN1;
    handler->pga       = ADS1015_PGA_2_048;
    handler->mode      = ADS1015_MODE_SINGLE_SHOT;
    handler->data_rate = ADS1015_DATA_RATE_1600SPS;
    handler->comp_que  = ADS1015_COMP_QUE_DISABLE;

    return ADS1015_OK;
}

ads1015_result_t ads1015_start_single_meas(ads1015_handler_t *handler) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_CONV_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (0x1 << ADS1015_CONV_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    return ADS1015_OK;
}


ads1015_result_t ads1015_check_if_data_available(ads1015_handler_t *handler) {
    uint16_t data = 0;
    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ADS1015_CONV_MASK;

    if (data == 0) {
        return ADS1015_FAIL;
    }

    return ADS1015_OK;
}


ads1015_result_t ads1015_read_sample(ads1015_handler_t *handler, ads1015_sample_t *sample) {
    for (int i = 0; i < 3; i++) {
        if (ads1015_check_if_data_available(handler) == ADS1015_OK) {
            if(ads1015_read_register(handler, ADS1015_REG_CONVERSION, (uint16_t *)&sample->raw) != ADS1015_OK) {
                return ADS1015_FAIL;
            }

            sample->raw = sample->raw >> 4;

            // If sample->raw is unsigned, do sign extension manually
            if (sample->raw & 0x800) {
                sample->raw |= 0xF000;
            }

            
            if (handler->pga == ADS1015_PGA_6_144) {
                sample->voltage = sample->raw * 0.003f;
            } else if(handler->pga == ADS1015_PGA_4_096) {
                sample->voltage = sample->raw * 0.002f;
            } else if(handler->pga == ADS1015_PGA_2_048) {
                sample->voltage = sample->raw * 0.001f;
            } else if(handler->pga == ADS1015_PGA_1_024) {
                sample->voltage = sample->raw * 0.0005f;
            } else if(handler->pga == ADS1015_PGA_0_512) {
                sample->voltage = sample->raw * 0.00025f;
            } else if(handler->pga == ADS1015_PGA_0_256) {
                sample->voltage = sample->raw * 0.000125f;
            }

            return ADS1015_OK;
        }
    }

    return ADS1015_FAIL;
}

ads1015_result_t ads1015_set_mux(ads1015_handler_t *handler, ads1015_mux_t mux) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_MUX_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (mux << ADS1015_MUX_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }
    
    handler->mux = mux;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_pga(ads1015_handler_t *handler, ads1015_pga_t pga) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_PGA_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (pga << ADS1015_PGA_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->pga = pga;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_mode(ads1015_handler_t *handler, ads1015_mode_t mode) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_MODE_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (mode << ADS1015_MODE_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->mode = mode;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_data_rate(ads1015_handler_t *handler, ads1015_data_rate_t rate) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_DATA_RATE_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (rate << ADS1015_DATA_RATE_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->data_rate = rate;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_comp_mode(ads1015_handler_t *handler, ads1015_comp_mode_t comp_mode) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_MODE_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_mode << ADS1015_COMP_MODE_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->comp_mode = comp_mode;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_comp_pol(ads1015_handler_t *handler, ads1015_comp_pol_t comp_pol) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_POL_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_pol << ADS1015_COMP_POL_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->comp_pol = comp_pol;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_comp_lat(ads1015_handler_t *handler, ads1015_comp_lat_t comp_lat) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_LAT_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_lat << ADS1015_COMP_LAT_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->comp_lat = comp_lat;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_comp_que(ads1015_handler_t *handler, ads1015_comp_que_t comp_que) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_QUE_MASK;

    if (ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_que << ADS1015_COMP_QUE_SHIFT) | data) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    handler->comp_que = comp_que;

    return ADS1015_OK;
}


ads1015_result_t ads1015_set_i2c_address(ads1015_handler_t *handler, uint8_t i2c_address) {
    if (i2c_address == 0)
    {
        return ADS1015_FAIL;
    }

    handler->i2c_addr = i2c_address;

    return ADS1015_OK;    
}

ads1015_result_t ads1015_set_fd(ads1015_handler_t *handler, int fd) {
    if (fd == 0)
    {
        return ADS1015_FAIL;
    }

    handler->fd = fd;

    return ADS1015_OK;    
}


ads1015_result_t ads1015_set_high_thresh(ads1015_handler_t *handler, uint16_t thresh) {
    if (ads1015_write_to_register(handler, ADS1015_REG_HI_THRESH, thresh) < 0) {
        return ADS1015_FAIL;
    }
    
    return ADS1015_OK;
}


ads1015_result_t ads1015_set_low_thresh(ads1015_handler_t *handler, uint16_t thresh) {
    if (ads1015_write_to_register(handler, ADS1015_REG_LO_THRESH, thresh) < 0) {
        return ADS1015_FAIL;
    }
    
    return ADS1015_OK;
}


ads1015_result_t ads1015_general_call_reset(ads1015_handler_t *handler) {
    uint8_t msg = 0b00000110;

    if (handler->send(handler->i2c_addr, &msg, 1, handler->fd) < 0) {
        return ADS1015_FAIL;
    }

    return ADS1015_OK;
}