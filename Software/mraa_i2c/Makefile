# Build target executable when user executes "make"
TARGET=mraa_i2c

export STAGING_DIR=../../SDK/staging_dir
CC=../../SDK/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-uclibc-gcc
CFLAGS =-I.
CFLAGS+=-I ../../SDK/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/usr/include
CFLAGS+=-I ../../SDK/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/include
LDFLAGS =-L.
LDFLAGS+=-L../../SDK/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/usr/lib
LDFLAGS+=-L../../SDK/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/lib
LDFLAGS+=-lmraa -pthread -ldl

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)

# remove object files and executable when user executes "make clean"
clean:
	rm $(TARGET)

#send to linkit
send:
	scp $(TARGET) root@mylinkit.local:/root/develop
