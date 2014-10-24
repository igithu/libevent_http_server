
#SUBDIRS=src
#DIST_SUBDIRS=src

bin_PROGRAMS = http_server

http_server_SOURCES = \
		      src/main.cc \
		      src/http_server.h \
		      src/http_server.cpp \
		      src/http_handler.h \
		      src/http_handler.cpp \
		      src/util.h \
		      src/util.cpp

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
http_server_CPPFLAGS = -I../third-64/libevent/include/
#http_server_LDFLAGS = -L../third-64/libevent/lib/*.a
http_server_LDADD = -lpthread -lz -ldl -lrt ../third-64/libevent/lib/*.a 
#http_server_a_LDADD = ../third-64/libevent/lib/*.a
