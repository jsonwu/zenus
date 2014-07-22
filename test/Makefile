CXX=g++
CPP_FLAGS= -Wall -O3 -g 
LIB=-lpthread


TARGET=test

MACROS =

VPATH = ../share/

INCLUDE_DIRS = -I./ -I../share/net  -I../share/common  -I../share/thread

CPPFLAGS := $(CPP_FLAGS) $(INCLUDE_DIRS) $(MACROS)

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

$(TARGET):$(OBJS)
	$(CXX) $(CPPFLAGS) $^ -o $@  $(LIB)


$(OBJS):%.o:%.cpp 
	$(CXX) $(INCLUDE) $(CPPFLAGS) -c $< -o $@ 

echo:
	echo $(SRCS)

clean:
	-rm -rf $(TARGET) *.o

tag:
	ctags -R ./*  ../share/*
.PHONY: clean tag echo
