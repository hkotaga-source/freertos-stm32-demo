TARGET = freertos_demo
BUILD_DIR = build

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

MCU = -mcpu=cortex-m3 -mthumb

C_DEFS = -DSTM32F103xB
C_INCLUDES = -ICore/Inc -IMiddlewares/FreeRTOS/include -IMiddlewares/FreeRTOS/portable/GCC/ARM_CM3

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -Wall -O2 -g -ffunction-sections -fdata-sections

# You need to add FreeRTOS source files here after downloading them
C_SOURCES = \
Core/Src/main.c

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@echo "Note: Add FreeRTOS object files and linker script to complete the build"
	@echo "This is a template Makefile"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
