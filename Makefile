CC = clang
CFLAGS = -Wall -Wextra
SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXE = imhash

all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: all clean
