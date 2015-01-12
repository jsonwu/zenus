LIBS = libpip
DEST = ../../lib
CXX = g++


SRCS := $(wildcard *.cpp)
OBJS_CPP := $(patsubst %.cpp, %.o, $(SRCS))

INCLUDE_DIRS = -I../../share/thread -I../../share/common   -I../../share/buff -I. -I../../share/pip

$(LIBS):$(OBJS_CPP)
	ar r  $(DEST)/$@.a $^ 
	rm ./*.o

$(OBJS_CPP):%.o:%.cpp
	$(CXX) -c $(INCLUDE_DIRS) $< -o $@


.PHONY : clean	echo

clean:
	rm *.o

echo:
	echo $(OBJS_CPP)
