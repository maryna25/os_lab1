CC					:= gcc

RM					:= rm -rf

LDFLAGS			+= -Llib

CFLAGS			+= -Iinclude

LOG_FILES		:= $(wildcard *.log)

SRCS				:= $(wildcard src/*.c)

SRCS_TEST1	:= $(wildcard src/fork.c src/manager.c src/main.c src/function.c src/read.c src/tools.c test/init_test1.c)

SRCS_TEST2	:= $(wildcard src/fork.c src/manager.c src/main.c src/function.c src/read.c src/tools.c test/init_test2.c)

SRCS_TEST3	:= $(wildcard src/fork.c src/manager.c src/main.c src/function.c src/read.c src/tools.c test/init_test3.c)

SRCS_TEST4	:= $(wildcard src/fork.c src/manager.c src/main.c src/function.c src/read.c src/tools.c test/init_test4.c)

SRCS_TEST5	:= $(wildcard src/fork.c src/manager.c src/main.c src/function.c src/read.c src/tools.c test/init_test5.c)

SRCS_TEST6	:= $(wildcard src/fork.c src/manager.c src/main.c src/function.c src/read.c src/tools.c test/init_test6.c)

OBJS				:= $(SRCS:.c=.o)

OBJS_TEST1  := $(SRCS_TEST1:.c=.o)

OBJS_TEST2  := $(SRCS_TEST2:.c=.o)

OBJS_TEST3  := $(SRCS_TEST3:.c=.o)

OBJS_TEST4  := $(SRCS_TEST4:.c=.o)

OBJS_TEST5  := $(SRCS_TEST5:.c=.o)

OBJS_TEST6  := $(SRCS_TEST6:.c=.o)

NAME				:= lab1

NAME_TEST1   := lab1_test1

NAME_TEST2   := lab1_test2

NAME_TEST3   := lab1_test3

NAME_TEST4   := lab1_test4

NAME_TEST5   := lab1_test5

NAME_TEST6   := lab1_test6

all:				$(NAME)

$(NAME):		$(OBJS)
						$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) -lm

$(NAME_TEST1):	$(OBJS_TEST1)
								$(CC) -o $(NAME_TEST1) $(OBJS_TEST1) $(LDFLAGS) -lm

$(NAME_TEST2):	$(OBJS_TEST2)
								$(CC) -o $(NAME_TEST2) $(OBJS_TEST2) $(LDFLAGS) -lm

$(NAME_TEST3):	$(OBJS_TEST3)
								$(CC) -o $(NAME_TEST3) $(OBJS_TEST3) $(LDFLAGS) -lm

$(NAME_TEST4):	$(OBJS_TEST4)
								$(CC) -o $(NAME_TEST4) $(OBJS_TEST4) $(LDFLAGS) -lm

$(NAME_TEST5):	$(OBJS_TEST5)
								$(CC) -o $(NAME_TEST5) $(OBJS_TEST5) $(LDFLAGS) -lm

$(NAME_TEST6):	$(OBJS_TEST6)
								$(CC) -o $(NAME_TEST6) $(OBJS_TEST6) $(LDFLAGS) -lm

clean:
						$(RM) $(OBJS) $(OBJS_TEST1) $(OBJS_TEST2) $(OBJS_TEST3) $(OBJS_TEST4) $(OBJS_TEST5) $(OBJS_TEST6) $(LOG_FILES)

fclean: 		clean
						$(RM) $(NAME_TEST1) $(NAME_TEST2) $(NAME_TEST3) $(NAME_TEST4) $(NAME_TEST5) $(NAME_TEST6) $(NAME)

re: 				fclean all

test:				re
						@(./$(NAME))

test1:			fclean $(NAME_TEST1)
						@(./$(NAME_TEST1))

test2:			fclean $(NAME_TEST2)
						@(./$(NAME_TEST2))

test3:			fclean $(NAME_TEST3)
						@(./$(NAME_TEST3))

test4:			fclean $(NAME_TEST4)
						@(./$(NAME_TEST4))

test5:			fclean $(NAME_TEST5)
						@(./$(NAME_TEST5))

test6:			fclean $(NAME_TEST6)
						@(./$(NAME_TEST6))
