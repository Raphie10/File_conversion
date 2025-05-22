##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for robotfactory project
##

SRC     =       src/main.c					\
				src/generate_content.c		\
				src/read_bitmap_content.c	\
				src/generate_png_file.c		\
				src/get_crc.c				\
				src/modify_file.c			\
				src/write_bitmap_file.c		\
				src/write_png_file.c		\
				src/convert_bitmap_to_png.c	\
				

OBJ     =       $(SRC:.c=.o)

NAME = file_converter

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
