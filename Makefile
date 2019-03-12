CC = g++
CFLAGS = -Wall -I$(IDIR)

IDIR = include
LDIR = lib
ODIR = obj
SRCDIR = src
TESTDIR = tests
BINDIR = bin

LIBS =

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(ODIR)/%.o,$(SRCFILES))

EXEC_NAME = CTron

all: $(BINDIR)/$(EXEC_NAME)

$(BINDIR)/$(EXEC_NAME): $(OBJFILES)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(ODIR) $(BINDIR)