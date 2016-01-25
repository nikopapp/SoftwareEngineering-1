CFLAGS = `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm -O4 -lSDL2_image -lSDL2_mixer
INCS = $(TARGET).h input.h grid.h entity.h base.h bgame.h display.h quizGame.h
TARGET = game
TEST = test
TSOURCES =  quizGame.c grid.c input.c display.c entity.c bgame.c  $(TEST).c
SOURCES =  quizGame.c grid.c input.c display.c entity.c bgame.c  $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
test: quizGame.c grid.c input.c display.c entity.c bgame.c  test.c
	gcc quizGame.c grid.c input.c display.c entity.c bgame.c  test.c -o test `sdl2-config --cflags` -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf `sdl2-config --libs`
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
