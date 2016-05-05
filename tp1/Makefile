CC=g++
CFLAGS=-c -Wall
LFLAGS=-lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
OBJS=Brick.o Color.o
%.o: %.cpp
	@echo 'Building $<'
	$(CC) $(CFLAGS) "$<" -o "$@"
	@echo '$< built.'
	@echo ' '

all: tp1

tp1: $(OBJS) main.o
	@echo 'Building target $@'
	@echo 'Linking objects'
	$(CC) -o "$@" $(OBJS) main.o $(LFLAGS)
	@echo 'Target $@ built'
	@echo ' '

clean:
	rm -rf $(OBJS) main.o tp1
