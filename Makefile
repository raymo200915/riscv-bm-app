CROSS_COMPILE ?= riscv64-unknown-linux-gnu-

CC      := $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
READELF := $(CROSS_COMPILE)readelf
CPP = $(CC) -E

# bare-metal required flags when using a linux toolchain:
# CFLAGS: -ffreestanding -nostdlib -fno-builtin -fno-pie -fno-stack-protector
# LDFLAGS: -nostdlib -Tlink.ld -Wl,-no-pie
CFLAGS  := -Os -g \
           -march=rv64gc -mabi=lp64d -mcmodel=medany \
           -ffreestanding -nostdlib -fno-builtin \
           -fno-pie -fno-stack-protector \
           -Wall -Wextra

LDFLAGS := -nostdlib -Tlink.ld \
           -Wl,-Map=bm-app.map,--gc-sections \
           -Wl,-no-pie

OBJS := start.o bm_app.o sbi.o timer.o

#CPPFLAGS := $(if $(BM_M_MODE),-DBM_M_MODE,)
#CPPFLAGS += $(if $(SBI_V01_SUPPORT),-DCONFIG_RISCV_SBI_V01,)
#CFLAGS += $(CPPFLAGS)
CFLAGS += -DCONFIG_RISCV_SBI_V01
CFLAGS += -Iincludes

all: bm-app.elf

link.ld: link.ld.S
	$(CPP) $(CPPFLAGS) -P -o link.ld link.ld.S

bm-app.elf: $(OBJS) link.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o bm-app.elf bm-app.map link.ld
