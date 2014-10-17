LIBS = liblogger
DEST = ../../lib

CXX = g++


SRCS := $(wildcard *.cpp)
OBJS_CPP := $(patsubst %.cpp, %.o, $(SRCS))


$(LIBS):$(OBJS_CPP)
	ar r  $(DEST)/$@.a $^ 
	rm ./*.o

$(OBJS_CPP):%.o:%.cpp
	$(CXX) -c $< -o $@


.PHONY : clean	echo

clean:
	rm *.o

echo:
	echo $(OBJS_CPP)
