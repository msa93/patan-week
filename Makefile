patan:
	gcc -o main \
	-I./qlib -I ./ \
        ./qlib/*.c \
	patan.c \
	main.c \
	`pkg-config --cflags gtk+-3.0 --libs glib-2.0`
