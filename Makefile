CC := gcc
CFLAGS := -O3
OUTFILE := mmb
all: mmb

mmb: mmb.c
	$(CC) $(CFLAGS) mmb.c -o $(OUTFILE)
