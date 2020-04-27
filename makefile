IDIR =./
CC=gcc
CFLAGS=-I$(IDIR) -ggdb

ODIR=obj
#LDIR =../lib

LIBS=-lm 

_DEPS = pvd.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = pvd.o aux.o spherical.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#_EXTOBJ = gauss_legendre.o 
#EXTOBJ = $(patsubst %,$(ODIR)/%,$(_EXTOBJ))


$(ODIR)/%.o: %.c
		$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

#$(ODIR)/%.o: $(LDIR)/%.c
		$(CC) -c -o $@ $< $(CFLAGS)

#pvd: $(OBJ) $(EXTOBJ)
#		gcc -o $@ $^ $(CFLAGS) $(LIBS)

pvd: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ pvd 
