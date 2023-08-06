CC = clang
CFLAGS = -Wall -Wextra
SRCS = main.c lib.c
OBJS = $(SRCS:.c=.o)
EXE = imhash

all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)
	rm -f *.jpeg

.PHONY: all clean
