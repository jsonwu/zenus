CXX=g++
CPP_FLAGS= -Wall -O3 -g 
LIB=-lpthread -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto
LIB_DIR = -L/usr/lib64/mysql 

TARGET=test

MACROS =

VPATH = ../share/
VPATH += ../protc 

LIB_A_PATH = ../../../lib


INCLUDE_DIRS = -I./ -I../../../share/net  -I../../../share/common  -I../../../share/thread  -I../../../share/log -I../../../common -I/usr/include/mysql/  -I../../../protc -I../../../share/pip

CPPFLAGS := $(CPP_FLAGS) $(INCLUDE_DIRS) $(MACROS)
LFALGS :=  $(CPP_FLAGS)  $(LIB) $(LIB_DIR)

SRCS := $(wildcard *.cpp)
OBJS_CPP := $(patsubst %.cpp, %.o, $(SRCS))


$(TARGET):$(OBJS_CPP)
	$(CXX) $(LFALGS) $^  -o $@


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
