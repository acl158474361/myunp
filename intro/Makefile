PROGS = daytimetcpcli daytimetcpserv


all: $(PROGS)
%:%.c
	gcc -I../lib -o $@ $< -L../ -lunp -lpthread