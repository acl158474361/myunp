PROGS = udpcli01 echo.o udpcli02 udpserv01

all: $(PROGS)

%.o:%.c
	gcc -g -c -I../lib -o $@ $< 

%:%.c
	gcc -g -I../lib -o $@ $< -L../ -lunp

udpcli02: udpcli02.o echo.o
	gcc -o $@ udpcli02.o echo.o -L../ -lunp

udpserv01: udpserv01.o echo.o
	gcc -o $@ udpserv01.o echo.o -L../ -lunp