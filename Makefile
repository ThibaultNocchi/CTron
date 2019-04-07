CC = g++
CFLAGS = -Wall -I$(IDIR) -std=c++14 -O3

IDIR = include
LDIR = lib
ODIR = obj
SRCDIR = src
TESTDIR = tests
BINDIR = bin

LIBS = -fopenmp

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(ODIR)/%.o,$(SRCFILES))
MAINFILE = main

EXEC_NAME = CTron

GAMES_TO_RUN = 5

all: $(BINDIR)/$(EXEC_NAME)

run: $(BINDIR)/$(EXEC_NAME)
	@$(BINDIR)/./$(EXEC_NAME) $(GAMES_TO_RUN)

%Test: $(ODIR)/%Test.o $(OBJFILES)
	mkdir -p $(BINDIR)/$(TESTDIR)
	$(CC) -o $(BINDIR)/$(TESTDIR)/$@ $(filter-out $(ODIR)/$(MAINFILE).o, $^) $(CFLAGS) $(LIBS)
	@echo "Start of tests...\n"
	@$(BINDIR)/$(TESTDIR)/./$@
	@echo "\nTests successful!"

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
