# name of your application
APPLICATION = test-driver-sx127x

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= ../../../../RIOT-OS/RIOT
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

# include $(RIOTBASE)/tests/Makefile.tests_common

USEMODULE += od
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_cmds_default
#USEMODULE += shell_commands
USEMODULE += fmt

DRIVER ?= sx1272
# use SX1276 by default
USEMODULE += $(DRIVER)

# Fix the problem of the size of the debugging files
CFLAGS_DBG = 

CFLAGS += -DISR_STACKSIZE=1024U
#CFLAGS += -DSX127X_STACKSIZE=1024U


include $(RIOTBASE)/Makefile.include
