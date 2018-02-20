#include "mraa.h"
#include "mraa/common.h"
int main(int argc, char** argv)
{
    mraa_platform_t platform = mraa_get_platform_type();
    const char* board_name = mraa_get_platform_name();
    fprintf(stdout, "hello mraa\n Version: %s\n Running on %s\n", mraa_get_version(), board_name);
    mraa_deinit();
    return MRAA_SUCCESS;
}
