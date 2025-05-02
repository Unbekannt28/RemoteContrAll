#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"


// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart0 // was uart1
#define BAUD_RATE 300

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 0 // was 4
#define UART_RX_PIN 1 // was 5

/*

Layout:

/-------------\
|  X   O   1  |
|             |
|  4  4&2  2  |
|  5  5&3  3  |
|             |
|  8  8&6  6  |
|  9  9&7  7  |
| 12 12&10 10 |
|             |
| 13 13&11 11 |
| 19 19&16 16 |
|             |
| 18 18&15 15 |
| 17 17&14 14 |
\-------------/

*/

//int RF_DATA = 0;

uint8_t uart_prefix[3] = "UbK";

void send_key(int key) {
    uint8_t uart_msg[4];
    uart_msg[0] = uart_prefix[0];
    uart_msg[1] = uart_prefix[1];
    uart_msg[2] = uart_prefix[2];
    uart_msg[3] = key;
    uart_write_blocking(UART_ID, uart_msg, 4);
}

void gpio_toggle(int gpio) {
    if (gpio_get(gpio)) {
        gpio_put(gpio, false);
    }
    else {
        gpio_put(gpio, true);
    }
}

void gpio_flash(int gpio, int flashes) {
    for (int i = 0; i < flashes; i++) {
        gpio_put(gpio, true);
        sleep_ms(200);
        gpio_put(gpio, false);
        sleep_ms(200);
    }
}

int main()
{
    stdio_init_all();

    for (int i = 1; i <= 19; i++) {
        gpio_init(1);
        gpio_set_dir(1, false);
    }

    gpio_init(25);
    gpio_set_dir(25, true);

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    while (true) {
        if (!gpio_get(1)) {
            send_key(1);
        }

        else if(!gpio_get(4) && !gpio_get(2)) {
            send_key(3);
        }
        else if (!gpio_get(4)) {
            send_key(2);
        }
        else if (!gpio_get(2)) {
            send_key(4);
        }

        else if(!gpio_get(5) && !gpio_get(3)) {
            send_key(6);
        }
        else if (!gpio_get(5)) {
            send_key(5);
        }
        else if (!gpio_get(3)) {
            send_key(7);
        }

        else if(!gpio_get(8) && !gpio_get(6)) {
            send_key(9);
        }
        else if (!gpio_get(8)) {
            send_key(8);
        }
        else if (!gpio_get(6)) {
            send_key(10);
        }

        else if(!gpio_get(9) && !gpio_get(7)) {
            send_key(12);
        }
        else if (!gpio_get(9)) {
            send_key(11);
        }
        else if (!gpio_get(7)) {
            send_key(13);
        }

        else if(!gpio_get(12) && !gpio_get(10)) {
            send_key(15);
        }
        else if (!gpio_get(12)) {
            send_key(14);
        }
        else if (!gpio_get(10)) {
            send_key(16);
        }

        else if(!gpio_get(13) && !gpio_get(11)) {
            send_key(18);
        }
        else if (!gpio_get(13)) {
            send_key(17);
        }
        else if (!gpio_get(11)) {
            send_key(19);
        }

        else if(!gpio_get(19) && !gpio_get(16)) {
            send_key(21);
        }
        else if (!gpio_get(19)) {
            send_key(20);
        }
        else if (!gpio_get(16)) {
            send_key(22);
        }

        else if(!gpio_get(18) && !gpio_get(15)) {
            send_key(24);
        }
        else if (!gpio_get(18)) {
            send_key(23);
        }
        else if (!gpio_get(15)) {
            send_key(25);
        }

        else if(!gpio_get(17) && !gpio_get(14)) {
            send_key(27);
        }
        else if (!gpio_get(17)) {
            send_key(26);
        }
        else if (!gpio_get(14)) {
            send_key(28);
        }

        else {
            gpio_toggle(25);
        }
        sleep_ms(400);
    }
}