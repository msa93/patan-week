patan:
	gcc -o main \
	-I./qlib \
	main.c \
	`pkg-config --cflags --libs glib-2.0`
