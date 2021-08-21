# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmeiboom <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/27 21:14:05 by rmeiboom      #+#    #+#                  #
#    Updated: 2021/05/30 21:13:03 by rmeiboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS = -Wall -Werror -Wextra -ggdb3
NAME = libft.a
BASIC_OBJ_FILES = 	ft_toupper.o\
					ft_tolower.o\
					ft_isalpha.o\
					ft_isdigit.o\
					ft_isalnum.o\
					ft_isascii.o\
					ft_isprint.o\
					ft_memset.o\
					ft_memcpy.o\
					ft_memccpy.o\
					ft_memmove.o\
					ft_memchr.o\
					ft_memcmp.o\
					ft_bzero.o\
					ft_calloc.o\
					ft_strdup.o\
					ft_strlen.o\
					ft_strlcpy.o\
					ft_strlcat.o\
					ft_strchr.o\
					ft_strrchr.o\
					ft_strncmp.o\
					ft_strnstr.o\
					ft_atoi.o\
					ft_atof.o\
					ft_substr.o\
					ft_strjoin.o\
					ft_strtrim.o\
					ft_split.o\
					ft_putchar_fd.o\
					ft_putstr_fd.o\
					ft_putendl_fd.o\
					ft_putnbr_fd.o\
					ft_strmapi.o\
					ft_itoa.o\
					ft_lstnew.o\
					ft_lstadd_front.o\
					ft_lstsize.o\
					ft_lstlast.o\
					ft_lstadd_back.o\
					ft_lstdelone.o\
					ft_lstclear.o\
					ft_dbllst.o

HEADERS = libft.h

ifdef WITH_BONUS
O_FILES = $(BASIC_OBJ_FILES) $(BONUS_OBJ_FILES)
else
O_FILES = $(BASIC_OBJ_FILES)
endif

all: $(NAME)

$(NAME): $(O_FILES)
	ar rc $@ $^
	ranlib $@

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(BASIC_OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
