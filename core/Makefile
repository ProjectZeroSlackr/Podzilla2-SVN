ifdef IPOD
CROSS ?= arm-uclinux-elf
CC = $(CROSS)-gcc
LD = $(CROSS)-ld
MYCFLAGS = -O3 -fomit-frame-pointer -funroll-loops `$(TTKCONF) --ipod --sdl --cflags` -I../contrib/ucdl -mapcs -mcpu=arm7tdmi -DVERSION=\"$(VERSION)\" -Wall
else
CC ?= cc
LD ?= ld
MYCFLAGS = -g `$(TTKCONF) --x11 --sdl --cflags` -DVERSION=\"$(VERSION)\" -Wall
endif
MYCFLAGS += -I/sw/include

ifdef SANSA
MYCFLAGS += -DSANSA
endif

OBJS= pz.o module.o ipod.o dialog.o header.o settings.o fonts.o \
      menu.o legacy.o gui.o browser.o vector.o oss.o appearance.o input.o \
      priority.o icons.o menuconf.o
HDRS= pz.h

all: built-in.o

built-in.o: $(OBJS)
	@echo " LD      built-in.o"
	@$(LD) $(LDFLAGS) -r -o built-in.o $(OBJS)

$(OBJS): $(HDRS)

%.o: %.c
	@echo " CC     " $@
	@$(CC) $(CFLAGS) $(MYCFLAGS) -c -o $@ $<

clean:
	@rm -f *.o

.PHONY: clean all
