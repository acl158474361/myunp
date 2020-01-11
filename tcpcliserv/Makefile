PROC = tcpcli01 tcpserv01 sigchldwait.o tcpcli04 sigchldwaitpid.o  tcpserv04 tcpserv03

all:$(PROC)

%.o:%.c
	gcc -g -c -I../lib -o $@ $< 

%:%.c
	gcc -g -I../lib -o $@ $< -L../ -lunp

tcpserv03: tcpserv03.o sigchldwait.o
	gcc -g -o $@ tcpserv03.o sigchldwait.o -L../ -lunp

tcpserv04: tcpserv04.o sigchldwaitpid.o
	gcc -g -o $@ tcpserv04.o sigchldwaitpid.o  -L../ -lunp

.PHONY:clean

clean:
	rm $(PROC) tcpserv03.o tcpserv04.o