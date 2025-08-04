#include "ads1015.h"
#include "ads1015_platform.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sleep(5);
    int fd = open("/dev/i2c-1", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to open i2c\n", __FILE__, __LINE__);
        return 1;
    }

    ads1015_handler_t ads1015;
    ads1015_platform_init(&ads1015);
    if (ads1015_init(&ads1015, ADS1015_I2C_ADDR_GND, fd) != ADS1015_OK) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to initialize sensor\n", __FILE__, __LINE__);
        return 1;
    }
    
    if (ads1015_set_mux(&ads1015, ADS1015_MUX_AIN0_AIN_GND) != ADS1015_OK) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to change mux setting\n", __FILE__, __LINE__);
        return 1;
    }

    if (ads1015_set_pga(&ads1015, ADS1015_PGA_4_096) != ADS1015_OK) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to change mux setting\n", __FILE__, __LINE__);
        return 1;
    }

    for (size_t i = 0; i < 5; i++)
    {
        if (ads1015_start_single_meas(&ads1015) != ADS1015_OK) {
        fprintf(stderr, "[ERROR] %s:%d: Failed to start measurement\n", __FILE__, __LINE__);
        return 1;
        }
        sleep(5);
        ads1015_sample_t sample;
        if (ads1015_read_sample(&ads1015, &sample) != ADS1015_OK) {
            fprintf(stderr, "[ERROR] %s:%d: Failed to take sample\n", __FILE__, __LINE__);
            return 1;
        }
        float result = 30.9375f * sample.voltage - 11.875f;
        fprintf(stdout, "[INFO] %s:%d: Result of sample is %d, %fV, %fm/s\n", __FILE__, __LINE__, sample.raw, sample.voltage, result);
        sleep(1);
    }
    
    

    return 0;
}