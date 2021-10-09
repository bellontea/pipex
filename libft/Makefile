NAME	=	libft.a

HEADER	=	libft.h

SRCS	=   $(shell ls ./*.c)

CFLAGS	=	-Wall -Wextra -Werror

CC		=   gcc

OBJS	=	$(SRCS:%.c=%.o)

LIBC	=	ar rc

LIBR	=	ranlib

RM		=	rm -rf


all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			$(LIBC) $(NAME) $(OBJS)
			$(LIBR) $(NAME)

%.o: 		%.c	
			$(CC) $(CFLAGS) -I./ -c $< -o $@

clean:	
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re 