COMPILER = gcc

OPTIONS = -std=gnu99 -Wall -Wshadow -Wpointer-arith -Wstrict-prototypes -Wconversion -Wcast-qual

DEFINES = -DLOCALES_PATH='"$(locales_path)"'

SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = zws

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) -Wl,-export-dynamic -ldl $(OPTIONS) $(CFLAGS) $^ -o $@

%.o: %.c
	$(COMPILER) $(OPTIONS) $(DEFINES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
