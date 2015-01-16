CC	= gcc
CFLAGS	= -g -Wall -pedantic -std=c99 -Werror -lalpm
OUT	= pkgatime
OBJS	= main.o slist.o

.PHONY: clean main

main: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $(OBJS) $(CFLAGS)

c.o: c.c
	$(CC) $(CFLAGS) -c c.c

clean:
	rm -rf $(OUT) $(OBJS)

vg: $(OUT)
	valgrind --tool=memcheck ./$(OUT)
