PROJ_NAME := iot_gateway
export PROJ_NAME

CROSS_COMPILE 	= arm-none-eabi-
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AS		= $(CROSS_COMPILE)as
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
SIZE		= $(CROSS_COMPILE)size
export CC LD AS CPP AR NM
export STRIP OBJCOPY OBJDUMP SIZE

TOPDIR		:= $(shell pwd)
APPDIR		:= $(TOPDIR)/app
COREDIR 	:= $(TOPDIR)/core
BSPDIR		:= $(TOPDIR)/bsp
SDKDIR		:= $(BSPDIR)/sdk
LDDIR		:= $(TOPDIR)/ld
OUTDIR		:= $(TOPDIR)/build
export TOPDIR OUTDIR

.PHONY: all chkconfig menuconfig flash probe erase clean distclean

-include .config

CPU = $(patsubst "%",%,$(CONFIG_CPU_CORE))

INC = .\
	$(APPDIR) \
	$(COREDIR) \
	$(BSPDIR)/sdk \
	$(BSPDIR)/sdk/CMSIS/Include \
	$(BSPDIR)/sdk/CMSIS/Device/ST/STM32F4xx/Include \
	$(BSPDIR)/sdk/STM32F4xx_StdPeriph_Driver/inc \
	$(BSPDIR)/boards \
	$(BSPDIR)/drivers

CORE = -mcpu=$(CPU) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

OPTIMIZATION = $(patsubst "%",%,$(CONFIG_CC_OPTIMIZATION_LEVEL)) \
	       $(patsubst "%",%,$(CONFIG_CC_DEBUG_LEVEL))

FLAGS = $(patsubst "%",%,$(CONFIG_CC_USE_PRINTF_FLOAT)) \
	$(patsubst "%",%,$(CONFIG_CC_USE_SCANF_FLOAT))

DEFINITIONS = $(patsubst "%",%,$(CONFIG_MCU_SERIES)) \
       USE_STDPERIPH_DRIVER \
       HSE_VALUE=$(CONFIG_MCU_HSE_CLOCK)

CFLAGS = $(CORE) \
	 $(FLAGS) \
	 $(OPTIMIZATION) \
	 $(addprefix -D,$(DEFINITIONS)) \
	 -std=$(patsubst "%",%,$(CONFIG_CC_C_STANDARD)) \
	 $(patsubst "%",%,$(CONFIG_CC_DATA_SECTIONS)) \
	 $(patsubst "%",%,$(CONFIG_CC_FUNCTION_SECTIONS)) \
	 $(patsubst "%",%,$(CONFIG_CC_STACK_USAGE)) \
	 $(patsubst "%",%,$(CONFIG_CC_WARNING_ALL)) \
	 $(patsubst "%",%,$(CONFIG_CC_WARNING_ERROR)) \
	 $(patsubst "%",%,$(CONFIG_CC_WARNING_EXTRA)) \
	 $(patsubst "%",%,$(CONFIG_CC_WARNING_NO_UNUSED_PARAMETER)) \
	 $(patsubst "%",%,$(CONFIG_CC_WARNING_SWITCH_DEFAULT)) \
	 $(patsubst "%",%,$(CONFIG_CC_WARNING_SWITCH_ENUM)) \
	 -fmessage-length=0 \
	 $(addprefix -I,$(INC))


ifeq ($(CONFIG_MCU_SERIES),STM32F40XX)
LDSCRIPT = $(LDDIR)/stm32f40xx.ld
endif

LDFLAGS = $(CORE) \
	$(OPTIMIZATION) \
	$(addprefix -T,$(LDSCRIPT)) \
	-Wl,-Map=$(OUTDIR)/$(PROJ_NAME).map,--cref \
	-Wl,--gc-section \
	-specs=nano.specs \
	-specs=nosys.specs
export CFLAGS LDFLAGS


obj-y += app/
obj-y += bsp/

OUT_HEX = $(OUTDIR)/$(PROJ_NAME).hex
OUT_BIN = $(OUTDIR)/$(PROJ_NAME).bin
OUT_ELF = $(OUTDIR)/$(PROJ_NAME).elf


all: chkconfig start_recursive_build $(OUT_HEX) $(OUT_BIN)
	@echo $(PROJ_NAME) has been built!

chkconfig:
	@test -f .config || (echo .conifg is not found; exit 1)

start_recursive_build:
	make -C ./ -f $(TOPDIR)/Makefile.build

$(OUT_HEX): $(OUT_ELF)
	@echo "Create hex file..." $(notdir $@)
	$(OBJCOPY) -O ihex --set-start 0x08000000 $< $@

$(OUT_BIN): $(OUT_ELF)
	@echo "Generating bin file..." $(notdir $@)
	$(OBJCOPY) -O binary -S $< $@

$(OUT_ELF): $(OUTDIR)/built-in.o
	$(CC) -o $@ $< $(LDFLAGS)
	$(SIZE) $@

menuconfig:
	@$(MAKE) -f scripts/Makefile $@

flash:
	sudo st-flash --reset write $(OUT_BIN) 0x08000000

probe:
	sudo st-info --probe

erase:
	sudo st-flash erase

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.su")
	rm -f $(OUTDIR)/$(PROJ_NAME).*

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.su")
	rm -f $(shell find -name "*.d")
	rm -rf $(OUTDIR)
	rm -f .config
	rm -f .config.old
	rm -f config.h

