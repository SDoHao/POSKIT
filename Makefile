srcs=main.c cmd.c file.c trim.c
objs=$(srcs:%.c=%.o)
cflags=-O3 -Wall -Wextra -I .
ldflags=
cc=gcc

all: main.exe

main.exe:$(objs)
	$(cc) $^  -o $@ $(ldflags)

%.o: %.c
	gcc $(cflags) -c $< -o $@

sinclude $(srcs:.c=.d)

%.d: %.c
	gcc -MM $(cflags) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean run

run: main.exe 
	./main.exe

clean:
	find . '(' -name "*.o" -or -name "*.d" -or -name "*.exe" ')' -delete