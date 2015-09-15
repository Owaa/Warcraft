CC = gcc
FLAGS =  -lm -lGL -lGLU -lglut
NAME = warcraft
SRC = f1.c image.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	@rm $(NAME) $(OBJS) *~ 

