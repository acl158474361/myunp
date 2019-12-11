PROGS = daytimetcpcli daytimetcpsrv

all: $(PROGS)

%:%.c
	gcc -I../lib -o $@ $< -L../ -lunp -lpthread