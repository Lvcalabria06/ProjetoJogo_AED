CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/menu.c src/jogo.c src/estrutura.c src/ordenacao.c src/api.c
OBJ = $(SRC:.c=.o)
EXEC = meu_jogo

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
