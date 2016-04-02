OBJ = main.o Shader.o
LIB = -lsfml-graphics -lsfml-window -lsfml-system -pthread -lGL -lGLEW
CFLAGS = -Wall -Wextra -Werror -O2 -std=c++14
CC = g++
TARGET = Programme

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIB) $(CFLAGS)

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c $<
Shader.o: src/Shader.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o

mrproper: clean
	rm Programme
