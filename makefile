CC=g++
CFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = .main.o .World.o .MobileCircle.o .Bird.o .TexturesHolder.o

start: $(OBJECTS)
	$(CC) -std=c++11 .*.o $(CFLAGS)

.main.o: main.cpp World.h
	$(CC) -std=c++11 -o $@ -c main.cpp

.World.o: World.cpp World.h MobileCircle.h Bird.h TexturesHolder.h
	$(CC) -std=c++11 -o $@ -c World.cpp

.MobileCircle.o: MobileCircle.h MobileCircle.cpp
	$(CC) -std=c++11 -o $@ -c MobileCircle.cpp

.Bird.o: Bird.cpp Bird.h TexturesHolder.h
	$(CC) -std=c++11 -o $@ -c Bird.cpp

.TexturesHolder.o: TexturesHolder.cpp TexturesHolder.h
	$(CC) -std=c++11 -o $@ -c TexturesHolder.cpp
