CC=gcc
CFLAGS=-Wall -std=c99 -g -DSILENT

# define targets
TARGETS=db

OBJ=main.o error.o list.o hashtable.o table.o item.o db.o load.o

build: $(TARGETS)

db: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr No_SQL_DB.zip Makefile README *.c *.h

clean:
	rm -f $(TARGETS)
	rm -f *.o

.PHONY: pack clean