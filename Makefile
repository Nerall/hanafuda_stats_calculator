# Makefile

DEBUG_FLAGS = -O0 -g -fsanitize=address
RELEASE_FLAGS = -O0 -DNGDEBUG

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 ${DEBUG_FLAGS}

EXE := hanafuda_stats_calculator
SRC := $(wildcard src/*.c)
OBJ := ${SRC:.c=.o}
DEP := ${SRC:.c=.d}

%.o: %.c
	@echo "Compiling: $<"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

all: pretty_message ${EXE}

${EXE}: ${OBJ}
	@echo "Linking: ${EXE}"
	@${CC} ${CFLAGS} ${OBJ} -o ${EXE}

pretty_message:
	@echo "Target: \"${EXE}\""
	@echo "CC    : ${CC}"
	@echo "FLAGS : ${CPPFLAGS} ${CFLAGS}"
	@echo

clean:
	@echo "Removing .o files"
	@${RM} ${OBJ}

	@echo "Removing .d files"
	@${RM} ${DEP}

	@echo "Removing executable"
	@${RM} ${EXE}

	@echo

-include ${DEP}
