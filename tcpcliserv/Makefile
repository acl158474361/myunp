PROC = tcpcli01 tcpserv01 sigchldwait.o tcpcli04 sigchldwaitpid.o  tcpserv04 tcpserv03 tcpserv08 strcli.o tcpservselect01\
	tcpservpoll01

all:$(PROC)

%.o:%.c
	gcc -g -c -I../lib -o $@ $< 

%:%.c
	gcc -g -I../lib -o $@ $< -L../ -lunp

tcpcli01: tcpcli01.o strcli.o
	gcc -g -o $@ tcpcli01.o strcli.o -L../ -lunp

tcpserv03: tcpserv03.o sigchldwait.o
	gcc -g -o $@ tcpserv03.o sigchldwait.o -L../ -lunp

tcpserv04: tcpserv04.o sigchldwaitpid.o
	gcc -g -o $@ tcpserv04.o sigchldwaitpid.o  -L../ -lunp

tcpserv08: tcpserv08.o sigchldwaitpid.o
	gcc -g -o $@ tcpserv08.o sigchldwaitpid.o  -L../ -lunp

.PHONY:clean

clean:
	rm $(PROC) tcpserv03.o tcpserv04.o