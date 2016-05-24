CC=g++
CFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = .main.o .World.o .MobileCircle.o .Bird.o .TexturesHolder.o .BirdRegulator.o .Projectile.o

start: $(OBJECTS)
	$(CC) -std=c++11 .*.o $(CFLAGS)

.main.o: main.cpp World.h
	$(CC) -std=c++11 -o $@ -c main.cpp

.World.o: World.cpp World.h MobileCircle.h Bird.h TexturesHolder.h BirdRegulator.h
	$(CC) -std=c++11 -o $@ -c World.cpp

.MobileCircle.o: MobileCircle.h MobileCircle.cpp
	$(CC) -std=c++11 -o $@ -c MobileCircle.cpp

.Bird.o: Bird.cpp Bird.h TexturesHolder.h Projectile.h
	$(CC) -std=c++11 -o $@ -c Bird.cpp

.TexturesHolder.o: TexturesHolder.cpp TexturesHolder.h
	$(CC) -std=c++11 -o $@ -c TexturesHolder.cpp

.BirdRegulator.o: BirdRegulator.cpp BirdRegulator.h Bird.h
	$(CC) -std=c++11 -o $@ -c BirdRegulator.cpp

.Projectile.o: Projectile.cpp Projectile.h TexturesHolder.h
	$(CC) -std=c++11 -o $@ -c Projectile.cpp
