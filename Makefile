################################################################################
#외부 라이브러리는 link order를 고려해서 순서를 정해야 한다.
#mysql -> boost 순으로 참조하는 경우 반드시 mysql을 먼저 설정하고, boost를 나중에 설정해야 한다.



################################################################################
# mysql cluster
NDB_ROOT:=$(MYSQL_ROOT)/storage/ndb

INCLUDES+=-I$(MYSQL_ROOT)/include
INCLUDES+=-I$(NDB_ROOT)/include

LIBS+=$(NDB_ROOT)/src/libndbclient_static.a
LIBS+=$(MYSQL_ROOT)/libmysql/libmysqlclient.a



################################################################################
# boost
INCLUDES+=-I$(BOOST_ROOT)
LDFLAGS+=-L$(BOOST_ROOT)/stage64/lib
LIBS+=-lboost_log
LIBS+=-lboost_thread
LIBS+=-lboost_system



################################################################################
# common
INCLUDES+=-Isrc
LIBS+=-lpthread

WFLAGS:=-Wall -Wextra -Wformat-security -Wvla -Woverloaded-virtual -Wunused -Wno-unused-parameter -Wno-unknown-pragmas
#DFLAGS:=-DDBUG_OFF -D_DEBUG
DFLAGS:=-DDBUG_OFF
#CXXFLAGS:=-c -std=c++11 -O3 -g -fno-omit-frame-pointer $(WFLAGS) $(DFLAGS) $(INCLUDES)
CXXFLAGS:=-c -std=c++11 -O3 -fno-omit-frame-pointer $(WFLAGS) $(DFLAGS) $(INCLUDES)

VPATH=src:src/ssLib:src/ssImpl
CPPS=$(wildcard src/stdafx.cpp src/ssLib/*.cpp src/ssImpl/*.cpp)
OBJS=$(addprefix obj/, $(notdir $(CPPS:.cpp=.o)))
EXEC=SimpleServer SimpleClient


all: $(EXEC)

SimpleServer: Makefile src/stdafx.hpp.gch $(OBJS) obj/SimpleServer.o
	@echo "[Link] $@"
	@g++ -o $@ $(OBJS) obj/$@.o $(LDFLAGS) $(LIBS)

SimpleClient: Makefile src/stdafx.hpp.gch $(OBJS) obj/SimpleClient.o
	@echo "[Link] $@"
	@g++ -o $@ $(OBJS) obj/$@.o $(LDFLAGS) $(LIBS)

clean:
	rm -rf $(EXEC) obj src/stdafx.hpp.gch

src/stdafx.hpp.gch: src/stdafx.hpp
	@mkdir -p obj
	@echo "[Build] PreCompiled Header"
	@g++ $(CXXFLAGS) -c $< -o $@

obj/%.o: %.cpp src/stdafx.hpp.gch
	@mkdir -p obj
	@echo "[Compile] $<"
	@g++ $(CXXFLAGS) -c -MD -o $@ $<

-include $(OBJS:%.o=%.d)
