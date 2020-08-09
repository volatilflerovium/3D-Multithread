# to run this file:
# $ make -f clock.mk
# $ make -f clock.mk clean

FLAGS = -c -std=c++11

animation-app : animation.o noise.o base.o shape.o mover.o master.o camera.o platonic.o
	g++ base.o noise.o shape.o mover.o master.o camera.o platonic.o animation.o -o animation-app -pthread -lsfml-graphics -lsfml-window -lsfml-system

base.o : base.cpp
	g++ ${FLAGS} base.cpp

noise.o : noise.cpp
	g++ ${FLAGS} noise.cpp

shape.o : shape.cpp
	g++ ${FLAGS} shape.cpp

mover.o : mover.cpp
	g++ ${FLAGS} mover.cpp

master.o : master.cpp
	g++ ${FLAGS} master.cpp

camera.o : camera.cpp
	g++ ${FLAGS} camera.cpp

platonic.o : platonic.cpp
	g++ ${FLAGS} platonic.cpp	

animation.o : animation.cpp
	g++ ${FLAGS} animation.cpp

clean :
	rm -f *~ *.o 
