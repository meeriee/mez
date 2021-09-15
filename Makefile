include config.mk

CC ?= gcc
CFLAGS += -fPIC -Wall -Wextra -Wshadow -Wcast-align -Wunused -Wpedantic -Wnull-dereference -Wformat=2 -march=native -I"src/"
ifndef DEBUG
	ADDITIONAL_CFLAGS ?= -O3
	SANITIZERS =
else
	ADDITIONAL_CFLAGS ?= -Og -g3
	SANITIZERS = -fsanitize=address,undefined
endif

CFLAGS += $(ADDITIONAL_CFLAGS) $(SANITIZERS)
LDFLAGS += -pthread $(SANITIZERS) -lm -lGL -lGLEW -lglfw -lpng 

RM ?= rm -f

SRC ?= src
OBJ ?= .obj

SRCS += $(wildcard $(SRC)/*.c)
SRCS += $(wildcard $(SRC)/ui/*.c) 
SRCS += $(wildcard $(SRC)/ui/render/*.c) 
SRCS += $(wildcard $(SRC)/util/*.c)
SRCS += $(wildcard $(SRC)/math/*.c)

OBJS += $(patsubst $(SRC)/%.c,$(OBJ)/src/%.o,$(SRCS))

all: options mez

options:
	@echo mez build options:
	@echo "CC          = $(CC)"
	@echo "CFLAGS      = $(CFLAGS)"
	@echo "LDFLAGS     = $(LDFLAGS)"

$(OBJ)/%.o: %.c
	test -f $@ || mkdir -p $@ && rm -r $@ 
	$(CC) -c $(CFLAGS) $< -o $@

mez: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) mez
