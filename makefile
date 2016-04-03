OBJ = main.o Shader.o MyException.o Texture.o
LIB = -lsfml-graphics -lsfml-window -lsfml-system -pthread -lGL -lGLEW
CFLAGS = -Wall -Wextra -Werror -O2 -std=c++14
CC = g++
TARGET = Programme

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIB) $(CFLAGS)

main.o: src/main.cpp include/Shader.h include/MyException.h
	$(CC) $(CFLAGS) -c $<
Shader.o: src/Shader.cpp include/Shader.h include/MyException.h
	$(CC) $(CFLAGS) -c $<
MyException.o: src/MyException.cpp include/MyException.h	
	$(CC) $(CFLAGS) -c $<
Texture.o: src/Texture.cpp include/MyException.h include/Texture.h
	$(CC) $(CFLAGS) -c $<


clean:
	rm *.o

mrproper: clean
	rm Programme
