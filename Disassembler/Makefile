CC=g++

CFLAGS=-c -Wall -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
          -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
		  -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
		  -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op \
		  -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith \
		  -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits \
		  -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: Disassembler.exe


Disassembler.exe: Disassembler.o Disassembler_funcs.o
	$(CC) $^ -o $@

Disassembler_funcs.o: Disassembler_funcs.cpp Disassembler_funcs.h
	$(CC) $(CFLAGS) $<

Disassembler.o: Disassembler.cpp Disassembler_funcs.h
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf *.o Disassembler.exe
