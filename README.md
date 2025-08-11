# ads1015-driver

A C driver for the ADS1015 ADC, designed for use on the Raspberry Pi 4 (RPi4) but may work on other platforms supporting I2C and the ADS1x1x family.

## Features

- Supports single-shot and continuous conversion modes
- Configurable multiplexer (MUX), programmable gain amplifier (PGA), data rate, comparator, and more
- Platform abstraction for easy porting
- Example application included

## Directory Structure

```
.
├── ads1015.c              # Core driver implementation
├── ads1015.h              # Driver API and type definitions
├── ads1015_platform.c     # Linux/RPi4 platform-specific I2C implementation
├── ads1015_platform.h     # Platform abstraction header
├── example/
│   ├── main.c             # Example usage
│   └── Makefile           # Build script for the example
├── LICENSE
├── README.md
└── .gitignore
```

## Getting Started

### Prerequisites

- Linux system with I2C support (e.g., Raspberry Pi)
- `libi2c-dev` installed (`sudo apt-get install libi2c-dev`)
- GCC or compatible C compiler

### Build Example

```sh
cd example
make
```

### Run Example

Make sure your ADS1015 is connected to the I2C bus (default `/dev/i2c-1`):

```sh
sudo ./ads1015_example
```

The example will initialize the ADS1015, take several samples, and print the raw and voltage values.

## Usage

Include the driver files in your project:

```c
#include "ads1015.h"
#include "ads1015_platform.h"
```

See [`example/main.c`](example/main.c) for a usage example.

## API

The main API is defined in [`ads1015.h`](ads1015.h). Key functions include:

- [`ads1015_init`](ads1015.h)
- [`ads1015_start_single_meas`](ads1015.h)
- [`ads1015_read_sample`](ads1015.h)
- [`ads1015_set_mux`](ads1015.h)
- [`ads1015_set_pga`](ads1015.h)
- ...and more

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Author
Hall.T ([AimrayX](https://github.com/AimrayX))
