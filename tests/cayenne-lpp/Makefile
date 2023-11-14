# name of your application
APPLICATION = test-driver-sx127x

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= ../../../../RIOT-OS/RIOT
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

USEPKG += cayenne-lpp

USEMODULE += ztimer
USEMODULE += ztimer_sec 
USEMODULE += ztimer_msec

USEMODULE += printf_float


include $(RIOTBASE)/Makefile.include
