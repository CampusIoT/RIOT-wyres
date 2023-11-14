# name of your application
APPLICATION = test-pkg-semtech-loramac

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards
# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Fix the problem of the size of the debugging files
CFLAGS_DBG = 


include $(RIOTBASE)/tests/Makefile.tests_common
BOARD_WITHOUT_LORAMAC_RX := \
    arduino-mega2560 \
    i-nucleo-lrwan1 \
    stm32f0discovery \
    waspmote-pro \

LORA_DRIVER ?= sx1272
LORA_REGION ?= EU868

USEPKG += semtech-loramac
USEMODULE += $(LORA_DRIVER)

# load loramac RX if board supports it
ifeq (,$(filter $(BOARD),$(BOARD_WITHOUT_LORAMAC_RX)))
  USEMODULE += semtech_loramac_rx
endif

USEMODULE += auto_init_loramac
USEMODULE += shell_cmds_default
USEMODULE += fmt

FEATURES_OPTIONAL += periph_eeprom

include $(RIOTBASE)/Makefile.include
