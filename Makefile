NAME		=   pipex

HEADER  	=   pipex.h

LIBFT		=	./libft/libft.a

PATH_LIB	=	./libft/

PATH_BONUS	=	./bonus

SRCS_UTILS 	=   $(shell ls ./utils/*.c)

SRCS_GNL	=	$(shell ls ./gnl/*.c)

SRCS		=   ${SRCS_UTILS} ${SRCS_GNL} pipex.c

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

CC			=   gcc

OBJS		=	$(SRCS:%.c=%.o)

.PHONY:		all clean fclean re run_libft bonus

all:		run_libft $(NAME)

$(NAME):	${OBJS} $(HEADER) $(LIBFT)
			$(CC) -o $(NAME) ${OBJS} $(LIBFT)

bonus:		
			@make -C $(PATH_BONUS)

run_libft:	
			@make -C $(PATH_LIB)

%.o: 		%.c	
			$(CC) $(CFLAGS) -I./ -I./libft/ -I./gnl/ -c $< -o $@

clean:
			$(RM) ${OBJS}
			@make -C $(PATH_LIB) clean
			@make -C $(PATH_BONUS) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(PATH_LIB) fclean
			@make -C $(PATH_BONUS) fclean

re:			fclean all
