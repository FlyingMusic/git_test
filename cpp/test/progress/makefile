PROG=check_process
OBJS=process.o main.o
#CFLAGS = -g -ggdb

all:$(PROG)

check_process:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm -rf $(PROG) *.o
