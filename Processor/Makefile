CC=g++

CFLAGS=-c -Wall -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
          -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
		  -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
		  -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op \
		  -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith \
		  -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits \
		  -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: Processor.exe


Processor.exe: Processor.o Processor_funcs.o ../Stack.o ../Text_funcs.o
	$(CC) $^ -o $@

Processor_funcs.o: Processor_funcs.cpp Processor_funcs.h ../Commands.h ../Text_funcs.h ../Stack.h
	$(CC) $(CFLAGS) $<

Processor.o: Processor.cpp Processor_funcs.h
	$(CC) $(CFLAGS) $<

../Stack.o: ../Stack.cpp ../Stack.h
	$(CC) $(CFLAGS) -c $< -o $@

../Text_funcs.o: ../Text_funcs.cpp ../Text_funcs.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o Processor.exe
