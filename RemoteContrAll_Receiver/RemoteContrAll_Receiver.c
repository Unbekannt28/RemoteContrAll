#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pio.h"
#include "build/manchester_encoding.pio.h"

uint8_t uart_buffer[4];

// Need to connect a wire from GPIO2 -> GPIO3
const uint pin_tx = 2;
const uint pin_rx = 3;

int bit_sequence = 0b1001101000000001;

void printBinary(int num) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

bool checkBinarySequence(int num, int sequence, int length) {
    for (int i = 0; i <= (32 - length); i++) {
        int masked = (num >> i) & ((1 << length) - 1);
        if (masked == sequence) {
            return true;
        }
    }
    return false;
}

int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Example to turn on the Pico W LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    PIO pio = pio0;
    //uint sm_tx = 0;
    uint sm_rx = 1;

    //uint offset_tx = pio_add_program(pio, &manchester_tx_program);
    uint offset_rx = pio_add_program(pio, &manchester_rx_program);
    //printf("Transmit program loaded at %d\n", offset_tx);
    printf("Receive program loaded at %d\n", offset_rx);

    //manchester_tx_program_init(pio, sm_tx, offset_tx, pin_tx, 1.f);
    manchester_rx_program_init(pio, sm_rx, offset_rx, pin_rx, 10000.f);

    // pio_sm_set_enabled(pio, sm_tx, false);
    // pio_sm_put_blocking(pio, sm_tx, 0);
    // pio_sm_put_blocking(pio, sm_tx, 0x0ff0a55a);
    // pio_sm_put_blocking(pio, sm_tx, 0x12345678);
    // pio_sm_set_enabled(pio, sm_tx, true);

    uint32_t new_fifo;
    while (true) {
        new_fifo = pio_sm_get_blocking(pio, sm_rx);
        printBinary(new_fifo);
        if (checkBinarySequence(new_fifo, bit_sequence, 16)) {
            printf(" Sequence Found!");
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            sleep_ms(100);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
        printf("\n");
    }
}
