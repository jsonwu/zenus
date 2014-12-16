CXX=g++
CPP_FLAGS= -Wall -O3 -g 
LIB=-lpthread -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto -lprotobuf
LIB_DIR = -L/usr/lib64/mysql 
SHARE_LIB_PATH = ../lib

DB_LIB += $(SHARE_LIB_PATH)/libgamecommon.a
DB_LIB += $(SHARE_LIB_PATH)/libnet.a
DB_LIB += $(SHARE_LIB_PATH)/libtimer.a


TARGET=gameserver

MACROS =

VPATH = ../share/
VPATH += ../protc 

INCLUDE_DIRS = -I./ -I../share/net  -I../share/common   -I ../share/timer -I../share/thread  -I../common -I/usr/include/mysql/  -I../protc  -I../game_common

CPPFLAGS := $(CPP_FLAGS) $(INCLUDE_DIRS) $(MACROS)
LFALGS :=  $(CPP_FLAGS)  $(LIB) $(LIB_DIR)

SRCS := $(wildcard *.cpp)
OBJS_CPP := $(patsubst %.cpp, %.o, $(SRCS))
#OBJS := $(SRCS:%.cpp=%.o)

SRC_CC := $(wildcard ../protc/*.cc)
OBJS_CC := $(notdir $(patsubst %.cc, %.o, $(SRC_CC)))


#OBJS +=$(SRC_CC:%.cc=%.o)


#OBJS := $(OBJS_CC)
#OBJS += $(OBJS_CPP)


$(TARGET):$(OBJS_CPP) $(OBJS_CC)
	$(CXX) $(LFALGS) $^ -o $@ $(DB_LIB)
	rm *.o
	cp $(TARGET) ../bin/
	rm $(TARGET)


$(OBJS_CPP):%.o:%.cpp
	$(CXX) $(INCLUDE)   $(CPPFLAGS) -c  $< -o $@ 

$(OBJS_CC):%.o:%.cc
	$(CXX) $(INCLUDE)   $(CPPFLAGS) -c  $< -o $@ 

echo:
	echo $(SRCS)
	echo $(SRC_CC) echo $(OBJS_CC) echo $(OBJS_CPP) 
clean:
	-rm -rf $(TARGET) *.o

tag:
	ctags -R ./*  ../share/*
.PHONY: clean tag echo
