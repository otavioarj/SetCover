CFLAGS =   -g  
CC = gcc
PROG = main
PROGS = main.c algorithm.c  generate_tad.c  
RM = /bin/rm -f 
OBJS = main.o algorithm.o  generate_tad.o 

all:clean $(PROG) 

$(PROG):main.c
	$(CC) $(CFLAGS) -c $(PROGS) 
	$(CC) $(OBJS) -o $(PROG) 
	$(RM) *.o

clean:
	$(RM) $(PROG)
	$(RM) *.o

