# BOOT
BOOT_DIR = boot

LINKER_SCRIPT = $(BOOT_DIR)/default.ld
BOOT_CODE = $(BOOT_DIR)/boot.c

# TESTS
TESTS_DIR = tests
ACTIVE_TEST = $(shell grep -E "^CONFIG_TEST_.*=y" .config | cut -d_ -f3 | cut -d= -f1 | tr A-Z a-z)
TEST_SRC = $(TESTS_DIR)/$(ACTIVE_TEST)/*.c

# DRIVERS
DRIVERS_DIR = lib/drivers
ACTIVE_DRIVERS = $(shell grep -E "^CONFIG_DRIVER_.*=y" .config | cut -d_ -f3 | cut -d= -f1 | tr A-Z a-z)
DRIVERS_SRC = $(foreach dir,$(ACTIVE_DRIVERS),$(DRIVERS_DIR)/$(dir)/*.c)

UART_BAUD_RATE = $(shell grep -E "^CONFIG_UART_BAUD_RATE" .config | cut -d= -f2)

# BUILD
BUILD_DIR = build/

KCONFIGLIB_DIR = tools/kconfiglib

CC = arm-none-eabi-gcc

CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb
CFLAGS += -nostdlib

INCLUDES += -Ilib/include

# TARGETS

.DEFAULT_GOAL := build

test:
	@echo $(UART_BAUD_RATE)


clean:
	@rm $(BUILD_DIR)/*


build: genheader
	@$(CC) $(CFLAGS) $(TEST_SRC) $(DRIVERS_SRC) $(BOOT_CODE) -T $(LINKER_SCRIPT) $(INCLUDES) -o $(BUILD_DIR)/$(ACTIVE_TEST).elf


flash:
	@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(ACTIVE_TEST).elf verify reset exit"


open-uart:
	@minicom --baudrate $(UART_BAUD_RATE) --device /dev/ttyACM0


menuconfig:
	@python3 $(KCONFIGLIB_DIR)/menuconfig.py


genheader:
	@python3 $(KCONFIGLIB_DIR)/genconfig.py
	@mv config.h lib/include
