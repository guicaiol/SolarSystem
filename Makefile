SRC		= src
OBJ		= obj
BIN		= bin
CC		= g++
CFLAGS	= -Wall -Isrc/
LFLAGS	= -lglut -lGLU -lGL -lm
TARGET	= $(BIN)/SolarSystem

OBJECTS = \
	$(OBJ)/planet.o \
	$(OBJ)/object.o \
	$(OBJ)/position.o \
	$(OBJ)/color.o \
	$(OBJ)/solarsystem.o \
	$(OBJ)/imageloader.o \
	$(OBJ)/main.o
	
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)
	
$(OBJ)/planet.o:
	$(CC) $(CFLAGS) -c $(SRC)/SolarSystem/object/planet/planet.cc -o $@
	
$(OBJ)/object.o:
	$(CC) $(CFLAGS) -c $(SRC)/SolarSystem/object/object.cc -o $@
	
$(OBJ)/position.o:
	$(CC) $(CFLAGS) -c $(SRC)/SolarSystem/utils/position.cc -o $@

$(OBJ)/color.o:
	$(CC) $(CFLAGS) -c $(SRC)/SolarSystem/utils/color.cc -o $@
	
$(OBJ)/solarsystem.o:
	$(CC) $(CFLAGS) -c $(SRC)/SolarSystem/solarsystem.cc -o $@
	
$(OBJ)/imageloader.o:
	$(CC) $(CFLAGS) -c $(SRC)/3rdparty/imageloader.cc -o $@
	
$(OBJ)/main.o:
	$(CC) $(CFLAGS) -c $(SRC)/main.cc -o $@

clean:
	rm -f $(OBJ)/* $(TARGET)
	
valgrind:
	valgrind ./$(TARGET)

