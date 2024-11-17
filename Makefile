CC = clang
CFLAGS = -fsanitize=safe-stack -Wall -Wextra

all: main unsafe

main: main.c
	$(CC) $(CFLAGS) -o main main.c

unsafe: unsafe.c
	$(CC) -Wall -Wextra -o unsafe unsafe.c

clean:
	rm -f main unsafe
