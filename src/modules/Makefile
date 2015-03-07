COMPILER = gcc

OPTIONS = -fPIC -shared -std=gnu99 -Wall -Wshadow -Wpointer-arith -Wstrict-prototypes -Wconversion -Wcast-qual

SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.so)

modules: $(OBJECTS)

%.so: %.c
	$(COMPILER) $(OPTIONS) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
