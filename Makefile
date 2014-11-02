patan:
	gcc -o main \
	-I./qlib -I ./ \
        ./qlib/*.c \
	patan.c \
	main.c \
	`pkg-config --cflags --libs glib-2.0`
