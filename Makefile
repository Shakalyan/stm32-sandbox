build:
	arm-none-eabi-gcc main.c start.c -T main.ld -o blink.elf -mcpu=cortex-m4 -mthumb -nostdlib

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"
