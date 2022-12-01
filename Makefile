# C project: ims_project
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -Iinclude
LDLIBS=-lncursesw
# CFLAGS+=-O2 # Release
CFLAGS+=-g  # Debug
TARGET=ims_project
OBJS=$(patsubst %.c,%.o,$(wildcard ./src/*.c))

#####################################

.PHONY: all run doc pack valgrind debug pixel_edit

all: $(TARGET)

run: $(TARGET)
	./$<

doc: Doxyfile
	doxygen

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

pixel_edit:
	cd src && python pixel_editor.py

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$<

debug: $(TARGET)
	gdb -tui ./$<

pack:
	rm -f ims_project.zip
	zip ims_project Makefile *.c *.h

