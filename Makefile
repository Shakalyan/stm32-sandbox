# BOOT
BOOT_DIR = boot

LINKER_SCRIPT = $(BOOT_DIR)/default.ld
BOOT_CODE = $(BOOT_DIR)/boot.c

# TESTS
TESTS_DIR = tests
DRIVERS_DIR = lib/drivers

ifdef TEST
include $(TESTS_DIR)/$(TEST)/config.mk
TEST_SOURCES = $(addprefix $(TESTS_DIR)/$(TEST)/, $(TEST_SOURCES_L))
TEST_DRIVERS = $(addprefix $(DRIVERS_DIR)/, $(TEST_DRIVERS_L))
endif

# BUILD
BUILD_DIR = build/

CC = arm-none-eabi-gcc

CFLAGS += -mcpu=cortex-m4
CFLAGS += -mthumb
CFLAGS += -nostdlib

INCLUDES += -Ilib/include


# TARGETS
build-test: # $TEST
#	echo $(TEST_SOURCES)
#	echo $(TEST_DRIVERS)
	$(if $(TEST),, $(error "Specify TEST= to build"))

	@$(CC) $(CFLAGS) $(TEST_SOURCES) $(TEST_DRIVERS) $(BOOT_CODE) -T $(LINKER_SCRIPT) $(INCLUDES) -o $(BUILD_DIR)/$(TEST).elf


flash: # $ELF
	$(if $(ELF),, $(error "Specify ELF= file to flash"))

	@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(ELF) verify reset exit"
