CC        = cc
CDEBUG    = -ggdb
WARN      = -Wall -Wstrict-prototypes -Wmissing-prototypes -Winline -Wshadow \
            -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings \
            -Waggregate-return -Winline -W -Wno-unused -Wsign-compare \
            -Wformat -Wformat-nonliteral -Wformat-security -Wpacked \
            -Wswitch -Wpadded \
            -Wdisabled-optimization -mno-accumulate-outgoing-args -Wno-shadow \
            -ansi -pedantic
CFLAGS    = -march=i686 -pipe $(CDEBUG) $(WARN)
LDFLAGS   = -shared -fPIC

LIB           = libgeekdb.so.0
LIBNAME       = $(subst lib,,$(basename $(basename $(LIB))))
LIB_SOURCES   = block.c blocklist.c buffer.c cell.c db.c field.c g_error.c table.c
LIB_OBJS      = $(LIB_SOURCES:.c=.o)

EXEC          = geekbase
EXEC_SOURCES  = main.c
EXEC_OBJS     = $(EXEC_SOURCES:.c=.o)

SOURCES       = $(LIB_SOURCES) $(EXEC_SOURCES)
OBJS          = $(LIB_OBJS) $(EXEC_OBJS)

DEPS          = $(addprefix .,$(SOURCES:.c=.d))

DESTDIR	= /usr/local
BINDIR	= $(DESTDIR)/bin
LIBDIR	= $(DESTDIR)/lib

all: $(EXEC)

$(EXEC): $(LIB) $(EXEC_OBJS)
	$(CC) -L. -l$(LIBNAME) $(EXEC_OBJS) -o $@

$(LIB): $(LIB_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@
	ln -sf $@ $(basename $@)

.%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(LIB) $(basename $(LIB)) $(EXEC)

install: all
	mkdir -p $(BINDIR) $(LIBDIR)
	cp $(EXEC) $(BINDIR)
	cp $(LIB) $(LIBDIR)
	cd $(LIBDIR); ln -sf $(LIB) $(basename $(LIB))

uninstall:
	rm -f $(BINDIR)/$(EXEC)
	rm -f $(LIBDIR)/$(LIB) $(LIBDIR)/$(basename $(LIB))

.PHONY: clean install uninstall
