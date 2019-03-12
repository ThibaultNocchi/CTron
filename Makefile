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

%Test: $(ODIR)/%Test.o
	mkdir -p $(BINDIR)/$(TESTDIR)
	$(CC) -o $(BINDIR)/$(TESTDIR)/$@ $^ $(CFLAGS) $(LIBS)
	@echo "Start of test...\n"
	@$(BINDIR)/$(TESTDIR)/./$@
	@echo "\nEnd of test."

$(BINDIR)/$(EXEC_NAME): $(OBJFILES)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%Test.o: $(TESTDIR)/%Test.cpp
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PRECIOUS: $(ODIR)/%Test.o

$(ODIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(ODIR) $(BINDIR)