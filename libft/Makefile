# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/12 18:42:33 by ubyrd             #+#    #+#              #
#    Updated: 2019/07/15 23:03:59 by ubyrd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN			=	\x1B[32m
MAG			=	\x1B[35m
RES			=	\x1B[0m


NAME		=	libft.a

SRC_PATH	=	srcs/
OBJ_PATH	=	srcs/obj/
INC_PATH	=	includes/
PRINTF_PATH	=	ft_printf/

SRC_NAME	=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c	ft_strlen.c ft_strdup.c ft_strcpy.c \
				ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
				ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
				ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_toupper.c ft_tolower.c \
				\
				ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
				ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
				ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
				ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				\
				ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
				ft_lstmap.c \
				\
				ft_abs.c ft_factorial.c ft_power.c ft_sqrt.c ft_atoi_base.c \
				ft_itoa_base.c ft_gcd.c ft_nextprime.c \
				\
				ft_btree_create_node.c ft_btree_delone.c ft_btree_apply_prefix.c \
				ft_btree_apply_infix.c ft_btree_apply_suffix.c \
				\
				ft_memswap.c ft_qsort.c \
				\
				ft_putwchar.c ft_putwstr.c ft_putwchar_fd.c ft_putwstr_fd.c \
				ft_wcharlen.c ft_wstrlen.c \
				\
				get_next_line.c
OBJ_NAME	=	$(SRC_NAME:.c=.o)
INC_NAME	=	libft.h get_next_line.h
PRINTF_NAME	=	libftprintf.a

SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC			=	$(addprefix $(INC_PATH), $(INC_NAME))
PRINTF		=	$(addprefix $(PRINTF_PATH), $(PRINTF_NAME))

.PHONY:			all $(PRINTF_NAME) clean fclean re


all:			$(PRINTF_NAME) $(NAME)

$(PRINTF_NAME):
				@make -C $(PRINTF_PATH)

$(NAME):		$(PRINTF) $(OBJ)
				@cp $(PRINTF) $(NAME)
				@ar rc $(NAME) $(OBJ)
				@ranlib $(NAME)
				@echo "$(GRN)\nLinking & indexing [ $(NAME) ] SUCCESS$(RES)"

$(PRINTF):		$(PRINTF_NAME)

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c $(INC)
				@mkdir -p $(OBJ_PATH)
				@gcc -Wall -Wextra -Werror -I $(INC_PATH) -o $@ -c $<
				@echo ".\c"

clean:
				@make fclean -C $(PRINTF_PATH)
				@rm -f $(OBJ)
				@rm -rf $(OBJ_PATH)
				@echo "$(MAG)Cleaning [ $(NAME) ] OK$(RES)"

fclean:			clean
				@rm -f $(NAME)
				@echo "$(MAG)Delete [ $(NAME) ] OK$(RES)"

re:				fclean all
