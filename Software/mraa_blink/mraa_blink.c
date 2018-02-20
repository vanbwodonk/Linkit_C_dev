#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "mraa/gpio.h"
#include "mraa/common.h"

int main(int argc, char **argv)
{
    mraa_gpio_context gpio = NULL;
    const char *board_name = mraa_get_platform_name();
    int ledstate = 0;

    // for LinkIt MT7688 use WiFi LED
    gpio = mraa_gpio_init(44);

    fprintf(stdout, "GPIO BLINK EXAMPLE \nLibmraa Version: %s\nRunning on %s (Ctrl+C to exit)\n", mraa_get_version(), board_name);

    if (gpio == NULL)
    {
        fprintf(stdout, "Could not initilaize gpio\n");
        return 1;
    }

    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);

    while (1)
    {
        ledstate = !ledstate;
        mraa_gpio_write(gpio, !ledstate);
        sleep(1);
    }

    return 0;
}
