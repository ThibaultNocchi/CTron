CC = g++
CFLAGS = -Wall
EXEC_NAME = CTron

OBJ_FILES = Snake.o main.o Grid.o

all : $(EXEC_NAME)

clean : rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
