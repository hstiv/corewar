# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 00:32:42 by ubyrd             #+#    #+#              #
#    Updated: 2019/07/31 11:43:19 by ubyrd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN				=	\x1B[32m
MAG				=	\x1B[35m
RES				=	\x1B[0m


NAME1			=	asm
NAME2			=	corewar

# ASM
SRC1_PATH		=	srcs/asm/
OBJ1_PATH		=	srcs/asm/obj/
INC1_PATH		=	includes/asm/
# COREWAR
SRC2_PATH		=	srcs/corewar/
OBJ2_PATH		=	srcs/corewar/obj/
INC2_PATH		=	includes/corewar/
# LIBFT
LIB_PATH		=	libft/
LIB_INC_PATH	=	libft/includes/

# ASM
SRC1_NAME		=	main.c g_op_tab.c utils.c utils2.c handling_header.c \
					handling_label.c handling_args.c handling_op.c output_file.c
OBJ1_NAME		=	$(SRC1_NAME:.c=.o)
INC1_NAME		=	op.h asm.h asm_strings.h
# COREWAR
SRC2_NAME		=	main.c arena.c args_check.c check_live.c cor_sort.c game.c \
					init_mlx_args.c key_hooks.c mouse_press.c new_vm.c op.c \
					op1.c op2.c op3.c op4.c parse_champs.c parser.c \
					rec_utils.c run_window.c utils.c utils1.c valid_args.c
OBJ2_NAME		=	$(SRC2_NAME:.c=.o)
INC2_NAME		=	op.h corvm.h
# LIBFT
LIB_NAME		=	libft.a
LIB_INC_NAME	=	libft.h

# ASM
OBJ1			=	$(addprefix $(OBJ1_PATH), $(OBJ1_NAME))
INC1			=	$(addprefix $(INC1_PATH), $(INC1_NAME))
# COREWAR
OBJ2			=	$(addprefix $(OBJ2_PATH), $(OBJ2_NAME))
INC2			=	$(addprefix $(INC2_PATH), $(INC2_NAME))
# LIBFT
LIB				=	$(addprefix $(LIB_PATH), $(LIB_NAME))
LIB_INC			=	$(addprefix $(LIB_INC_PATH), $(LIB_INC_NAME))

.PHONY:				all $(LIB_NAME) clean fclean re


all:				$(LIB_NAME) $(NAME1) $(NAME2)

# LIBFT
$(LIB_NAME):
					@make -C $(LIB_PATH)
# ASM
$(NAME1):			$(LIB) $(OBJ1)
					@gcc -Wall -Wextra -Werror $(OBJ1) \
						-L $(LIB_PATH) -lft -o $(NAME1)
					@echo "$(GRN)\nLinking [ $(NAME1) ] SUCCESS$(RES)"
# COREWAR
$(NAME2):			$(LIB) $(OBJ2)
					@gcc -Wall -Wextra -Werror $(OBJ2) \
						-lmlx -framework OpenGL -framework AppKit -lm \
						-L $(LIB_PATH) -lft -o $(NAME2)
					@echo "$(GRN)\nLinking [ $(NAME2) ] SUCCESS$(RES)"

# LIBFT
$(LIB):				$(LIB_NAME)
# ASM
$(OBJ1_PATH)%.o:	$(SRC1_PATH)%.c $(INC1) $(LIB_INC)
					@mkdir -p $(OBJ1_PATH)
					@gcc -Wall -Wextra -Wextra \
						-I $(INC1_PATH) -I $(LIB_INC_PATH) -o $@ -c $<
					@echo ".\c"
# COREWAR
$(OBJ2_PATH)%.o:	$(SRC2_PATH)%.c $(INC2) $(LIB_INC)
					@mkdir -p $(OBJ2_PATH)
					@gcc -Wall -Wextra -Wextra \
						-I $(INC2_PATH) -I $(LIB_INC_PATH) -o $@ -c $<
					@echo ".\c"


clean:
					@make -C $(LIB_PATH) fclean
					@rm -f $(OBJ1) $(OBJ2)
					@rm -rf $(OBJ_PATH1) $(OBJ_PATH2)
					@echo "$(MAG)Cleaning [ $(NAME1) ] OK$(RES)"
					@echo "$(MAG)Cleaning [ $(NAME2) ] OK$(RES)"

fclean:				clean
					@rm -f $(NAME1) $(NAME2)
					@echo "$(MAG)Delete [ $(NAME1) ] OK$(RES)"
					@echo "$(MAG)Delete [ $(NAME2) ] OK$(RES)"

re:					fclean all
