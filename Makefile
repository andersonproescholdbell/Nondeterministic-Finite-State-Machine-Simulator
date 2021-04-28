# Anderson Proescholdbell

CXX = clang++
CXXFLAGS = -g -Wall
OBJECTS = main.o NFA.o

a.out: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o a.out
	@echo "Compiled!"

main.o: main.cpp NFA.h
NFA.o: NFA.cpp NFA.h


.PHONY: clean
clean:
	-rm -f *.o *~ a.out
