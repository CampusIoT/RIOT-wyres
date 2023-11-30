# name of your application
APPLICATION = test-solpos

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= ../../../../RIOT-OS/RIOT
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

EXTERNAL_MODULE_DIRS += ../../modules

USEMODULE += solpos

USEMODULE += printf_float


include $(RIOTBASE)/Makefile.include
