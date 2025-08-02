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

    return handler->send(handler->i2c_addr, buffer, 3);

}

static ads1015_result_t ads1015_read_register(ads1015_handler_t *handler, uint8_t reg, uint16_t *data) {
    uint8_t buffer[2] = {0};
    int8_t ret_val = 0;
    buffer[0] = reg;
    
    ret_val = handler->send(handler->i2c_addr, &reg, 1);

    if (ret_val < 0)
    {
        return ret_val;
    }

    ret_val = handler->receive(handler->i2c_addr, buffer, 2);

    if (ret_val < 0)
    {
        return ret_val;
    }

    *data = (uint16_t)(buffer[0] << 8) | (uint16_t)buffer[1];

    return ADS1015_OK;

}

ads1015_result_t ads1015_init(ads1015_handler_t *handler, uint8_t address) {

}

ads1015_result_t ads1015_start_single_meas(ads1015_handler_t *handler) {
    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, ADS1015_CONV_START);
}


ads1015_result_t ads1015_check_if_data_available(ads1015_handler_t *handler) {

}


ads1015_result_t ads1015_read_sample(ads1015_handler_t *handler, ads1015_sample_t *sample) {
    if(ads1015_read_register(handler, ADS1015_REG_CONVERSION, sample->raw) != ADS1015_OK) {
        return ADS1015_FAIL;
    }

    sample->raw == sample->raw >> 4;
    sample->voltage == 0; //TODO

    return ADS1015_OK;
}


ads1015_result_t ads1015_get_op_status(ads1015_handler_t *handler) {

}


ads1015_result_t ads1015_set_mux(ads1015_handler_t *handler, ads1015_mux_t mux) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_MUX_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (mux << ADS1015_MUX_SHIFT) | data);
}


ads1015_result_t ads1015_set_pga(ads1015_handler_t *handler, ads1015_pga_t pga) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_PGA_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (pga << ADS1015_PGA_SHIFT) | data);
}


ads1015_result_t ads1015_set_mode(ads1015_handler_t *handler, ads1015_mode_t mode) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_MODE_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (mode << ADS1015_MODE_SHIFT) | data);
}


ads1015_result_t ads1015_set_data_rate(ads1015_handler_t *handler, ads1015_data_rate_t rate) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_DATA_RATE_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (rate << ADS1015_DATA_RATE_SHIFT) | data);
}


ads1015_result_t ads1015_set_comp_mode(ads1015_handler_t *handler, ads1015_comp_mode_t comp_mode) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_MODE_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_mode << ADS1015_COMP_MODE_SHIFT) | data);
}


ads1015_result_t ads1015_set_comp_pol(ads1015_handler_t *handler, ads1015_comp_pol_t comp_pol) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_POL_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_pol << ADS1015_COMP_POL_SHIFT) | data);
}


ads1015_result_t ads1015_set_comp_lat(ads1015_handler_t *handler, ads1015_comp_lat_t comp_lat) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_LAT_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_lat << ADS1015_COMP_LAT_SHIFT) | data);
}


ads1015_result_t ads1015_set_comp_que(ads1015_handler_t *handler, ads1015_comp_que_t comp_que) {
    uint16_t data = 0;

    if (ads1015_read_register(handler, ADS1015_REG_CONFIG, &data) != ADS1015_OK)
    {
        return ADS1015_FAIL;
    }

    data &= ~ADS1015_COMP_QUE_MASK;

    return ads1015_write_to_register(handler, ADS1015_REG_CONFIG, (comp_que << ADS1015_COMP_QUE_SHIFT) | data);
}


ads1015_result_t ads1015_set_i2c_address(ads1015_handler_t *handler, uint8_t i2c_address) {

}


ads1015_result_t ads1015_set_high_thresh(ads1015_handler_t *handler, uint16_t thresh) {

}


ads1015_result_t ads1015_set_low_thresh(ads1015_handler_t *handler, uint16_t thresh) {

}


ads1015_result_t ads1015_general_call_reset(ads1015_handler_t *handler) {

}