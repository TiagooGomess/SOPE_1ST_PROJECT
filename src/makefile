CC = gcc
CFLAGS = -Wall -g
OBJS = simpledu.o
HEADERS = simpledu.c #mudar pra .h depois
EXEC = simpledu

$(EXEC): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $@

%.o: %.c %.h $(HEADERS)
	@$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean:
	$-rm $(OBJS) $(EXEC)
