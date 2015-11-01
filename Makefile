CFLAGS = `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm
INCS = $(TARGET).h binaryGame.h
TARGET = game
SOURCES =  binaryGame.c $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
push:
	git commit -a -m $$(date +%d-%m-%Y/%H:%M)
	git push "https://github.com/nikopapp/SoftwareEngineering"
