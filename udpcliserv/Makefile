PROGS = udpcli01

all: $(PROGS)

%.o:%.c
	gcc -g -c -I../lib -o $@ $< 

%:%.c
	gcc -g -I../lib -o $@ $< -L../ -lunp