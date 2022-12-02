# C project: ims_project
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -Iinclude
LDLIBS=-lncursesw
CFLAGS+=-O2 # Release
# CFLAGS+=-g  # Debug
TARGETS=ims_project1 ims_project2 ims_project3
OBJS=$(patsubst %.c,%.o,$(wildcard ./src/*.c))

#####################################

.PHONY: all run doc pack valgrind debug pixel_edit

all: $(TARGETS)

doc: Doxyfile
	doxygen

ims_project1: $(OBJS)
	$(CC) $(CFLAGS) -o $@ ./src/main.o ./src/board.o ./src/board_setup.o ./src/board_rule1.o $(LDLIBS);
ims_project2: $(OBJS)
	$(CC) $(CFLAGS) -o $@ ./src/main.o ./src/board.o ./src/board_setup.o ./src/board_rule2.o $(LDLIBS);
ims_project3: $(OBJS)
	$(CC) $(CFLAGS) -o $@ ./src/main.o ./src/board.o ./src/board_setup.o ./src/board_rule3.o $(LDLIBS);

src/%.o: src/%.c

pixel_edit:
	cd src && python pixel_editor.py

clean:
	rm -f $(TARGETS) ./src/*.o

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$<

debug: $(TARGET)
	gdb -tui ./$<

pack:
	rm -f 11_xdohna48_xdohun00.zip
	zip -r 11_xdohna48_xdohun00 Makefile ./src/*.c ./include/*.h docs/* README.md

