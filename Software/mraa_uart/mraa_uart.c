#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "mraa.h"
#include "mraa/common.h"
#include "mraa/uart.h"

mraa_uart_context uart;

#define BUFFER_SIZE 64
volatile char buffer[BUFFER_SIZE];
volatile unsigned char buffer_head = 0, buffer_tail = 0;

void put_in_buffer(char data)
{
    buffer[buffer_head] = data;
    buffer_head++;
    if (buffer_head >= BUFFER_SIZE)
        buffer_head = 0;
}

unsigned char available_buffer(void)
{
    return ((buffer_head - buffer_tail) % BUFFER_SIZE);
    //return buffer_head - buffer_tail;
}

char get_from_buffer(void)
{
    char data;
    data = buffer[buffer_tail];
    buffer_tail++;
    if (buffer_tail >= BUFFER_SIZE)
        buffer_tail = 0;
    return data;
}

void *readUart(void *arg)
{
    //cz mraa serial read is blocking try to pool serial from thread
    char data[1];
    while (1)
    {
        mraa_uart_read(uart, data, 1);
        put_in_buffer(data[0]);
    }
}

int main(int argc, char **argv)
{
    pthread_t uartRX_thread;
    mraa_platform_t platform = mraa_get_platform_type();
    const char *board_name = mraa_get_platform_name();
    fprintf(stdout, "---------------------------------\n");
    fprintf(stdout, "- MRAA UART TEST\n- Libmraa Version: %s\n- Running on %s\n", mraa_get_version(), board_name);
    fprintf(stdout, "---------------------------------\n\n");

    uart = mraa_uart_init(0);
    mraa_uart_set_baudrate(uart, 57600);
    mraa_uart_set_mode(uart, 8, MRAA_UART_PARITY_NONE, 1); //8N1

    if (uart == NULL)
    {
        fprintf(stderr, "UART failed to setup\n");
        return EXIT_FAILURE;
    }

    char buffer[] = "This is UART MRAA!!\r\n";
    mraa_uart_write(uart, buffer, sizeof(buffer));
    int err = pthread_create(&uartRX_thread, NULL, &readUart, NULL);
    if (err != 0)
        printf("can't create thread :[%s]", strerror(err));
    else
        printf("Thread created successfully\n");
    while (1)
    {
        fprintf(stdout, "BLOCKING !! \r\n");
        char _data[100];
        unsigned char _available, i;
        _available = available_buffer();
        if (_available)
        {
            fprintf(stdout, "Data on buffer = %d\n", _available);
            for (i = 0; i < _available; i++)
                _data[i] = get_from_buffer();
            mraa_uart_write(uart, _data, _available);
        }
        sleep(5);
    }

    mraa_uart_stop(uart);
    mraa_deinit();
    return MRAA_SUCCESS;
}