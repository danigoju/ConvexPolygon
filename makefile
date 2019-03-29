# Defines the flags for compiling with C++.
CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include


all: main.exe

# Regla per netejar tots els arxius executables (make clean).
clean:
	rm -f main.exe *.o


# Regla per linkar tots els arxius objecte (llenguatge compilat o assamblador)
main.exe: main.o Point.o ConvexPolygon.o
	$(CXX) $^ -L $(HOME)/libs/lib -l PNGwriter -l png -o $@


# Dependències entre arxius

main.o: main.cc Point.hh ConvexPolygon.hh

Point.o: Point.cc Point.hh

ConvexPolygon.o: ConvexPolygon.cc ConvexPolygon.hh Point.hh
