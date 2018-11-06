cc = arm-none-eabi-gcc
arch = -mcpu=arm7tdmi -mthumb -mthumb-interwork
cflags = $(arch) -Os -fomit-frame-pointer -fno-toplevel-reorder -nostdinc -mlong-calls
lflags = $(arch) -Wl,--no-check-sections,--no-warn-mismatch
dump = arm-none-eabi-objcopy -O binary
deps = $(shell find ../ -name "*.h")
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o)

%.o: %.c $(deps)
	$(cc) $(cflags) -c $< -o $@

.PHONY:all clean
	
all: lucky.elf
	
lucky.elf: $(obj) rom.ld
	$(cc) $(lflags) -Trom.ld -o $@ rom.o $<
	$(dump) $@ lucky_rom.bin
	
clean:
	rm -rf $(obj) lucky.elf lucky_rom.bin
	