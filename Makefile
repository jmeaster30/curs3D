COMP=g++
PROG=render
FLAGS=-lncurses
OBJS= main.o renderer.o color.o engine.o

$(PROG) : $(OBJS)
	$(COMP) $(FLAGS) -o $(PROG) $(OBJS)

engine.o : engine.cpp engine.h renderer.h
	$(COMP) $(FLAGS) -c engine.cpp

color.o : color.cpp color.h
	$(COMP) $(FLAGS) -c color.cpp

renderer.o: renderer.cpp renderer.h color.h
	$(COMP) $(FLAGS) -c renderer.cpp

main.o : main.cpp engine.h
	$(COMP) $(FLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)
