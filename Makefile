# BOOT
BOOT_DIR = boot/

LINKER_SCRIPT = $(BOOT_DIR)/default.ld
BOOT_CODE = $(BOOT_DIR)/boot.c

# TESTS
TESTS_DIR = tests/

ifdef TEST
include $(TESTS_DIR)/$(TEST)/config.mk
TEST_SOURCES = $(addprefix $(TESTS_DIR)$(TEST)/, $(TEST_SOURCES_L))
endif

# BUILD
BUILD_DIR = build/

CC = arm-none-eabi-gcc

CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb
CFLAGS += -nostdlib


# TARGETS
build-test: # $TEST
	echo $(TEST_SOURCES)
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(BOOT_CODE) -T $(LINKER_SCRIPT) -o $(BUILD_DIR)/$(TEST).elf

build:
	arm-none-eabi-gcc main.c start.c -T main.ld -o blink.elf -mcpu=cortex-m4 -mthumb -nostdlib

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"
