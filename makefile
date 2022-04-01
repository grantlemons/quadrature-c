CC=gcc
CFLAGS=-I. -lm
DEPS=tinyexpr.c
OBJ=quadrature.c
NAME=quadrature

$(NAME): $(OBJ) $(DEPS)
	$(CC) $(OBJ) $(DEPS) -o $(NAME) $(CFLAGS)