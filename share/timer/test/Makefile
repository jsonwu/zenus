CXX=g++
CPP_FLAGS= -Wall -O3 -g 
LIB=-lpthread -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto
LIB_DIR = -L/usr/lib64/mysql 

TARGET=test

MACROS =

VPATH = ../share/
VPATH += ../protc 

LIB_A_PATH = ../../../lib

#LIB_A += $(LIB_A_PATH)/liblogger.a
LIB_A += $(LIB_A_PATH)/libtimer.a

INCLUDE_DIRS = -I./ -I../../../share/timer  -I../../../share/common  -I../../thread  -I../../net

CPPFLAGS := $(CPP_FLAGS) $(INCLUDE_DIRS) $(MACROS)
LFALGS :=  $(CPP_FLAGS)  $(LIB) $(LIB_DIR)

SRCS := $(wildcard *.cpp)
OBJS_CPP := $(patsubst %.cpp, %.o, $(SRCS))


$(TARGET):$(OBJS_CPP)
	$(CXX) $(LFALGS) $^  -o $@  $(LIB_A)


$(OBJS_CPP):%.o:%.cpp
	$(CXX) $(INCLUDE)   $(CPPFLAGS) -c  $< -o $@ 


echo:
	echo $(SRCS)
	echo $(SRC_CC)
	echo $(OBJS_CPP)

clean:
	-rm -rf $(TARGET) *.o

tag:
	ctags -R ./*  ../share/*
.PHONY: clean tag echo
