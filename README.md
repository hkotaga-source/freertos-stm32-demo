# FreeRTOS STM32 Demo

A clean **FreeRTOS** demonstration project written in Embedded C for STM32.

This project shows practical use of:

- Multiple FreeRTOS tasks
- Queue for inter-task communication
- Software timer
- LED control from different tasks
- Proper project structure with Makefile

## Features

- `LedTask` – Blinks an LED at a fixed rate
- `PrintTask` – Receives messages from a queue and prints them (UART)
- `TimerCallback` – Software timer that sends messages to the queue
- Simple and readable code, good for learning / portfolio

## Project Structure

```
freertos-stm32-demo/
├── Makefile
├── README.md
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── FreeRTOSConfig.h
│   │   └── ...
│   └── Src/
│       ├── main.c
│       └── freertos_hooks.c
├── Drivers/          # (placeholder for CMSIS / HAL if needed)
└── Middlewares/
    └── FreeRTOS/       # Put FreeRTOS source here
```

## How to use

1. Download FreeRTOS from https://www.freertos.org/
2. Place the FreeRTOS source under `Middlewares/FreeRTOS/`
3. Adjust `FreeRTOSConfig.h` according to your MCU
4. Build with:

```bash
make
```

## Notes

This is an educational / portfolio project.  
It focuses on clarity rather than full production readiness.

You can easily port it to STM32F4, G0, L4, or other Cortex-M devices.
