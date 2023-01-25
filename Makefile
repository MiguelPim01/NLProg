PROJ_NAME_1=prog1
PROJ_NAME_2=prog2

CC=gcc
CFLAGS=-lm -g -Wall

C_SOURCE=$(wildcard ./source/*.c)

H_SOURCE=$(wildcard ./headers/*.h)

OBJ=$(C_SOURCE:./source/%.c=./objects/%.o)

all: $(PROJ_NAME_1) $(PROJ_NAME_2)

# Fazer o prog1
$(PROJ_NAME_1): $(OBJ) ./objects/main1.o
	$(CC) -o $@ $^ $(CFLAGS)

# Fazer o prog2
$(PROJ_NAME_2): $(OBJ) ./objects/main2.o
	$(CC) -o $@ $^ $(CFLAGS)

./objects/%.o: ./source/%.c ./headers/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main1.o: main1.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main2.o: main2.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf ./objects/*.o $(PROJ_NAME_1) $(PROJ_NAME_2)