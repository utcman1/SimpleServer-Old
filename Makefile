################################################################################
# boost
BOOST_ROOT=/root/rpmbuild/SOURCES/boost_1_61_0
BOOST_INCLUDE=$(BOOST_ROOT)
BOOST_LIBS=-L$(BOOST_ROOT)/stage64/lib -lboost_log -lboost_thread -lboost_system

################################################################################
# mysql cluster
MYSQL_ROOT=/root/rpmbuild/SOURCES/mysql-cluster-gpl-7.5.3
NDB_ROOT=$(MYSQL_ROOT)/storage/ndb

MYSQL_INCLUDE=$(MYSQL_ROOT)/include:$(NDB_ROOT)/include:$(NDB_ROOT)/include/portlib

MYSQL_LIBS+=$(NDB_ROOT)/src/libndbclient_static.a
MYSQL_LIBS+=$(MYSQL_ROOT)/libmysql/libmysqlclient.a

#MYSQL_LIBS+=$(NDB_ROOT)/src/ndbapi/libndbapi.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/mgmapi/libndbmgmapi.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/mgmsrv/libndbconf.a

#MYSQL_LIBS+=$(NDB_ROOT)/src/common/transporter/libndbtransport.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/common/logger/libndblogger.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/common/util/libndbgeneral.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/common/debugger/libndbtrace.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/common/portlib/libndbportlib.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/common/mgmcommon/libndbmgmcommon.a
#MYSQL_LIBS+=$(NDB_ROOT)/src/common/debugger/signaldata/libndbsignaldata.a

#MYSQL_LIBS+=$(MYSQL_ROOT)/mysys_ssl/libmysys_ssl.a
#MYSQL_LIBS+=$(MYSQL_ROOT)/mysys/libmysys.a
#MYSQL_LIBS+=$(MYSQL_ROOT)/extra/yassl/taocrypt/libtaocrypt.a
#MYSQL_LIBS+=$(MYSQL_ROOT)/strings/libstrings.a



CPLUS_INCLUDE_PATH=$(BOOST_INCLUDE):$(MYSQL_INCLUDE):src
WFLAGS=-Wall -Wextra -Wformat-security -Wvla -Woverloaded-virtual -Wunused -Wno-unused-parameter -Wno-unknown-pragmas
#DFLAGS=-DDBUG_OFF -D_DEBUG
DFLAGS=-DDBUG_OFF
#CXXFLAGS=-c -std=c++11 -O3 -g -fno-omit-frame-pointer $(INCLUDE) $(WFLAGS) $(DFLAGS)
CXXFLAGS=-c -std=c++11 -O3 -fno-omit-frame-pointer $(INCLUDE) $(WFLAGS) $(DFLAGS)
LDFLAGS+=-lpthread

export CPLUS_INCLUDE_PATH

VPATH=src:src/ssLib:src/ssImpl

CPPS=$(wildcard src/stdafx.cpp src/ssLib/*.cpp src/ssImpl/*.cpp)
OBJS=$(addprefix obj/, $(notdir $(CPPS:.cpp=.o)))



all: SimpleServer SimpleClient

SimpleServer: Makefile obj/stdafx.hpp.gch $(OBJS) obj/SimpleServer.o
	@echo "[Link] SimpleServer"
	@g++ -o SimpleServer $(OBJS) obj/SimpleServer.o $(LDFLAGS) $(BOOST_LIBS)

SimpleClient: Makefile obj/stdafx.hpp.gch $(OBJS) obj/SimpleClient.o
	@echo "[Link] SimpleClient"
	@g++ -o SimpleClient $(OBJS) obj/SimpleClient.o $(LDFLAGS) $(BOOST_LIBS)

clean:
	rm -rf $(EXEC) obj

obj/stdafx.hpp.gch: src/stdafx.hpp
	@mkdir -p obj
	@echo "[Build] PreCompiled Header"
	@g++ $(CXXFLAGS) -c $< -o $@

obj/%.o: %.cpp
	@mkdir -p obj
	@echo "[Compile] $<"
	@g++ $(CXXFLAGS) -c -MD -o $@ $<

-include $(OBJS:%.o=%.d)
