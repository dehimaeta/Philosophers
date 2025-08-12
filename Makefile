NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(HDRS_DIR)

SRCS_DIR = sources/
HDRS_DIR = includes/

SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)datainit.c \
		$(SRCS_DIR)dinner.c \
		$(SRCS_DIR)get_set.c \
		$(SRCS_DIR)help_functions.c \
		$(SRCS_DIR)monitoring.c \
		$(SRCS_DIR)parsing.c \
		$(SRCS_DIR)synchro.c \
		$(SRCS_DIR)utils.c \
		$(SRCS_DIR)write.c \

HDRS = $(HDRS_DIR)philo.h

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re