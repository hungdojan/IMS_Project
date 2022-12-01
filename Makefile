# C project: ims_project
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -Iinclude
LDLIBS=-lncursesw
# CFLAGS+=-O2 # Release
CFLAGS+=-g  # Debug
TARGET=ims_project
OBJS=$(patsubst %.c,%.o,$(wildcard ./src/*.c))

#####################################

.PHONY: all run doc pack valgrind debug update_board

all: $(TARGET)

run: $(TARGET)
	./$<

doc: Doxyfile
	doxygen

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

update_board:
	cp ./src/board_setup.c ./pixel_editor/backup.c
	cp ./pixel_editor/board_setup.c ./src/board_setup.c

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$<

debug: $(TARGET)
	gdb -tui ./$<

pack:
	rm -f ims_project.zip
	zip ims_project Makefile *.c *.h

