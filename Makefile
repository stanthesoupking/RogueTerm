all: out

CC=g++
CFLAGS=-I$(IDIR) -std=c++11
LDIR=lib

IDIR =include
SRC=src
ODIR=object

LIBS=-lSDL2 -lstdc++ -lSDL2_image

INCLUDE = 
OBJS = main RogueTerm/RT_Font RogueTerm/RT_Window

FULL = $(OBJS)

DEPS = $(patsubst %,$(IDIR)/%.h,$(FULL))

CODE = $(patsubst %,$(SRC)/%.cpp,$(FULL))

OBJ = $(patsubst %,$(SRC)/%.o,$(FULL))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

out: $(CODE)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~