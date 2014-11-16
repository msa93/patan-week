CFLAGS=-DDEBUG

patanweek:
	gcc -o main \
	-I./qlib -I ./ -I./patan \
        ./qlib/*.c \
	./patan/*.c \
	main.c \
	$(CFLAGS)
