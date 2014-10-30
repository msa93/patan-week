patan:
	gcc -o main \
	-I./qlib \
    ./qlib/*.c \
	main.c \
	`pkg-config --cflags --libs glib-2.0`
