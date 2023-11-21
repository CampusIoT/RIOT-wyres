# name of your application
APPLICATION = test-saul

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= ../../../../RIOT-OS/RIOT
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

# Accelero : ST [LIS2DE12](https://github.com/RIOT-OS/RIOT/tree/master/tests/drivers/lis2dh12) via I2C 
# TODO add driver

# Altimeter : ST [LPS22HB](https://github.com/RIOT-OS/RIOT/tree/master/tests/drivers/lpsxxx) via I2C
USEMODULE += lps22hb

# include and auto-initialize all available sensors
USEMODULE += saul_default

USEMODULE += xtimer

include $(RIOTBASE)/Makefile.include
