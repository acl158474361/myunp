PROC = tcpcli01 tcpserv01 sigchldwait.o

all:$(PROC)

%.o:%.c
	gcc -c -I../lib -o $@ $< 

%:%.c
	gcc -I../lib -o $@ $< -L../ -lunp

tcpserv01: tcpserv01.o sigchldwait.o
	gcc -o $@ tcpserv01.o sigchldwait.o -L../ -lunp