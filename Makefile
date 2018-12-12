TARGET=solitaire

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall -Werror

PTHREAD=-pthread
GTKCFLAGS=`pkg-config --cflags gtk+-3.0`
CFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) $(GTKCFLAGS) -pipe

GTKLIB=`pkg-config --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

SRCS:=main.c
SRCS+=gui.c
SRCS+=handler.c
SRCS+=game.c
OBJS:=$(SRCS:%.c=%.o)

ifeq ($(VERBOSE),1)
Q=
echo-cmd=
else
Q=@
echo-cmd=@echo $(1)
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(call echo-cmd, "  LD   $@")
	$(Q)$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(call echo-cmd, "  CC   $@")
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(call echo-cmd, "  CLEAN")
	$(Q)rm -f $(TARGET) $(OBJS)
