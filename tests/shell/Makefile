# name of your application
APPLICATION = test-shell

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= ../../../../RIOT-OS/RIOT
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

include git.mk

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

USEMODULE += app_metadata
USEMODULE += shell_cmds_default
USEMODULE += ps

FEATURES_REQUIRED += periph_rtc
FEATURES_OPTIONAL += periph_rtc_ms
FEATURES_OPTIONAL += periph_rtc_mem

DISABLE_MODULE += periph_init_rtc



# Use a terminal that does not introduce extra characters into the stream.
RIOT_TERMINAL ?= socat

APP_SHELL_FMT ?= NONE

# microbit qemu failing currently
TEST_ON_CI_BLACKLIST += microbit

include $(RIOTBASE)/Makefile.include

CFLAGS += '-DTHREAD_STACKSIZE_MAIN=(THREAD_STACKSIZE_SMALL+THREAD_EXTRA_STACKSIZE_PRINTF)'

# the test script skips tests if socat is not used
$(call target-export-variables,$(RIOT_TERMINAL),RIOT_TERMINAL)
