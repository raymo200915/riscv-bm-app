PROJECT      := bm-app

CROSS_COMPILE ?= riscv64-unknown-linux-gnu-

CC      := $(CROSS_COMPILE)gcc
CFLAGS  := -Os -g -march=rv64gc -mabi=lp64d \
           -mcmodel=medany \
           -ffreestanding -nostdlib -fno-builtin \
           -Wall -Wextra
LDFLAGS := -nostdlib -Tlink.ld -Wl,-Map=$(PROJECT).map,--gc-sections

all: $(PROJECT).elf

$(PROJECT).elf: bm_app.o
	$(CC) $(LDFLAGS) -o $@ $^

bm_app.o: bm_app.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).map

.PHONY: all clean
