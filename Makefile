NAME		=   pipex

HEADER  	=   pipex.h

LIBFT		=	./libft/libft.a

PATH_LIB	=	./libft/

SRCS_UTILS 	=   $(shell ls ./utils/*.c)

SRCS_GNL	=	$(shell ls ./gnl/*.c)

SRCS		=   ${SRCS_UTILS} ${SRCS_GNL} pipex.c

CFLAGS		=	#-Wall -Wextra -Werror

RM			=	rm -rf

CC			=   gcc

OBJS		=	$(SRCS:%.c=%.o)

.PHONY:		all clean fclean re run_libft

all:		run_libft $(NAME)

$(NAME):	${OBJS} $(HEADER) $(LIBFT)
			$(CC) -o $(NAME) ${OBJS} $(LIBFT)

run_libft:	
			@make -C $(PATH_LIB)

%.o: 		%.c	
			$(CC) $(CFLAGS) -I./ -I./libft/ -I./gnl/ -c $< -o $@

clean:
			$(RM) ${OBJS}
			@make -C $(PATH_LIB) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(PATH_LIB) fclean

re:			fclean all
