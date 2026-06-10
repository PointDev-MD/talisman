#include <stdint.h>

static volatile uint16_t *const COM1_PORT = (uint16_t *)0x3F8;

static int serial_is_transmit_empty(void) {
    return (*(volatile uint8_t *)(COM1_PORT) & 0x20) != 0;
}

void serial_init(void) {
    *(volatile uint8_t *)(COM1_PORT + 1) = 0x00;
    *(volatile uint8_t *)(COM1_PORT + 3) = 0x80;
    *(volatile uint8_t *)(COM1_PORT + 0) = 0x03;
    *(volatile uint8_t *)(COM1_PORT + 1) = 0x00;
    *(volatile uint8_t *)(COM1_PORT + 3) = 0x03;
    *(volatile uint8_t *)(COM1_PORT + 2) = 0xC7;
    *(volatile uint8_t *)(COM1_PORT + 4) = 0x0B;
}

void serial_write(char c) {
    while (!serial_is_transmit_empty()) {
    }
    *(volatile uint8_t *)(COM1_PORT) = (uint8_t)c;
}
