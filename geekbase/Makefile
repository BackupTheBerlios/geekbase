CC        = cc
CDEBUG    = -g3
WARN      = -Wall -Wstrict-prototypes -Wmissing-prototypes -Winline -Wshadow \
            -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings \
            -Waggregate-return -Winline -W -Wno-unused -Wsign-compare \
            -Wformat -Wformat-nonliteral -Wformat-security -Wpacked \
            -Wswitch -Wpadded -Wdisabled-optimization -Wno-shadow \
            -mno-accumulate-outgoing-args -ansi -pedantic
CFLAGS    = -D_GNU_SOURCE -DDEBUG
ifndef NODEBUG
CFLAGS += $(CDEBUG) $(WARN)
endif
LDFLAGS   = -shared -fPIC

LIB           = libgeekdb.so.0
LIBNAME       = $(subst lib,,$(basename $(basename $(LIB))))
LIB_SOURCES   = block.c blocklist.c buffer.c db.c field.c g_error.c \
		g_limits.c list.c table.c
LIB_OBJS      = $(LIB_SOURCES:.c=.o)

EXEC          = geekbase
EXEC_SOURCES  = main.c
EXEC_OBJS     = $(EXEC_SOURCES:.c=.o)

TEST          = g_test
TEST_SOURCES  = g_test.c
TEST_OBJS     = $(TEST_SOURCES:.c=.o)

SOURCES       = $(LIB_SOURCES) $(EXEC_SOURCES) $(TEST_SOURCES)
OBJS          = $(LIB_OBJS) $(EXEC_OBJS) $(TEST_OBJS)

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

test: $(LIB) $(TEST_OBJS)
	$(CC) -L. -l$(LIBNAME) $(TEST_OBJS) -o g_test

ifeq (,$(findstring clean,$(MAKECMDGOALS)))
.%.d: %.c
	echo Generating dependencies for $< ...
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

-include $(DEPS)
endif

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(LIB) $(basename $(LIB))
	$(RM) $(EXEC)
	$(RM) $(TEST)

install: all
	mkdir -p $(BINDIR) $(LIBDIR)
	cp $(EXEC) $(BINDIR)
	cp $(LIB) $(LIBDIR)
	cd $(LIBDIR); ln -sf $(LIB) $(basename $(LIB))

uninstall:
	$(RM) $(BINDIR)/$(EXEC)
	$(RM) $(LIBDIR)/$(LIB) $(LIBDIR)/$(basename $(LIB))

.PHONY: clean install uninstall exec_msg lib_msg
.SILENT: $(DEPS) exec_msg lib_msg
