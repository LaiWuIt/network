target = server
ctarget = client
src = $(wildcard ./*.c)
obj = $(patsubst ./%.c, ./%.o, $(src))
CC=gcc
CPPFLAGS=-I
$(target): $(obj)
	$(CC) $(obj) -o $(target) -Wall

%.o: %.c
	$(CC) -c $< -o $@
	
.PHONY: clean
clean:
	-rm $(obj) $(target) -f




