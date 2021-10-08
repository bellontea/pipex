NAME		=   pipex

HEADER  	=   pipex.h

LIBFT		=	./libft/libft.a

PATH_LIB	=	./libft/

SRCS_UTILS 	=   $(shell ls ./utils/*.c)

SRCS		=   ${SRCS_UTILS} pipex.c

CFLAGS		=	

RM			=	rm -rf

CC			=   gcc

OBJS		=	$(SRCS:%.c=%.o)

.PHONY:		all clean fclean re ${NAME} run_libft

all:		run_libft $(NAME)

$(NAME):	${OBJS} $(HEADER) $(LIBFT)
			$(CC) -o $(NAME) ${OBJS} $(LIBFT)

run_libft:	
			@make -C $(PATH_LIB)

%.o: 		%.c	
			$(CC) $(CFLAGS) -I./ -I./libft/ -c $< -o $@

clean:
			$(RM) ${OBJS}
			@make -C $(PATH_LIB) clean

fclean:		clean
			$(RM) $(NAME)
			@make -C $(PATH_LIB) fclean

re:			fclean all
