CFLAGS = `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf
INCS = $(TARGET).h input.h grid.h entity.h base.h bgame.h display.h
TARGET = game
TEST = test
TSOURCES =  encryption.c grid.c input.c display.c entity.c bgame.c  $(TEST).c
SOURCES =  encryption.c grid.c input.c display.c entity.c bgame.c  $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
test:
	$(CC) $(TSOURCES) -o $(TEST) $(CFLAGS) $(LIBS)
	./$(TEST) 		

push:
	git commit -a -m $$(date +%d-%m-%Y/%H:%M)
	git push
pull:
	git pull
debug:
	valgrind ./game
gdebug:
	gdb ./game
