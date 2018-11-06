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
	
all: lucky_jp.elf lucky_us.elf
	
lucky_jp.elf: $(obj) jp_rom.ld
	$(cc) $(lflags) -Tjp_rom.ld -o $@ jp_rom.o $<
	$(dump) $@ lucky_jp_rom.bin
	
lucky_us.elf: $(obj) us_rom.ld
	$(cc) $(lflags) -Tus_rom.ld -o $@ us_rom.o $<
	$(dump) $@ lucky_us_rom.bin
	
clean:
	rm -rf $(obj) lucky_jp.elf lucky_us.elf lucky_jp_rom.bin lucky_us_rom.bin
	