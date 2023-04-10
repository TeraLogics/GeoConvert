CXXFLAGS:=-fPIC
SRC:=$(wildcard *.cpp)
OBJS:=$(SRC:.cpp=.o)

libgeoconvert.a: $(OBJS)
	ar -rcs $@ $(OBJS)

clean:
	-rm libgeoconvert.a
	-rm *.o
