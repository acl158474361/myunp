PROC = tcpcli01 tcpserv01 sigchldwait.o tcpcli04 sigchldwaitpid.o  tcpserv04

all:$(PROC)

%.o:%.c
	gcc -c -I../lib -o $@ $< 

%:%.c
	gcc -I../lib -o $@ $< -L../ -lunp

tcpserv01: tcpserv01.o sigchldwait.o
	gcc -o $@ tcpserv01.o sigchldwait.o -L../ -lunp

tcpserv04: tcpserv01.o sigchldwaitpid.o
	gcc -o $@ tcpserv01.o sigchldwaitpid.o  -L../ -lunp