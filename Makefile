# BOOT
BOOT_DIR = boot

LINKER_SCRIPT = $(BOOT_DIR)/default.ld
BOOT_CODE = $(BOOT_DIR)/boot.c


# TESTS
TESTS_DIR = tests
ACTIVE_TEST = $(shell grep -E "^CONFIG_TEST_.*=y" .config | sed -E 's/CONFIG_TEST_//g' | cut -d= -f1 | tr A-Z a-z)
TEST_SRC = $(TESTS_DIR)/$(ACTIVE_TEST)/*.c


# DRIVERS
DRIVERS_DIR = lib/drivers
ACTIVE_DRIVERS = $(shell grep -E "^CONFIG_DRIVER_.*=y" .config | sed -E 's/CONFIG_DRIVER_//g' | cut -d= -f1 | tr A-Z a-z)
DRIVERS_SRC = $(foreach dir,$(ACTIVE_DRIVERS),$(DRIVERS_DIR)/$(dir)/*.c)

UART_BAUD_RATE = $(shell grep -E "^CONFIG_UART_BAUD_RATE" .config | cut -d= -f2)


# COMMON
COMMON_DIR = lib/common
COMMON_SRC = $(COMMON_DIR)/test_runner/test_runner.c \
			 $(COMMON_DIR)/log/log.c \
			 $(COMMON_DIR)/timer/timer.c


# BUILD
BUILD_DIR = build/

KCONFIGLIB_DIR = tools/kconfiglib

CC = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
GDB = arm-none-eabi-gdb

CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb
CFLAGS += -nostdlib
ifeq ($(DEBUG), yes)
CFLAGS += -g
endif

INCLUDES += -Ilib/include


# TARGETS

.DEFAULT_GOAL := build
.PHONY: test clean build flash open-uart open-gdb menuconfig

test:
	@echo $(DRIVERS_SRC)
	@echo $(TEST_SRC)
	@echo $(COMMON_SRC)


clean:
	@rm $(BUILD_DIR)/*


build:
	@$(CC) $(CFLAGS) $(TEST_SRC) $(DRIVERS_SRC) $(COMMON_SRC) $(BOOT_CODE) -T $(LINKER_SCRIPT) $(INCLUDES) -o $(BUILD_DIR)/$(ACTIVE_TEST).elf
	@$(OBJDUMP) -D $(BUILD_DIR)/$(ACTIVE_TEST).elf > $(BUILD_DIR)/$(ACTIVE_TEST).dis

flash:
	@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(ACTIVE_TEST).elf verify reset exit"


open-uart:
	@minicom --baudrate $(UART_BAUD_RATE) --device /dev/ttyACM0


open-gdb:
	make build DEBUG=yes
	@sh -c '\
		openocd -f interface/stlink.cfg -f target/stm32f4x.cfg & \
		OC_PID=$$!; \
		$(GDB) $(BUILD_DIR)/$(ACTIVE_TEST).elf -ex "target remote localhost:3333"; \
		kill $$OC_PID; wait $$OC_PID \
	'


menuconfig:
	@python3 $(KCONFIGLIB_DIR)/menuconfig.py
	@python3 $(KCONFIGLIB_DIR)/genconfig.py
	@mv config.h lib/include


genheader:
	@python3 $(KCONFIGLIB_DIR)/genconfig.py
	@mv config.h lib/include
