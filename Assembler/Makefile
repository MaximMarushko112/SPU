CC=g++

CFLAGS=-c -Wall -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
          -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
		  -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
		  -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op \
		  -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith \
		  -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits \
		  -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: Assembler.exe


Assembler.exe: Assembler.o Assembler_funcs.o
	$(CC) $^ -o $@

Assembler_funcs.o: Assembler_funcs.cpp Assembler_funcs.h
	$(CC) $(CFLAGS) $<

Assembler.o: Assembler.cpp Assembler_funcs.h
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf *.o Assembler.exe
