.POSIX:

OBJECTS = main.o

all: a.out

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

a.out: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o a.out

clean:
	rm -f a.out $(OBJECTS)

.PHONY: all clean
