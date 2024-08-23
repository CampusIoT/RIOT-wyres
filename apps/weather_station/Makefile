# name of your application
APPLICATION = test_station

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= ${HOME}/github/RIOT-OS/RIOT

# Path to my boards
EXTERNAL_BOARD_DIRS ?= ../../boards

# Path to custom module
EXTERNAL_MODULE_DIRS += ../../modules

# If no BOARD is found in the environment, use this default:
BOARD ?= wyres-base

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Modules to include:
USEMODULE += xtimer
USEMODULE += analog_util
USEMODULE += sen15901
USEMODULE += periph_gpio_irq

LORA_DRIVER ?= sx1272
LORA_REGION ?= EU868

USEPKG += semtech-loramac
USEMODULE += $(LORA_DRIVER)

USEMODULE += auto_init_loramac
USEMODULE += fmt

FEATURES_REQUIRED += periph_adc

FEATURES_OPTIONAL += periph_eeprom

include $(RIOTBASE)/Makefile.include
