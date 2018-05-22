IDIR=../include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib

CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags glib-2.0` -I$(IDIR)

excludes=interfaceTESTE.c

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(filter-out $(interfaceTESTE.c),$(wildcard *.c))
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)
LIBS = `pkg-config --libs glib-2.0`

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program

doxy:
	doxygen doxy
