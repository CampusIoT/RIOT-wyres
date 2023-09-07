# name of your application
APPLICATION = test-driver-sx127x

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= ../../../../RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

include $(RIOTBASE)/tests/Makefile.tests_common

USEMODULE += od
USEMODULE += ps
USEMODULE += shell_cmds_default
USEMODULE += fmt

DRIVER ?= sx1272

# use SX1276 by default
USEMODULE += $(DRIVER)

include $(RIOTBASE)/Makefile.include
