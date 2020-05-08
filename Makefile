COMP=g++
PROG=render
FLAGS=-lncurses
OBJS= main.o renderer.o color.o

$(PROG) : $(OBJS)
	$(COMP) $(FLAGS) -o $(PROG) $(OBJS)

color.o : color.cpp color.h
	$(COMP) $(FLAGS) -c color.cpp

renderer.o: renderer.cpp renderer.h color.h
	$(COMP) $(FLAGS) -c renderer.cpp

main.o : main.cpp renderer.h
	$(COMP) $(FLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)
