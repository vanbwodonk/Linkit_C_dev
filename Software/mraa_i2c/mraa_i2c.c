#include "mraa.h"
#include "mraa/common.h"
#include "mraa/i2c.h"

//#define MODE_NORMAL I2C_STD 	//up to 100Khz
//#define MODE_FAST   I2C_FAST 	//up to 400Khz
//#define MODE_HIGH   I2C_HIGH    //up to 3.4Mhz 
#define I2C_WRITE 0
#define I2C_READ 1
#define PCF8574_ADDR 0x20

int main(int argc, char **argv)
{
    mraa_platform_t platform = mraa_get_platform_type();
    const char *board_name = mraa_get_platform_name();
    fprintf(stdout, "---------------------------------\n");
    fprintf(stdout, "- MRAA I2C TEST\n- Libmraa Version: %s\n- Running on %s\n", mraa_get_version(), board_name);
    fprintf(stdout, "---------------------------------\n\n");
    mraa_init();
    mraa_i2c_context i2c;
    i2c = mraa_i2c_init(0);
    if (i2c == NULL)
    {
        return MRAA_ERROR_NO_RESOURCES;
    }
    //mraa_i2c_frequency(i2c, MODE_FAST); not working on linkit
    mraa_i2c_address(i2c, PCF8574_ADDR);
    //set default value, or set pin PULLUP if pin as input
    mraa_i2c_write_byte(i2c, 0xFF);
    sleep(1);
    while (1)
    {
        uint8_t val;
        //----------------------------------------------------
        //                      TOGGLE PIN
        //----------------------------------------------------
        // mraa_i2c_write_byte(i2c, 0x01);
        // val = mraa_i2c_read_byte(i2c);
        // fprintf(stdout, "PCF8574 value = 0x%X\r\n", val);
        // sleep(3);

        // mraa_i2c_write_byte(i2c, 0x00);
        // val = mraa_i2c_read_byte(i2c);
        // fprintf(stdout, "PCF8574 value = 0x%X\r\n", val);
        // sleep(3);

        //----------------------------------------------------
        //      READ INPUT PIN 
        //----------------------------------------------------
        val = mraa_i2c_read_byte(i2c);
        fprintf(stdout, "PCF8574 value = 0x%X\r\n", val);
        sleep(1);
    }
    mraa_deinit();
    return MRAA_SUCCESS;
}
