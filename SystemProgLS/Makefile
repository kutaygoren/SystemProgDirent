CC   = gcc
OBJ=160101003.o
CFLAGS = -c
SOURCES= 160101003.c
BIN  = vals
RM = rm -f

all: obj

derle:
	$(CC) $(CFLAGS) $(SOURCES)

obj: derle
	$(CC) $(OBJ) -o $(BIN)

calistir: derle
	./$(BIN) testFolder
	./$(BIN) B
	./$(BIN) -r .
	./$(BIN) out.txt testFolder
	./$(BIN) -d testFolder
	./$(BIN) -d B

val: derle
	valgrind --leak-check=yes ./$(BIN) testFolder
	valgrind --leak-check=yes ./$(BIN) -r testFolder
	valgrind --leak-check=yes ./$(BIN) out.txt testFolder
	valgrind --leak-check=yes ./$(BIN) -d testFolder

clean:
	${RM} $(OBJ) $(BIN)
