##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for robotfactory project
##

SRC     =       src/main.c				\
				src/generate_content.c	\
				src/read_content.c

OBJ     =       $(SRC:.c=.o)

NAME = amazed

all: $(NAME)

$(NAME):        $(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:     fclean  all

debug:
	gcc -g3 -o $(NAME) $(SRC) -L.


codingstyle:
	coding-style . .
	cat coding-style-reports.log
	rm -f coding-style-reports.log
