# name of your application
APPLICATION = test-driver-lis2dh12

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= ../../../../RIOT-OS/RIOT
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# include $(RIOTBASE)/tests/drivers/Makefile.drivers_common

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

# use lis2dh12_spi for SPI-Mode and lis2dh12_i2c for I2C-Mode
DRIVER ?= lis2dh12_i2c

USEMODULE += fmt
USEMODULE += ztimer
USEMODULE += ztimer_msec
USEMODULE += shell_cmds_default
USEMODULE += $(DRIVER)

# for using lis2dh12 with interrupt function
USEMODULE += lis2dh12_int


# -----------------------------
# Debug
# -----------------------------

# Set this to 1 to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

#CFLAGS += -DENABLE_DEBUG=1
CFLAGS += -DDEBUG_ASSERT_VERBOSE=1


include $(RIOTBASE)/Makefile.include
