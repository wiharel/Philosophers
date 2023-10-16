SRCS = src/actions.c src/exit.c \
		src/init.c src/main.c \
		src/routine.c src/utils.c

OBJS = ${SRCS:.c=.o}

NAME = philo

INC = ./include/

CC = gcc -Wall -Werror -Wextra -pthread

RM = rm -f

all: ${NAME}

.c.o:
	${CC} -I${INC} -c $< -o ${<:.c=.o}

$(NAME) : ${OBJS}
	${CC} ${OBJS} -I${INC} -o${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re