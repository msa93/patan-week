CFLAGS=-I./qlib -I ./ -I./patan
ifeq ($(debug),1)
	CFLAGS+=-DDEBUG
endif

patanweek:
	gcc -o main \
        ./qlib/*.c \
	./patan/*.c \
	main.c \
	$(CFLAGS)
