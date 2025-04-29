#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

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

int RF_DATA = 0;

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

    gpio_init(RF_DATA);
    gpio_set_dir(RF_DATA, true);

    while (true) {
        if (!gpio_get(1)) {
            gpio_flash(RF_DATA, 1);
        }

        else if(!gpio_get(4) && !gpio_get(2)) {
            gpio_flash(RF_DATA, 3);
        }
        else if (!gpio_get(4)) {
            gpio_flash(RF_DATA, 2);
        }
        else if (!gpio_get(2)) {
            gpio_flash(RF_DATA, 4);
        }

        else if(!gpio_get(5) && !gpio_get(3)) {
            gpio_flash(RF_DATA, 6);
        }
        else if (!gpio_get(5)) {
            gpio_flash(RF_DATA, 5);
        }
        else if (!gpio_get(3)) {
            gpio_flash(RF_DATA, 7);
        }

        else if(!gpio_get(8) && !gpio_get(6)) {
            gpio_flash(RF_DATA, 9);
        }
        else if (!gpio_get(8)) {
            gpio_flash(RF_DATA, 8);
        }
        else if (!gpio_get(6)) {
            gpio_flash(RF_DATA, 10);
        }

        else if(!gpio_get(9) && !gpio_get(7)) {
            gpio_flash(RF_DATA, 12);
        }
        else if (!gpio_get(9)) {
            gpio_flash(RF_DATA, 11);
        }
        else if (!gpio_get(7)) {
            gpio_flash(RF_DATA, 13);
        }

        else if(!gpio_get(12) && !gpio_get(10)) {
            gpio_flash(RF_DATA, 15);
        }
        else if (!gpio_get(12)) {
            gpio_flash(RF_DATA, 14);
        }
        else if (!gpio_get(10)) {
            gpio_flash(RF_DATA, 16);
        }

        else if(!gpio_get(13) && !gpio_get(11)) {
            gpio_flash(RF_DATA, 18);
        }
        else if (!gpio_get(13)) {
            gpio_flash(RF_DATA, 17);
        }
        else if (!gpio_get(11)) {
            gpio_flash(RF_DATA, 19);
        }

        else if(!gpio_get(19) && !gpio_get(16)) {
            gpio_flash(RF_DATA, 21);
        }
        else if (!gpio_get(19)) {
            gpio_flash(RF_DATA, 20);
        }
        else if (!gpio_get(16)) {
            gpio_flash(RF_DATA, 22);
        }

        else if(!gpio_get(18) && !gpio_get(15)) {
            gpio_flash(RF_DATA, 24);
        }
        else if (!gpio_get(18)) {
            gpio_flash(RF_DATA, 23);
        }
        else if (!gpio_get(15)) {
            gpio_flash(RF_DATA, 25);
        }

        else if(!gpio_get(17) && !gpio_get(14)) {
            gpio_flash(RF_DATA, 27);
        }
        else if (!gpio_get(17)) {
            gpio_flash(RF_DATA, 26);
        }
        else if (!gpio_get(14)) {
            gpio_flash(RF_DATA, 28);
        }

        else {
            gpio_toggle(25);
        }
        sleep_ms(400);
    }
}