# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:46:54 by artuda-s          #+#    #+#              #
#    Updated: 2024/06/23 19:45:40 by artuda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = gcc
CFLAGS = -Wextra -Wall -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
    ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
    ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
    ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
    ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
    ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
    ft_strrchr.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_substr.c \
    ft_atoi_base.c get_next_line.c ft_printf.c ft_printf_chars.c \
    ft_printf_putptr.c ft_printf_putnum_base.c ft_append_char_to_str.c


SRCS_BONUS = 	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
    ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = libft.a
DEPS = libft.h ft_printf.h


.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)
