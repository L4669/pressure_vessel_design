IDIR =./
CC=gcc
CFLAGS=-I$(IDIR) -ggdb

ODIR=obj

LIBS=-lm 

_DEPS = pvd.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = pvd.o aux.o spherical.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
		$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

pvd: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ pvd 
