PROC = checkopts

all:$(PROC)

%.o:%.c
	gcc -g -c -I../lib -o $@ $< 

%:%.c
	gcc -g -I../lib -o $@ $< -L../ -lunp
